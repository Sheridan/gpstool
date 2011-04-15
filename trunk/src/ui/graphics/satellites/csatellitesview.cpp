#include "csatellitesview.h"
#include "st.h"
namespace ui
{
namespace graphics
{
// --------------------------------------------------------------------------------------------------------------------------------------
CSatellitesView::CSatellitesView(QWidget * parent) : CGraphicsView(parent)
{
    m_scene = new CSatellitesScene();
    setScene(m_scene);
}
// --------------------------------------------------------------------------------------------------------------------------------------
CSatellitesView::~CSatellitesView()
{
    delete m_scene;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CSatellitesView::resizeEvent(QResizeEvent * event)
{
    Q_UNUSED(event);
    QPointF leftTop, rightBottom;
    if(viewport()->size().width() > viewport()->size().height())
    {
        leftTop = QPointF(viewport()->size().width()/2-viewport()->size().height()/2, 0);
        rightBottom = QPointF(viewport()->size().width()/2+viewport()->size().height()/2, viewport()->size().height());
    }
    if(viewport()->size().width() < viewport()->size().height())
    {
        leftTop = QPointF(0, viewport()->size().height()/2-viewport()->size().width()/2);
        rightBottom = QPointF(viewport()->size().width(), viewport()->size().height()/2+viewport()->size().width()/2);
    }
    if(viewport()->size().width() == viewport()->size().height())
    {
        leftTop = QPointF(0,0);
        rightBottom = QPointF(viewport()->size().width(), viewport()->size().height());
    }
    //GT_LOGGER->append(QString("[%1,%2] - [%3,%4]").arg(leftTop.x()).arg(leftTop.y()).arg(rightBottom.x()).arg(rightBottom.y()));
    QRectF srect(leftTop, rightBottom);
    m_scene->setSceneRect(srect);
}

}
}
