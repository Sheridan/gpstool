#include "cgpssource.h"
#include "st.h"
#include "optionsdefines.h"
#include "gtdebug.h"
#include <QDateTime>

namespace gps
{
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsSource::CGpsSource(EGpsSourceTypes gpsType, TGpsSourceId id_val)
    : QThread(), tools::CId(id_val)
{
    m_updateReceivers = 0;
    m_type            = gpsType;
    GT_OPTIONS_GPS->setSectionValue(QString::number(id()), "type", static_cast<int>(m_type));
    m_name           = GT_OPTIONS_GPS->requestOption(GT_OPTION_GPS_NAME            (id()  ));
    m_updatePeriod   = GT_OPTIONS_GPS->requestOption(GT_OPTION_GPS_UPDATE_PERIOD   (id()  ));
    m_autoConnect    = GT_OPTIONS_GPS->requestOption(GT_OPTION_GPS_AUTOCONNECT     (id()  ));
    m_color          = GT_OPTIONS_GPS->requestOption(GT_OPTION_GPS_COLOR           (id()  ));
    m_icon           = GT_OPTIONS_GPS->requestOption(GT_OPTION_GPS_ICON            (id()  ));
    m_timer          = new QTimer(this);
    GT_LOGGER->append(tr("GPS source '%1' created").arg(name()));
}
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsSource::~CGpsSource()
{
    delete m_timer;
    GT_DEBUG(QString("GPS source `%1` destroyed").arg(name()));
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsSource::run()
{
    m_timer->setInterval(m_updatePeriod->value());
    connect(this,    SIGNAL(connected()),    this,    SLOT(sendConnected())   );
    connect(this,    SIGNAL(disconnected()), this,    SLOT(sendDisconnected()));
    connect(this,    SIGNAL(connected()),    m_timer, SLOT(start())           );
    connect(this,    SIGNAL(disconnected()), m_timer, SLOT(stop())            );
    connect(m_timer, SIGNAL(timeout()),      this,    SLOT(update())          );
    exec();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsSource::stop()
{
    threadStop();
    m_timer->stop();
    quit();
    wait();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsSource::setUpdatePeriod(const int & value)
{
    m_updatePeriod->set(value);
    m_timer->setInterval(m_updatePeriod->value());
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsSource::changeStatus()
{
    if(isGpsConnected()) { disconnectGps(); }
    else { connectGps(); }
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsSource::cleanConfig()
{
    GT_OPTIONS_APP->removeSection(name());
}
// --------------------------------------------------------------------------------------------------------------------------------------
bool CGpsSource::connectNewData(const QObject *reciever, const char *slot)
{
    if(connect(this, SIGNAL(newDataAvialable(const data::CGpsData *)), reciever, slot, Qt::QueuedConnection))
    {
        m_updateReceivers++;
        GT_DEBUG_ADV
                (
                QString("New data reciever `%1` connected to `%2` GPS. Total: %3")
                    .arg(reciever->objectName())
                    .arg(name())
                    .arg(m_updateReceivers),
                QString("newDataAvialable -> %1")
                    .arg(slot)
                );
        return true;
    }
    return false;
}
// --------------------------------------------------------------------------------------------------------------------------------------
bool CGpsSource::disconnectNewData(const QObject *reciever)
{
    if(disconnect(reciever))
    {
        m_updateReceivers--;
        GT_DEBUG
                (
                QString("Data reciever `%1` disconnected from `%2` GPS. Total: %3")
                     .arg(reciever->objectName())
                     .arg(name())
                     .arg(m_updateReceivers)
                );
        return true;
    }
    return false;
}

}


