#include "ctextview.h"
#include "st.h"
#include "ctextitemadddialog.h"
namespace ui
{
namespace graphics
{
// --------------------------------------------------------------------------------------------------------------------------------------
CTextView::CTextView(QWidget * parent) : CGraphicsView(parent)
{
    m_scene = new CTextScene();
    setScene(m_scene);
}
// --------------------------------------------------------------------------------------------------------------------------------------
CTextView::~CTextView()
{
    delete m_scene;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CTextView::resizeEvent(QResizeEvent * event)
{
    Q_UNUSED(event);
    m_scene->setSceneRect(viewport()->rect());
}


}
}
