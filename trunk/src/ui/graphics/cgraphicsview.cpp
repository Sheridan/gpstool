#include "cgraphicsview.h"
#include "cgraphicsscene.h"
#include "st.h"
#include "ctextitemadddialog.h"
namespace ui
{
namespace graphics
{
// --------------------------------------------------------------------------------------------------------------------------------------
CGraphicsView::CGraphicsView(QWidget * parent) : QGraphicsView(parent)
{
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    m_menu = new QMenu(this);
    QMenu *addMenu = m_menu->addMenu(tr("Add..."));
    addMenu->addAction(tr("Text item"), this, SLOT(addTextItemShowDialog()));
}
// --------------------------------------------------------------------------------------------------------------------------------------
CGraphicsView::~CGraphicsView()
{
    delete m_menu;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGraphicsView::contextMenuEvent ( QContextMenuEvent * event )
{
    if(scene())
    {
        m_menu->popup(mapToGlobal(event->pos()));
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGraphicsView::addTextItemShowDialog()
{
    ui::dialogs::CTextItemAddDialog dlg(static_cast<CGraphicsScene *>(scene()));
    dlg.exec();
}

}
}
