#ifndef CGPSDATABASE_H
#define CGPSDATABASE_H
#include "cdatabase.h"
#include "cgpsdata.h"
#include "coptionbool.h"
namespace data
{
namespace db
{

class CGpsDatabase : public CDatabase
{
    Q_OBJECT
public: // ####################################################
    CGpsDatabase    ();
    ~CGpsDatabase   ();
    void run        ();
private: // ####################################################
    QSqlQuery                   * m_gpsDataInserter;
    QSqlQuery                   * m_satellitesInserter;
    QList<gps::TGpsSourceId>      m_connectedSources;
    QMutex                        m_dbInsertDataMutex;
    options::COptionBool        * m_storeSatellites;

    void connectToSources       ();
    void disconnectFromSources  ();
    void create                 ();
    void afterDatabaseOpen      ();
    void beforeDatabaseClose    ();

private slots: // ####################################################
    void newSourceAvialable (const gps::TGpsSourceId & srcId);
    void sourceRemoved      (const gps::TGpsSourceId & srcId);
    void gpsDataUpdated     (const data::CGpsData *segment);
};

}
}
#endif // CGPSDATABASE_H
