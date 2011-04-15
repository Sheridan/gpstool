#include "ccachedgraphicsitem.h"
#include <QGraphicsScene>
#include <QGraphicsView>
namespace ui
{
namespace graphics
{
// --------------------------------------------------------------------------------------------------------------------------------------
CCachedGraphicsItem::CCachedGraphicsItem(const EGraphicsItemType &giType, QGraphicsItem * parent) : CGraphicsItem(giType, parent)
{
    m_pixmap = NULL;
}
// --------------------------------------------------------------------------------------------------------------------------------------
CCachedGraphicsItem::~CCachedGraphicsItem()
{
    delete m_pixmap;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CCachedGraphicsItem::paint(QPainter * painter)
{
    if(m_pixmap)
    {
        painter->setRenderHints(QPainter::SmoothPixmapTransform, true);
        painter->drawPixmap(0,0,*m_pixmap);
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CCachedGraphicsItem::updateCache()
{
    if(isActive())
    {
        QPixmap *pixmap = new QPixmap(size().toSize());
        pixmap->fill(QColor(0,0,0,0));

        QPainter *painter = new QPainter(pixmap);
        painter->setBackgroundMode(Qt::TransparentMode);
        painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::HighQualityAntialiasing, true);
        painter->setPen(m_stdPen);
        painter->setBrush(m_stdBrush);
        painter->setFont(m_stdFont);

        paintToCache(painter);

        delete painter;
        QPixmap *tmp = m_pixmap;
        m_pixmap = pixmap;
        delete tmp;
        //update(boundingRect());
    }
}

}
}
