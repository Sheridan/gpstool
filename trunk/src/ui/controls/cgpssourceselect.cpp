#include "cgpssourceselect.h"
#include "st.h"
namespace ui
{
namespace controls
{

#define DEF_TEXT QString("...")
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsSourceSelect::CGpsSourceSelect(QWidget *parent) :
    QToolButton(parent)
{
    setObjectName("GPS source selector");
    m_selectedId = 0;
    m_menu = new QMenu(this);
    setText(DEF_TEXT);
    setPopupMode(QToolButton::InstantPopup);
    setMenu(m_menu);
    GT_GPS_MANAGER->connectSourceUpdates(this,
                                         SLOT(appendGpsSource(const gps::TGpsSourceId &)),
                                         SLOT(removeGpsSource(const gps::TGpsSourceId &)),
                                         SLOT(updateSelected(const gps::TGpsSourceId &)));
    foreach(gps::TGpsSourceId id, GT_GPS_MANAGER->ids())
    {
        appendGpsSource(id);
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsSourceSelect::~CGpsSourceSelect()
{
    GT_GPS_MANAGER->disconnectSourceUpdates(this);
    delete m_menu;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsSourceSelect::appendGpsSource(const gps::TGpsSourceId &id)
{
    if(!m_gpsActions.contains(id))
    {
        CGpsSourceSelectAction *a = new CGpsSourceSelectAction(GT_GPS_MANAGER->source(id), m_menu);
        m_menu->addAction(a);
        m_gpsActions[id] = a;
        connect(a, SIGNAL(selected(const gps::TGpsSourceId &)), this, SLOT(setSelected(const gps::TGpsSourceId &)));
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsSourceSelect::removeGpsSource(const gps::TGpsSourceId &id)
{
    CGpsSourceSelectAction *a = m_gpsActions.value(id);
    m_menu->removeAction(a);
    m_gpsActions.remove(id);
    delete a;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsSourceSelect::updateSelected(const gps::TGpsSourceId &id)
{
    m_selectedId = id;
    setText(GT_GPS_MANAGER->source(id)->name());
}
// --------------------------------------------------------------------------------------------------------------------------------------
bool CGpsSourceSelect::isEmpty()
{
    return m_selectedId == 0;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsSourceSelect::setSelected(const gps::TGpsSourceId & id)
{
    updateSelected(id);
    emit selected(m_selectedId);
}

}
}
