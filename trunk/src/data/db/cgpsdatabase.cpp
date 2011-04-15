#include "cgpsdatabase.h"
#include "st.h"
#include "gtdebug.h"
#include "optionsdefines.h"
namespace data
{
namespace db
{
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsDatabase::CGpsDatabase() : CDatabase("GPSDatabase")
{
    m_gpsDataInserter = NULL;
    m_satellitesInserter = NULL;
    m_storeSatellites = GT_OPTIONS_APP->requestOption(GT_OPTION_STORE_SATELLITES);
}
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsDatabase::~CGpsDatabase()
{
    GT_GPS_MANAGER->disconnectSourceUpdates(this);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsDatabase::run()
{
    GT_GPS_MANAGER->connectSourceUpdates(this, SLOT(newSourceAvialable(const gps::TGpsSourceId &)), SLOT(sourceRemoved(const gps::TGpsSourceId &)));
    QThread::exec();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsDatabase::newSourceAvialable(const gps::TGpsSourceId & srcId)
{
    if(isOpen())
    {
        gps::CGpsSource * src = GT_GPS_MANAGER->source(srcId);
        if(src && !m_connectedSources.contains(srcId))
        {
            src->connectNewData(this, SLOT(gpsDataUpdated(const data::CGpsData *)));
            m_connectedSources << srcId;
        }
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsDatabase::sourceRemoved(const gps::TGpsSourceId & srcId)
{
    if(isOpen())
    {
        gps::CGpsSource * src = GT_GPS_MANAGER->source(srcId);
        if(src)
        {
            src->disconnectNewData(this);
            m_connectedSources.removeOne(srcId);
        }
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsDatabase::connectToSources()
{
    foreach(gps::TGpsSourceId id, GT_GPS_MANAGER->ids())
    {
        GT_GPS_MANAGER->source(id)->connectNewData(this, SLOT(gpsDataUpdated(const data::CGpsData *)));
        m_connectedSources << id;
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsDatabase::disconnectFromSources()
{
    foreach(gps::TGpsSourceId id, m_connectedSources)
    {
        GT_GPS_MANAGER->source(id)->disconnectNewData(this);
        m_connectedSources.removeOne(id);
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsDatabase::create()
{
    CDatabase::create(":/db/sql/db.sql");
}
// --------------------------------------------------------------------------------------------------------------------------------------
#define GT_SQL_GPSDATA_INSERT " \
insert into gpsdata ( \
    gps_name, \
    timestamp, \
    course_from_north, \
    altitude, \
    latitude, \
    longitude, \
    mode, \
    status, \
    speed_over_ground, \
    position_quality_total, \
    position_quality_horizontal, \
    position_quality_vertical, \
    satellites_in_last_fix, \
    dop_spherical, \
    dop_horizontal, \
    dop_vertical, \
    dop_time, \
    dop_total_geometric, \
    sentence ) \
values (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?) "

#define GT_SQL_SATELLITES_INSERT " \
insert into satellites ( \
    gps_name, \
    timestamp, \
    satprn, \
    signal_strength, \
    used_in_last_fix, \
    azimuth, \
    elevation ) \
values (?,?,?,?,?,?,?) "
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsDatabase::afterDatabaseOpen()
{
    m_gpsDataInserter    = new QSqlQuery(m_db);
    m_satellitesInserter = new QSqlQuery(m_db);
    m_gpsDataInserter    ->prepare(GT_SQL_GPSDATA_INSERT     );
    m_satellitesInserter ->prepare(GT_SQL_SATELLITES_INSERT  );
    connectToSources();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsDatabase::beforeDatabaseClose()
{
    disconnectFromSources();
    delete m_satellitesInserter;
    delete m_gpsDataInserter;
    m_satellitesInserter = NULL;
    m_gpsDataInserter    = NULL;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsDatabase::gpsDataUpdated(const data::CGpsData *segment)
{
    if(segment->isTimestampValid())
    {
        m_dbInsertDataMutex.lock();
        emit writeStart();
        m_db.driver()->beginTransaction();
        m_gpsDataInserter->bindValue( 0, segment->gpsSourceName                      ());
        m_gpsDataInserter->bindValue( 1, segment->timestamp                          ());
        m_gpsDataInserter->bindValue( 2, segment->isCourseFromNorthValid             () ? segment->courseFromNorth           () : QVariant(QVariant::Double  ));
        m_gpsDataInserter->bindValue( 3, segment->isAltitudeValid                    () ? segment->altitude                  () : QVariant(QVariant::Double  ));
        m_gpsDataInserter->bindValue( 4, segment->isLatitudeValid                    () ? segment->latitude                  () : QVariant(QVariant::Double  ));
        m_gpsDataInserter->bindValue( 5, segment->isLongitudeValid                   () ? segment->longitude                 () : QVariant(QVariant::Double  ));
        m_gpsDataInserter->bindValue( 6, segment->isModeValid                        () ? segment->mode                      () : QVariant(QVariant::Int     ));
        m_gpsDataInserter->bindValue( 7, segment->isStatusValid                      () ? segment->status                    () : QVariant(QVariant::Int     ));
        m_gpsDataInserter->bindValue( 8, segment->isSpeedOverGroundValid             () ? segment->speedOverGround           () : QVariant(QVariant::Double  ));
        m_gpsDataInserter->bindValue( 9, segment->isPositionQualityTotalValid        () ? segment->positionQualityTotal      () : QVariant(QVariant::Double  ));
        m_gpsDataInserter->bindValue(10, segment->isPositionQualityHorizontalValid   () ? segment->positionQualityHorizontal () : QVariant(QVariant::Double  ));
        m_gpsDataInserter->bindValue(11, segment->isPositionQualityVerticalValid     () ? segment->positionQualityVertical   () : QVariant(QVariant::Double  ));
        m_gpsDataInserter->bindValue(12, segment->isSatellitesInLastFixValid         () ? segment->satellitesInLastFix       () : QVariant(QVariant::Int     ));
        m_gpsDataInserter->bindValue(13, segment->isDopSphericalValid                () ? segment->dopSpherical              () : QVariant(QVariant::Double  ));
        m_gpsDataInserter->bindValue(14, segment->isDopHorizontalValid               () ? segment->dopHorizontal             () : QVariant(QVariant::Double  ));
        m_gpsDataInserter->bindValue(15, segment->isDopVerticalValid                 () ? segment->dopVertical               () : QVariant(QVariant::Double  ));
        m_gpsDataInserter->bindValue(16, segment->isDopTimeValid                     () ? segment->dopTime                   () : QVariant(QVariant::Double  ));
        m_gpsDataInserter->bindValue(17, segment->isDopTotalGeometricValid           () ? segment->dopTotalGeometric         () : QVariant(QVariant::Double  ));
        m_gpsDataInserter->bindValue(18, segment->isSatellitesSentenceValid          () ? segment->satellitesSentence        () : QVariant(QVariant::String  ));
        if(! m_gpsDataInserter->exec() ||
             m_gpsDataInserter->lastError().isValid())
        {
            GT_LOGGER->append(tr("GPS data insert error"),
                             lastErrorToLogDescription(m_gpsDataInserter->lastError(), GT_SQL_GPSDATA_INSERT),
                             mtError);
            m_db.driver()->rollbackTransaction();
        }
        else
        {
            m_db.driver()->commitTransaction();
        }

        if(m_storeSatellites->value() && segment->satellitesCount())
        {
            m_db.driver()->beginTransaction();
            QVariantList data[7];
            foreach(data::CSatelliteData *satData, segment->satellites())
            {
                if(!satData->isEmpty())
                {
                    data[0] << segment->gpsSourceName       ();
                    data[1] << segment->timestamp           ();
                    data[2] << satData->satPrn              ();
                    data[3] << satData->signalStrength      ();
                    data[4] << satData->usedInLastFix       ();
                    data[5] << satData->azimuth             ();
                    data[6] << satData->elevation           ();
                }
            }
            for (int i=0; i<7; i++)
            {
                m_satellitesInserter->bindValue(i, data[i]);
            }
            if(!m_satellitesInserter->execBatch() || m_satellitesInserter->lastError().isValid())
            {
                GT_LOGGER->append(tr("Satellites data insert error"),
                                 lastErrorToLogDescription(m_satellitesInserter->lastError(), GT_SQL_SATELLITES_INSERT),
                                 mtError);
                m_db.driver()->rollbackTransaction();
            }
            else
            {
                m_db.driver()->commitTransaction();
            }
        }
        //GT_LOGGER->append(QString("%1 %2").arg(_gpsDataInserter->boundValues().count()).arg(_satellitesInserter->boundValues().count()));
        emit operationDone();
        m_dbInsertDataMutex.unlock();
    }
    else
    {
        GT_DEBUG("Timestamp not valid, recors not insert into database");
    }
    segment->free();
}

}
}
