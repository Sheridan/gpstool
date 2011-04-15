#include "coptionsgps.h"
#include "st.h"
#include "optionsdefines.h"
namespace options
{
// --------------------------------------------------------------------------------------------------------------------------------------
COptionsGps::COptionsGps(COptionsApplication *appOptions)
    : COptions(QString("%1/gps.ini").arg(appOptions->requestOption(GT_OPTION_APPLICATION_HOME)->value()))
{}
// --------------------------------------------------------------------------------------------------------------------------------------
COptionsGps::~COptionsGps()
{}

}
