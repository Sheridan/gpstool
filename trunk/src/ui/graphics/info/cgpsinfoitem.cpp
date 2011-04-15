#include "cgpsinfoitem.h"
#include "optionsdefines.h"
#include "cgraphicsscene.h"
#include "st.h"
namespace ui
{
namespace graphics
{

CGpsInfoItem::CGpsInfoItem(gps::CGpsSource *gpssrc, tools::TId iid)
    : tools::CId(iid), gps::CGpsDataUpdateInterface(gpssrc)
{
}
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsInfoItem::~CGpsInfoItem()
{
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsInfoItem::load(const QString & section)
{
    loadFromConfig(section);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsInfoItem::save(const QString & section)
{
    GT_OPTIONS_WINDOWS_ITEMS->setSectionValue(section, "type", infoType());
    GT_OPTIONS_WINDOWS_ITEMS->setSectionValue(section, "gps", gps()->id());
    saveToConfig(section);
}

}
}
