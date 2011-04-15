#include "cdbiconlabel.h"
#include "icons.h"
#include "resources.h"
namespace ui
{
namespace controls
{
// --------------------------------------------------------------------------------------------------------------------------------------
CDbIconLabel::CDbIconLabel(data::db::CDatabase *db, QWidget *parent) : CIconLabel(parent)
{
    loadAddIcon (                                   GT_RESOURCE(icons,database)                               );  // 0 connected
    addIcon     (tools::icons::stratificateIcons(   GT_RESOURCE(icons,database), GT_RESOURCE(overlays,read ) )); // 1 read
    addIcon     (tools::icons::stratificateIcons(   GT_RESOURCE(icons,database), GT_RESOURCE(overlays,write) )); // 2 write
    addIcon     (tools::icons::setIconOpacity	(   GT_RESOURCE(icons,database), 0.5                         )); // 3 disconnected
    if(db->isOpen())
        setConnected();
    else
        setDisconnected();
    connect(db, SIGNAL(readStart())     , this, SLOT(setDbRead())       );
    connect(db, SIGNAL(writeStart())    , this, SLOT(setDbWrite())      );
    connect(db, SIGNAL(operationDone()) , this, SLOT(setConnected())    );
    connect(db, SIGNAL(disconnected())  , this, SLOT(setDisconnected()) );
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CDbIconLabel::setDbRead()
{
    setActiveIcon(1);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CDbIconLabel::setDbWrite()
{
    setActiveIcon(2);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CDbIconLabel::setConnected()
{
    setActiveIcon(0);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CDbIconLabel::setDisconnected()
{
    setActiveIcon(3);
}

}
}
