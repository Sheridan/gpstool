#include "csingleton.h"

CSingleton * sm_instance = NULL;
// --------------------------------------------------------------------------------------------------------------------------------------
CSingleton::CSingleton()
{
    sm_instance = this;

    m_application                       = NULL;
    GT_SIMPLE_ST_NAME(logger)           = NULL;
    GT_SIMPLE_ST_NAME(optionsPool)      = NULL;
    GT_SIMPLE_ST_NAME(gpsSourceManager) = NULL;
    GT_SIMPLE_ST_NAME(dayNight)         = NULL;
    GT_SIMPLE_ST_NAME(gpsDatabase)      = NULL;
}
// --------------------------------------------------------------------------------------------------------------------------------------
CSingleton::~CSingleton()
{
    GT_SIMPLE_DELETE        (dayNight);
    GT_SIMPLE_THREAD_DELETE (gpsDatabase);
    GT_SIMPLE_THREAD_DELETE (gpsSourceManager);
    GT_SIMPLE_THREAD_DELETE (logger);
    GT_SIMPLE_THREAD_DELETE (optionsPool);
}
// --------------------------------------------------------------------------------------------------------------------------------------
CSingleton *CSingleton::instance()
{
    if(sm_instance) return sm_instance;
    return new CSingleton();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CSingleton::destroy()
{
    delete sm_instance;
    sm_instance = NULL;
}

