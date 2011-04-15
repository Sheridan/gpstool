#ifndef CTOOLBUTTON_H
#define CTOOLBUTTON_H
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QObject>

namespace ui
{
namespace graphics
{
namespace primitive
{

class CToolButton : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public: // ####################################################
    CToolButton(const QString & pixmapFile, QGraphicsItem *parent = NULL);

signals: // ####################################################
    void clicked();

private: // ####################################################
    void mousePressEvent(QGraphicsSceneMouseEvent * event);

};

}
}
}
#endif // CTOOLBUTTON_H
