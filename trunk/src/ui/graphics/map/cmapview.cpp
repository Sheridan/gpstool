#include "cmapview.h"
namespace ui
{
namespace graphics
{
// --------------------------------------------------------------------------------------------------------------------------------------
CMapView::CMapView(QWidget * parent) : CGraphicsView(parent)
{
    m_scene = new CMapScene();
    setScene(m_scene);
}
// --------------------------------------------------------------------------------------------------------------------------------------
CMapView::~CMapView()
{
    delete m_scene;
}

}
}
