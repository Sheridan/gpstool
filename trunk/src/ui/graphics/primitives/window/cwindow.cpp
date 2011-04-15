#include "cwindow.h"
#include "primitivesdefines.h"
#include "graphicsdefines.h"
#include "gtdebug.h"
#include <QGraphicsScene>
#include <QPainter>
namespace ui
{
namespace graphics
{
namespace primitive
{
namespace window
{
// --------------------------------------------------------------------------------------------------------------------------------------
CWindow::CWindow(CClient *client, QGraphicsScene *scene)
    : QGraphicsObject(), m_client(client), m_scene(scene)
{
    m_client->setGWindow(this);
    m_caption    = new CCaption (m_client->clientTitle(), this);
    m_sizeGrep   = new CSizeGrip(                         this);
    m_lineTop    = new QGraphicsLineItem();
    m_lineRight  = new QGraphicsLineItem();
    m_lineBottom = new QGraphicsLineItem();
    m_lineLeft   = new QGraphicsLineItem();

    QPen linePen(Qt::lightGray, GT_G_PRIMITIVE_BORDER_PEN_WIDTH, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
    m_lineTop   ->setPen(linePen);
    m_lineRight ->setPen(linePen);
    m_lineBottom->setPen(linePen);
    m_lineLeft  ->setPen(linePen);

    updateMinSize();
    setSize(m_minSize);
    m_scene->addItem(this        );
    m_scene->addItem(m_caption   );
    m_scene->addItem(m_sizeGrep  );
    m_scene->addItem(m_client    );
    m_scene->addItem(m_lineTop   );
    m_scene->addItem(m_lineRight );
    m_scene->addItem(m_lineBottom);
    m_scene->addItem(m_lineLeft  );
    setElementsVisible  (false);
    setAcceptHoverEvents(true );
}
// --------------------------------------------------------------------------------------------------------------------------------------
CWindow::~CWindow()
{
    m_scene->removeItem(this        );
    m_scene->removeItem(m_caption   );
    m_scene->removeItem(m_sizeGrep  );
    m_scene->removeItem(m_client    );
    m_scene->removeItem(m_lineTop   );
    m_scene->removeItem(m_lineRight );
    m_scene->removeItem(m_lineBottom);
    m_scene->removeItem(m_lineLeft  );
    delete m_caption   ;
    delete m_sizeGrep  ;
    delete m_lineTop   ;
    delete m_lineRight ;
    delete m_lineBottom;
    delete m_lineLeft  ;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CWindow::setPos(qreal x, qreal y)
{
    QGraphicsItem::setPos(x,y);
    m_caption ->setPos(pos().x() + GT_G_PRIMITIVE_BORDER_WIDTH, pos().y() + GT_G_PRIMITIVE_BORDER_WIDTH);
    m_client  ->setPos(pos().x() + GT_G_PRIMITIVE_BORDER_WIDTH, pos().y() + m_caption->boundingRect().height() + GT_G_PRIMITIVE_BORDER_WIDTH * 2);
    m_sizeGrep->setPos(pos().x() + m_size.width()  - m_sizeGrep->boundingRect().width()  - GT_G_PRIMITIVE_BORDER_WIDTH,
                       pos().y() + m_size.height() - m_sizeGrep->boundingRect().height() - GT_G_PRIMITIVE_BORDER_WIDTH);
    updateLines();

}
// --------------------------------------------------------------------------------------------------------------------------------------
void CWindow::setSize(const QSizeF & value)
{
    prepareGeometryChange();
    m_size = value;
    m_caption->setSize(QSizeF(value.width() - GT_G_PRIMITIVE_BORDER_WIDTH * 2, m_caption->size().height()));
    m_sizeGrep->setPos(pos().x() + m_size.width()  - m_sizeGrep->boundingRect().width()  - GT_G_PRIMITIVE_BORDER_WIDTH,
                       pos().y() + m_size.height() - m_sizeGrep->boundingRect().height() - GT_G_PRIMITIVE_BORDER_WIDTH);
    m_client->setSize(QSizeF(m_size.width() - GT_G_PRIMITIVE_BORDER_WIDTH * 2,
                             m_size.height() - m_caption->size().height() - GT_G_PRIMITIVE_BORDER_WIDTH * 3));
    updateLines();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CWindow::updateLines()
{
    qreal divisor = (m_size.width() + m_size.height()) / 2 / GT_G_PRIVITIVE_BORDER_SPACE_DIVISOR;
    m_lineTop->setLine      (pos().x() + m_size.width() / divisor,
                             pos().y() + m_caption->boundingRect().height() + GT_G_PRIMITIVE_BORDER_WIDTH,
                             pos().x() - m_size.width() / divisor + m_size.width(),
                             pos().y() + m_caption->boundingRect().height() + GT_G_PRIMITIVE_BORDER_WIDTH);
    m_lineRight->setLine    (pos().x() + m_size.width(),
                             pos().y() + m_caption->boundingRect().height() + GT_G_PRIMITIVE_BORDER_WIDTH * 2 + m_client->boundingRect().height() / divisor,
                             pos().x() + m_size.width(),
                             pos().y() + m_caption->boundingRect().height() + GT_G_PRIMITIVE_BORDER_WIDTH * 2 - m_client->boundingRect().height() / divisor + m_client->boundingRect().height());
    m_lineBottom->setLine   (pos().x() + m_size.width() / divisor,
                             pos().y() + m_size.height() + GT_G_PRIMITIVE_BORDER_WIDTH,
                             pos().x() - m_size.width() / divisor + m_size.width(),
                             pos().y() + m_size.height() + GT_G_PRIMITIVE_BORDER_WIDTH);
    m_lineLeft->setLine     (pos().x(),
                             pos().y() + m_caption->boundingRect().height() + GT_G_PRIMITIVE_BORDER_WIDTH * 2 + m_client->boundingRect().height() / divisor,
                             pos().x(),
                             pos().y() + m_caption->boundingRect().height() + GT_G_PRIMITIVE_BORDER_WIDTH * 2 - m_client->boundingRect().height() / divisor + m_client->boundingRect().height());
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CWindow::updateMinSize()
{
    m_minSize = QSizeF(qMax(m_caption->minSize().width (),  m_client->minSize().width()) + GT_G_PRIMITIVE_BORDER_WIDTH * 2,
                            m_caption->minSize().height() + m_client->minSize().height() + GT_G_PRIMITIVE_BORDER_WIDTH * 3);
}
// --------------------------------------------------------------------------------------------------------------------------------------
QRectF CWindow::boundingRect() const
{
    return QRectF(QPointF(0,0), m_size);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CWindow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    GT_GI_PAINTER_MODE(painter);
    GT_DEBUG_GI_DRAW_BORDERS(painter);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CWindow::close()
{
    emit closeRequest(this);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CWindow::setElementsVisible(bool vis)
{
    m_caption ->setVisible( vis);
    m_sizeGrep->setVisible( vis);
    m_lineTop ->setVisible(!vis);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CWindow::hoverEnterEvent(QGraphicsSceneHoverEvent * event)
{
    Q_UNUSED(event);
    setElementsVisible(true);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CWindow::hoverLeaveEvent(QGraphicsSceneHoverEvent * event)
{
    Q_UNUSED(event);
    setElementsVisible(false);
}


}
}
}
}
