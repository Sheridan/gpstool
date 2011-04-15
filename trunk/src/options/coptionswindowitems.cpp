#include "coptionswindowitems.h"
#include "optionsdefines.h"

namespace options
{
// --------------------------------------------------------------------------------------------------------------------------------------
COptionsWindowItems::COptionsWindowItems(COptionsApplication *appOptions)
    : COptions(QString("%1/windowitems.ini").arg(appOptions->requestOption(GT_OPTION_APPLICATION_HOME)->value()))
{}
// --------------------------------------------------------------------------------------------------------------------------------------
COptionsWindowItems::~COptionsWindowItems()
{}

}
