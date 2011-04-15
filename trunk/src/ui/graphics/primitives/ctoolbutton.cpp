#include "ctoolbutton.h"
#include "gtdebug.h"
#include <QCursor>

namespace ui
{
namespace graphics
{
namespace primitive
{
// --------------------------------------------------------------------------------------------------------------------------------------
CToolButton::CToolButton(const QString & pixmapFile, QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(QPixmap(pixmapFile), parent)
{
    setCursor(Qt::PointingHandCursor);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CToolButton::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit clicked ();
    }
    else
    {
        event->ignore();
        QGraphicsPixmapItem::mousePressEvent(event);
    }
}

}
}
}
