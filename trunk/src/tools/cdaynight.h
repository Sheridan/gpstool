#ifndef CDAYNIGHT_H
#define CDAYNIGHT_H

#include <QObject>
#include <QTimer>
#include <QTime>
#include "coptiontime.h"

class CDayNight : public QObject
{
    Q_OBJECT
public: // ####################################################
    enum EDNType
    {
        dnUnset,
        dnDay,
        dnNight
    };

public: // ####################################################
    CDayNight                       ();
    ~CDayNight                      ();
    CDayNight::EDNType  current     ();
    void                start       ();
    void                stop        ();
    void                setActive   (bool value);

private: // ####################################################
    CDayNight::EDNType        m_current;
    QTimer                  * m_timer;
    options::COptionTime    * m_dayStartTime;
    options::COptionTime    * m_nightStartTime;

private slots: // ####################################################
    void checkTime();

signals: // ####################################################
    void switchTo(CDayNight::EDNType type);
};

#endif // CDAYNIGHT_H
