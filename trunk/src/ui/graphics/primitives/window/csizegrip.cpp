#include "csizegrip.h"
#include "resources.h"
#include "primitivesdefines.h"
#include "graphicsdefines.h"
#include "cwindow.h"
#include <QPainter>
#include <QCursor>
#include <QPolygon>

namespace ui
{
namespace graphics
{
namespace primitive
{
namespace window
{
// --------------------------------------------------------------------------------------------------------------------------------------
CSizeGrip::CSizeGrip(CWindow *parent)
    : QGraphicsPixmapItem(QPixmap(GT_RESOURCE(gwindow,sizegrip))), CWindowChild(parent)
{
    setCursor(Qt::SizeAllCursor);
    setFlag(QGraphicsItem::ItemIsMovable, true);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CSizeGrip::setPos(qreal x, qreal y)
{
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, false);
    QGraphicsPixmapItem::setPos(x,y);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}
// --------------------------------------------------------------------------------------------------------------------------------------
QVariant CSizeGrip::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch(change)
    {
    case QGraphicsItem::ItemPositionChange:
        {
            QPointF nextPos =  value.toPointF();
            QPointF targetPos = pos() - nextPos;
            QSizeF resultSize = gWindow()->size() - QSizeF(targetPos.x(), targetPos.y());

            if(resultSize.width() < gWindow()->minSize().width())
            {
                resultSize.setWidth(gWindow()->minSize().width());
                nextPos.setX(pos().x());
            }
            if(resultSize.height() < gWindow()->minSize().height())
            {
                resultSize.setHeight(gWindow()->minSize().height());
                nextPos.setY(pos().y());
            }
            gWindow()->setSize(resultSize);
            return nextPos;
        }
        break;
    default: return QGraphicsItem::itemChange(change, value);
    }
    return QGraphicsItem::itemChange(change, value);
}

}
}
}
}
