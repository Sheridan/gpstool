#include "cgpsdataupdateinterface.h"

namespace gps
{
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsDataUpdateInterface::CGpsDataUpdateInterface() : QObject(), CGpsDataUpdateInterfaseBase()
{
}
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsDataUpdateInterface::CGpsDataUpdateInterface(CGpsSource *gps) : QObject(), CGpsDataUpdateInterfaseBase(gps)
{
}
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsDataUpdateInterface::CGpsDataUpdateInterface(const TGpsSourceId &id) : QObject(), CGpsDataUpdateInterfaseBase(id)
{
}
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsDataUpdateInterface::~CGpsDataUpdateInterface()
{
}


}
