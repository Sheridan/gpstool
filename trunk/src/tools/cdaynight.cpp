#include "cdaynight.h"
#include "st.h"
#include "optionsdefines.h"
// --------------------------------------------------------------------------------------------------------------------------------------
CDayNight::CDayNight()
{
    m_current = CDayNight::dnUnset;
    m_timer = NULL;
    m_dayStartTime	= GT_OPTIONS_APP->requestOption(GT_OPTION_DAY_START);
    m_nightStartTime = GT_OPTIONS_APP->requestOption(GT_OPTION_NIGHT_START);
    connect(m_dayStartTime,   SIGNAL(changed()), this, SLOT(checkTime()));
    connect(m_nightStartTime, SIGNAL(changed()), this, SLOT(checkTime()));
    if(GT_OPTIONS_APP->requestOption(GT_OPTION_USESTYLES)->value())
    {
        start();
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
CDayNight::~CDayNight()
{
    stop();
}
// --------------------------------------------------------------------------------------------------------------------------------------
CDayNight::EDNType CDayNight::current()
{
    return m_current;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CDayNight::start()
{
    if(m_timer) return;

    m_timer = new QTimer(this);
    m_timer->setInterval(60000);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(checkTime()));
    checkTime();
    m_timer->start();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CDayNight::stop()
{
    if(m_timer)
    {
        m_timer->stop();
        delete m_timer;
        m_timer = NULL;
    }
    m_current = CDayNight::dnUnset;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CDayNight::setActive(bool value)
{
    if(value) start();
    else stop();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CDayNight::checkTime()
{
    QTime curr = QTime::currentTime();
    CDayNight::EDNType lastt = m_current;
    if(curr > m_dayStartTime->value() && curr < m_nightStartTime->value())
    {
        m_current = CDayNight::dnDay;
    }
    else
    {
        m_current = CDayNight::dnNight;
    }
    if (lastt != m_current)
    {
        emit switchTo(m_current);
    }
}

