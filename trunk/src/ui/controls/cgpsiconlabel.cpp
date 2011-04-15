#include "cgpsiconlabel.h"
#include "icons.h"
#include "st.h"
#include "optionsdefines.h"
#include "resources.h"
#include <QRgb>
namespace ui
{
namespace controls
{
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsIconLabel::CGpsIconLabel(gps::CGpsSource * src, QWidget * parent) : CIconLabel(parent), gps::CGpsInterface(src)
{
    connectGps();
}
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsIconLabel::CGpsIconLabel(QWidget * parent) : CIconLabel(parent), gps::CGpsInterface()
{
    clear();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsIconLabel::connectGps(gps::CGpsSource * src)
{
    setGps(src);
    connectGps();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsIconLabel::connectGps()
{
    m_icon      = GT_OPTIONS_GPS->requestOption(GT_OPTION_GPS_ICON(gps()->id()));
    iconUpdated ();
    connect(m_icon, SIGNAL(changed()), this, SLOT(iconUpdated()), Qt::UniqueConnection);
    setToolTip  (gps()->name());
    connect(gps(), SIGNAL(statusChanging()),  this, SLOT(setStatusChanging()) , Qt::UniqueConnection);
    connect(gps(), SIGNAL(connectionError()), this, SLOT(setError())          , Qt::UniqueConnection);
    connect(gps(), SIGNAL(disconnected()),    this, SLOT(setDisconnected())   , Qt::UniqueConnection);
    connect(gps(), SIGNAL(connected()),       this, SLOT(setConnected())      , Qt::UniqueConnection);
    connect(gps(), SIGNAL(unusable()),        this, SLOT(setUnusable())       , Qt::UniqueConnection);
    connect(gps(), SIGNAL(usable()),          this, SLOT(setUsable())         , Qt::UniqueConnection);
    connect(gps(), SIGNAL(updateBegin()),     this, SLOT(setBeginUpdate())    , Qt::UniqueConnection);
    connect(gps(), SIGNAL(updateEnd()),       this, SLOT(setEndUpdate())      , Qt::UniqueConnection);
    if(gps()->isGpsConnected())
        setConnected();
    else
        setDisconnected();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsIconLabel::iconUpdated()
{
    clear();
    addIcon     (                                   m_icon->value()                                       ); // 0 connected
    addIcon     (tools::icons::setIconOpacity   (   m_icon->value(), 0.5                                 )); // 1 disconnected
    addIcon     (tools::icons::stratificateIcons(   m_icon->value(), GT_RESOURCE(overlays,read)          )); // 2 updating
    addIcon     (tools::icons::stratificateIcons(
                 tools::icons::setIconOpacity   (   m_icon->value(), 0.5                                  ),
                                                                     GT_RESOURCE(overlays,warning)       )); // 3 error
    addIcon     (tools::icons::stratificateIcons(   m_icon->value(), GT_RESOURCE(overlays,connectiong)   )); // 4 connecting
    setActiveIcon();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsIconLabel::setConnected()
{
    setActiveIcon(0);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsIconLabel::setDisconnected()
{
    setActiveIcon(1);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsIconLabel::setUsable()
{

}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsIconLabel::setUnusable()
{

}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsIconLabel::setError()
{
    setActiveIcon(3);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsIconLabel::setStatusChanging()
{
    setActiveIcon(4);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsIconLabel::setBeginUpdate()
{
    setActiveIcon(2);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsIconLabel::setEndUpdate()
{
    setConnected();
}
}
}
