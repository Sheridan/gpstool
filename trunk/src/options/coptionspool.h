#ifndef COPTIONSPOOL_H
#define COPTIONSPOOL_H
#include <QThread>
#include "coptions.h"
#include "coptionsapplication.h"
#include "coptionsgps.h"
#include "coptionswindowitems.h"
namespace options
{

class COptionsPool : public QThread
{
    Q_OBJECT
public: // ####################################################
    COptionsPool();
    ~COptionsPool();

    COptionsApplication     * optionsApplication    () { return m_optionsApplication; }
    COptionsGps             * optionsGps            () { return m_optionsGps        ; }
    COptionsWindowItems     * optionsWindowItems    () { return m_optionsWindowItems; }

private: // ####################################################
    COptionsApplication     * m_optionsApplication;
    COptionsGps             * m_optionsGps;
    COptionsWindowItems     * m_optionsWindowItems;

public slots: // ####################################################
    void stop();
};

}
#endif // COPTIONSPOOL_H
