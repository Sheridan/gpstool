#include "cgpsinfotext.h"
#include "st.h"
namespace ui
{
namespace graphics
{
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsInfoText::CGpsInfoText(gps::CGpsSource *gpssrc, const QString & caption, tools::TId iid)
    : CGpsInfoItem(gpssrc, iid), ui::graphics::primitive::window::CClientText()
{
    setClientTitle(caption);
    connectGpsData();
}
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsInfoText::~CGpsInfoText()
{
    disconnectGpsData();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsInfoText::loadFromConfig(const QString & section)
{
    QFont fnt;
    fnt.fromString(GT_OPTIONS_WINDOWS_ITEMS->getSectionValue(section, "font", GT_APPLICATION->font().toString()).toString());
    setFont(fnt);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsInfoText::saveToConfig(const QString & section)
{
    GT_OPTIONS_WINDOWS_ITEMS->setSectionValue(section, "font"    , font().toString());
    GT_OPTIONS_WINDOWS_ITEMS->setSectionValue(section, "texttype", textType       ());
}
}
}
