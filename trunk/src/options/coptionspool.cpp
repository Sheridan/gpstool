#include "coptionspool.h"
namespace options
{
// --------------------------------------------------------------------------------------------------------------------------------------
COptionsPool::COptionsPool() : QThread()
{
    m_optionsApplication = new COptionsApplication   ();
    m_optionsGps         = new COptionsGps           (m_optionsApplication);
    m_optionsWindowItems = new COptionsWindowItems   (m_optionsApplication);
}
// --------------------------------------------------------------------------------------------------------------------------------------
COptionsPool::~COptionsPool()
{
    delete m_optionsWindowItems;
    delete m_optionsGps;
    delete m_optionsApplication;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void COptionsPool::stop()
{
    quit();
    wait();
}

}
