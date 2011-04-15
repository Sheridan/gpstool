#ifndef CSIZEGRIP_H
#define CSIZEGRIP_H
#include "cwindowchild.h"
#include <QGraphicsPixmapItem>
#include <QPen>
#include <QBrush>
namespace ui
{
namespace graphics
{
namespace primitive
{
namespace window
{

class CWindow;

class CSizeGrip : public QGraphicsPixmapItem, public CWindowChild
{
public: // ####################################################
    CSizeGrip(CWindow *parent);
    void setPos(qreal x, qreal y);
    void setPos(const QPointF &value) { setPos(value.x(), value.y()); };
private: // ####################################################
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};

}
}
}
}
#endif // CSIZEGRIP_H
