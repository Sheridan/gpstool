#ifndef CWINITEM_H
#define CWINITEM_H
#include <QObject>
#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QMap>
#include "ccaption.h"
#include "csizegrip.h"
#include "cclient.h"
#include "cid.h"

namespace ui
{
namespace graphics
{
namespace primitive
{
namespace window
{

class CWindow : public QGraphicsObject
{
    Q_OBJECT
public: // ####################################################
    CWindow(CClient *client, QGraphicsScene *scene);
    ~CWindow();
    void setPos (const QPointF &value) { setPos(value.x(), value.y()); };
    void setPos (qreal x, qreal y    );
    void setSize(const QSizeF & value);
    CCaption        * caption () { return m_caption ; }
    CSizeGrip       * sizeGrep() { return m_sizeGrep; }
    CClient         * client  () { return m_client  ; }
    const QSizeF & size       () { return m_size    ; }
    const QSizeF & minSize    () { return m_minSize ; }
    QRectF boundingRect() const;
    void close         ()      ;
    void updateMinSize ()      ;

private: // ####################################################
    CCaption          * m_caption;
    CSizeGrip         * m_sizeGrep;
    CClient           * m_client;
    QGraphicsScene    * m_scene;
    QSizeF              m_size;
    QSizeF              m_minSize;
    QGraphicsLineItem * m_lineTop;
    QGraphicsLineItem * m_lineRight;
    QGraphicsLineItem * m_lineBottom;
    QGraphicsLineItem * m_lineLeft;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = NULL);
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
    void setElementsVisible(bool vis);
    void updateLines();
signals: // ####################################################
    void closeRequest(ui::graphics::primitive::window::CWindow *wnd);

};

typedef QMap<tools::TId, CWindow *> TWindowsMap;

}
}
}
}
#endif // CWINITEM_H
