#ifndef CGPSGPSDSOURCE_H
#define CGPSGPSDSOURCE_H

#include "cgpssource.h"
#include "coptionint.h"
#include "coptionstring.h"
#include <QString>
#include <QTcpSocket>
#include <QMap>
namespace gps
{

typedef QMap<QString, QString> TStringMap;

class CGpsGpsdSource : public CGpsSource
{
    Q_OBJECT
public: // ####################################################
    CGpsGpsdSource(const QString & host, int port);
    CGpsGpsdSource(const gps::TGpsSourceId &id);
    virtual ~CGpsGpsdSource();

    QString           gpsInfo   ();
    const QString   & host      () { return m_host->value(); }
    const int       & port      () { return m_port->value(); }

private: // ####################################################
    QTcpSocket              * m_gpsdConnection;
    options::COptionString  * m_host;
    options::COptionInt     * m_port;
    double                    m_lastTimestamp;

    TStringMap  rawQuery        (const QString & request);
    void        optionsConstruct();
    void        threadStop      ();

private slots: // ####################################################
    void update             ();

public slots: // ####################################################
    bool connectGps         ();
    void disconnectGps      ();
    bool isGpsConnected     ();
    void showOptionsDialog  ();
    void setPort            (const int & value      ) { m_port->set(value); }
    void setHost            (const QString & value  ) { m_host->set(value); }
};

}
#endif
