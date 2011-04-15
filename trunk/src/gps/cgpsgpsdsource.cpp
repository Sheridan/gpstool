#include "cgpsgpsdsource.h"
#include "cgpsgpsdsourcedialog.h"
#include "st.h"
#include "optionsdefines.h"
#include "gtdebug.h"
#include <QRegExp>
namespace gps
{
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsGpsdSource::CGpsGpsdSource(const QString & host, int port) : CGpsSource(gstGpsd)
{
    optionsConstruct();
    setHost(host);
    setPort(port);
    m_gpsdConnection = NULL;
    m_lastTimestamp = 0;
}
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsGpsdSource::CGpsGpsdSource(const gps::TGpsSourceId &id) : CGpsSource(gstGpsd, id)
{
    optionsConstruct();
    m_gpsdConnection = NULL;
}
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsGpsdSource::~CGpsGpsdSource()
{
    delete m_gpsdConnection;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsGpsdSource::threadStop()
{
    if(isGpsConnected()) { disconnectGps(); }
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsGpsdSource::optionsConstruct()
{
    m_host = GT_OPTIONS_GPS->requestOption(GT_OPTION_GPSD_HOST(id()));
    m_port = GT_OPTIONS_GPS->requestOption(GT_OPTION_GPSD_PORT(id()));
}
// --------------------------------------------------------------------------------------------------------------------------------------
bool CGpsGpsdSource::connectGps()
{
    emit statusChanging();
    if(!m_gpsdConnection) { m_gpsdConnection = new QTcpSocket(); }
    m_gpsdConnection->connectToHost(m_host->value(), m_port->value());
    m_gpsdConnection->setSocketOption(QAbstractSocket::LowDelayOption, 0);
    if (m_gpsdConnection->waitForConnected())
    {
        GT_LOGGER->append(QObject::tr("Connected to `%1` %2:%3").arg(name()).arg(m_host->value()).arg(m_port->value()));
        emit connected();
        return true;
    }
    GT_LOGGER->append(QObject::tr("Can not connect to `%1` %2:%3").arg(name()).arg(m_host->value()).arg(m_port->value()), m_gpsdConnection->errorString(), mtError);
    emit connectionError();
    return false;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsGpsdSource::disconnectGps()
{
    emit statusChanging();
    m_gpsdConnection->disconnectFromHost();
    if (m_gpsdConnection->state() == QAbstractSocket::UnconnectedState || m_gpsdConnection->waitForDisconnected())
    {
        GT_LOGGER->append(QObject::tr("Disconnected from `%1` %2:%3").arg(name()).arg(m_host->value()).arg(m_port->value()));
        emit disconnected();
    }
    else
    {
        GT_LOGGER->append(QObject::tr("Can not disconnect from `%1` %2:%3").arg(name()).arg(m_host->value()).arg(m_port->value()), m_gpsdConnection->errorString(), mtError);
        emit connectionError();
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
bool CGpsGpsdSource::isGpsConnected()
{
    return m_gpsdConnection && m_gpsdConnection->state() == QAbstractSocket::ConnectedState;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsGpsdSource::showOptionsDialog()
{
    ui::dialogs::CGpsGpsdSourceDialog *dlg = new ui::dialogs::CGpsGpsdSourceDialog(id());
    dlg->exec();
    delete dlg;
}
// --------------------------------------------------------------------------------------------------------------------------------------
TStringMap CGpsGpsdSource::rawQuery(const QString & request)
{
    TStringMap smap;
    if(isGpsConnected())
    {
        if(!m_gpsdConnection->write(request.toLatin1()) || !m_gpsdConnection->waitForReadyRead())
        {
            GT_LOGGER->append(QObject::tr("Can not read from `%1` %2:%3").arg(name()).arg(m_host->value()).arg(m_port->value()), m_gpsdConnection->errorString(), mtError);
            //disconnectGps();
        }
        else
        {
            QString returned = QString(m_gpsdConnection->readAll()).simplified();
            GT_DEBUG_ADV(tr("Data from %1:%2").arg(m_host->value()).arg(m_port->value()), QString(returned).replace(",", "\n"));
            returned.remove(QRegExp("\\{.*\\}"));
            QStringList data = returned.split(',');
            QStringList entryItems;
            foreach(QString entry, data)
            {
                if(entry == "GPSD") { continue; }
                entryItems = entry.split('=');
                smap[entryItems.at(0)] = entryItems.at(1).simplified();
            }
        }
    }
    return smap;
}
// --------------------------------------------------------------------------------------------------------------------------------------
#define GT_GPSD_RAWQUERY(_q) TStringMap smap = rawQuery(_q);
#define GT_GPSD_RESPONSE_AVIALABLE (!smap.empty())
#define GT_GPSD_VALUE(_T_) string_##_T_
#define GT_GPSD_EXTRACT_VALUE(_T_) QString GT_GPSD_VALUE(_T_) = smap.value(#_T_);
#define GT_GPSD_VALUE_AVIALABLE(_T_) (!GT_GPSD_VALUE(_T_).isEmpty() && GT_GPSD_VALUE(_T_) != "?")
// --------------------------------------------------------------------------------------------------------------------------------------
QString CGpsGpsdSource::gpsInfo()
{
    GT_GPSD_RAWQUERY("fil");
    if(GT_GPSD_RESPONSE_AVIALABLE)
    {
        GT_GPSD_EXTRACT_VALUE(F);
        GT_GPSD_EXTRACT_VALUE(I);
        GT_GPSD_EXTRACT_VALUE(L);
        QStringList version = GT_GPSD_VALUE(L).split(' ');
        return QObject::tr("Type: gpsd\nIdentify: %1\nDevice: %2\nProtocol revision: %3\nGpsd version: %4\nGpsd avialable commands: %5")
                .arg(GT_GPSD_VALUE(I))
                .arg(GT_GPSD_VALUE(F))
                .arg(version.at(0))
                .arg(version.at(1))
                .arg(version.at(2));
    }
    return QObject::tr("Type: gpsd\nCan not read info");
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsGpsdSource::update()
{
    emit updateBegin();
    GT_GPSD_RAWQUERY("yxtavmsepuq");
    if(GT_GPSD_RESPONSE_AVIALABLE)
    {
        // x	Returns "X=0" if the GPS is offline, "X=%f" if online; in the latter case, %f is a timestamp from
        //		when the last sentence was received.
        GT_GPSD_EXTRACT_VALUE(X);
        if(GT_GPSD_VALUE_AVIALABLE(X) && GT_GPSD_VALUE(X).toDouble() != 0)
        {
            emit usable();
            data::CGpsData *segment = new data::CGpsData(name(), id(), updateReceivers());
            double timestamp = GT_GPSD_VALUE(X).toDouble();
            if(timestamp != m_lastTimestamp)
            {
                segment->setTimestamp(timestamp);
                m_lastTimestamp = timestamp;
            }

            // y	Returns Y=, followed by a sentence tag, followed by a timestamp (seconds since the Unix epoch, UTC)
            //		and a count not more than 12, followed by that many quintuples of satellite PRNs,
            //		elevation/azimuth pairs (elevation an integer formatted as %d in range 0-90, azimuth an integer
            //		formatted as %d in range 0-359), signal strengths in decibels, and
            //		1 or 0 according as the satellite was or was not used in the last fix. Each number is followed by one space.
            GT_GPSD_EXTRACT_VALUE(Y);
            if(GT_GPSD_VALUE_AVIALABLE(Y))
            {
                QStringList satelliteInfoList;
                QStringList satellitesInfoList = GT_GPSD_VALUE(Y).split(":");
                QStringList mainInfoList = satellitesInfoList.takeFirst().split(" ");
                segment->setSatellitesSentence(mainInfoList.at(0));
                int count = mainInfoList.at(2).toInt();
                for(int i = 0; i < count; i++)
                {
                    satelliteInfoList = satellitesInfoList.takeFirst().split(" ");
                    if((satelliteInfoList.at(2).toInt() || satelliteInfoList.at(1).toInt()) && satelliteInfoList.at(3).toInt())
                    {
                        segment->appendSatellite(
                                satelliteInfoList.at(0).toInt(), // sat prn
                                satelliteInfoList.at(3).toInt(), // signal str
                                satelliteInfoList.at(4).toInt(), // used in last fix
                                satelliteInfoList.at(2).toInt(), // azimuth
                                satelliteInfoList.at(1).toInt()  // elevation
                                );

                    }
                }
            }
            // t	Track made good; course "T=%f" in degrees from true north.
            GT_GPSD_EXTRACT_VALUE(T);
            if(GT_GPSD_VALUE_AVIALABLE(T))
            {
                segment->setCourseFromNorth(GT_GPSD_VALUE(T).toFloat());
            }

            // a	The current altitude as "A=%f", meters above mean sea level.
            GT_GPSD_EXTRACT_VALUE(A);
            if(GT_GPSD_VALUE_AVIALABLE(A))
            {
                segment->setAltitude(GT_GPSD_VALUE(A).toFloat());
            }

            // v	The current speed over ground as "V=%f" in knots.
            GT_GPSD_EXTRACT_VALUE(V);
            if(GT_GPSD_VALUE_AVIALABLE(V))
            {
                segment->setSpeedOverGround(GT_GPSD_VALUE(V).toFloat());
            }

            // m	The NMEA mode as "M=%d". 0=no mode value yet seen, 1=no fix, 2=2D (no altitude), 3=3D (with altitude).
            GT_GPSD_EXTRACT_VALUE(M);
            if(GT_GPSD_VALUE_AVIALABLE(M))
            {
                segment->setMode((static_cast<data::EMode>(GT_GPSD_VALUE(M).toInt())));
            }

            // s	The NMEA status as "S=%d". 0=no fix, 1=fix, 2=DGPS-corrected fix.
            GT_GPSD_EXTRACT_VALUE(S);
            if(GT_GPSD_VALUE_AVIALABLE(S))
            {
                segment->setStatus((static_cast<data::EStatus>(GT_GPSD_VALUE(S).toInt())));
            }

            // e	Returns "E=%f %f %f": three estimated position errors in meters -- total, horizontal, and vertical (95% confidence level).
            //		Note: many GPSes do not supply these numbers. When the GPS does not supply them, gpsd computes them from satellite
            //		DOP using fixed figures for expected non-DGPS and DGPS range errors in meters. A value of zero for any of these numbers
            //		should be taken to mean that component of DOP is not available. See also the 'q' command.
            GT_GPSD_EXTRACT_VALUE(E);
            if(GT_GPSD_VALUE_AVIALABLE(E))
            {
                QStringList list = GT_GPSD_VALUE(E).split(" ");
                if(list[0] != "nan") { segment->setPositionQualityT(list[0].toFloat()); }
                if(list[1] != "nan") { segment->setPositionQualityH(list[1].toFloat()); }
                if(list[2] != "nan") { segment->setPositionQualityV(list[2].toFloat()); }
            }
            // p	Returns the current position in the form "P=%f %f"; numbers are in degrees, latitude first.
            GT_GPSD_EXTRACT_VALUE(P);
            if(GT_GPSD_VALUE_AVIALABLE(P))
            {
                QStringList list = GT_GPSD_VALUE(P).split(" ");
                segment->setPosition(list[0].toFloat(), list[1].toFloat());
            }

            // u	Current rate of climb as "U=%f" in meters per second. Some GPSes (non-Sirf-II based) do not report this, in that case gpsd
            //		computes it using the altitude from the last fix (if available).
            GT_GPSD_EXTRACT_VALUE(U);
            if(GT_GPSD_VALUE_AVIALABLE(U))
            {
                segment->setRateOfClimb(GT_GPSD_VALUE(U).toFloat());
            }

            // q	Returns "Q=%d %f %f %f %f %f": a count of satellites used in the last fix, and five dimensionless dilution-of-precision
            //		(DOP) numbers -- spherical, horizontal, vertical, time, and total geometric. These are computed from the satellite geometry;
            //		they are factors by which to multiply the estimated UERE (user error in meters at specified confidence level due to ionospheric
            //		delay, multipath reception, etc.) to get actual circular error ranges in meters (or seconds) at the same confidence level.
            //		See also the 'e' command. Note: Some GPSes may fail to report these, or report only one of them (often HDOP);
            //		a value of 0.0 should be taken as an indication that the data is not available.
            //		Note: Older versions of gpsd reported only the first three DOP numbers, omitting time DOP and total DOP.
            GT_GPSD_EXTRACT_VALUE(Q);
            if(GT_GPSD_VALUE_AVIALABLE(Q))
            {
                QStringList list = GT_GPSD_VALUE(Q).split(" ");
                segment->setDilutionOfPrecision(
                        list[0].toInt(),
                        list[1].toFloat(),
                        list[2].toFloat(),
                        list[3].toFloat(),
                        list[4].toFloat(),
                        list[5].toFloat());
            }
            emit newDataAvialable(segment);
            emit updateEnd();
        }
        else
        {
            emit updateEnd();
            emit unusable();
        }
    }
}

}
