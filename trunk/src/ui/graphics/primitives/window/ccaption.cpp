#include "ccaption.h"
#include "resources.h"
#include "primitivesdefines.h"
#include "graphicsdefines.h"
#include "gtdebug.h"
#include "cwindow.h"
#include <QCursor>
#include <QBrush>
#include <QPen>
#include <QPainter>
#include "st.h"

namespace ui
{
namespace graphics
{
namespace primitive
{
namespace window
{

// --------------------------------------------------------------------------------------------------------------------------------------
CCaption::CCaption(const QString &text, CWindow *parent)
    : QGraphicsObject(), CWindowChild(parent)
{
    QFont captionFont = GT_APPLICATION->font();
    captionFont.setPointSizeF(captionFont.pointSizeF()/100*80);
    m_caption   = new QGraphicsSimpleTextItem             (text                        , this);
    m_tbClose   = new ui::graphics::primitive::CToolButton(GT_RESOURCE(gwindow,close)  , this);
    m_tbOptions = new ui::graphics::primitive::CToolButton(GT_RESOURCE(gwindow,options), this);
    m_caption->setFont(captionFont);


    m_gradient.setColorAt(0, Qt::lightGray);
    m_gradient.setColorAt(1, Qt::white    );

    m_pen = QPen(Qt::gray, GT_G_PRIMITIVE_BORDER_PEN_WIDTH, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    m_minSize = QSizeF
            (
            m_caption->boundingRect().width()
                + m_tbClose->boundingRect().width()
                + m_tbOptions->boundingRect().width()
                + GT_G_PRIMITIVE_BORDER_WIDTH * 4,
            qMax(m_caption->boundingRect().height(),
                 qMax(
                         m_tbClose->boundingRect().height(),
                         m_tbOptions->boundingRect().height()
                     )
                )
                + GT_G_PRIMITIVE_BORDER_WIDTH * 2
            );

    setSize(m_minSize);

    connect(m_tbClose  , SIGNAL(clicked()), this, SLOT(closeWindow())      );
    connect(m_tbOptions, SIGNAL(clicked()), this, SLOT(showClientOptions()));

    setCursor(Qt::OpenHandCursor                );
    setFlag  (QGraphicsItem::ItemIsMovable, true);

}
// --------------------------------------------------------------------------------------------------------------------------------------
CCaption::~CCaption()
{
    delete m_caption;
    delete m_tbClose;
    delete m_tbOptions;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CCaption::setSize(const QSizeF & value)
{
    prepareGeometryChange();
    m_size = value;
    m_caption->setPos(GT_G_PRIMITIVE_BORDER_WIDTH,
                      GT_G_PRIMITIVE_BORDER_WIDTH);

    m_tbClose->setPos(m_size.width() - GT_G_PRIMITIVE_BORDER_WIDTH - m_tbClose->boundingRect().width(),
                      GT_G_PRIMITIVE_BORDER_WIDTH);

    m_tbOptions->setPos(m_tbClose->pos().x() - m_tbOptions->boundingRect().width() - GT_G_PRIMITIVE_BORDER_WIDTH * 2,
                       GT_G_PRIMITIVE_BORDER_WIDTH);
}

// --------------------------------------------------------------------------------------------------------------------------------------
void CCaption::setPos(qreal x, qreal y)
{
    setFlag  (QGraphicsItem::ItemSendsGeometryChanges, false);
    QGraphicsObject::setPos(x,y);
    setFlag  (QGraphicsItem::ItemSendsGeometryChanges, true);
}
// --------------------------------------------------------------------------------------------------------------------------------------
QRectF CCaption::boundingRect() const
{
    return QRectF(QPointF(0,0), m_size);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CCaption::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    GT_GI_PAINTER_MODE(painter);
    painter->setPen(m_pen);
    m_gradient.setStart(boundingRect().topLeft());
    m_gradient.setFinalStop(boundingRect().bottomRight());
    painter->setBrush(QBrush(m_gradient));
    painter->drawRoundedRect(boundingRect(), 5.0, 5.0);
    GT_DEBUG_GI_DRAW_BORDERS(painter);
}
// --------------------------------------------------------------------------------------------------------------------------------------
QVariant CCaption::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch(change)
    {
    case QGraphicsItem::ItemPositionHasChanged:
        {
            gWindow()->setPos(pos().x() - GT_G_PRIMITIVE_BORDER_WIDTH, pos().y() - GT_G_PRIMITIVE_BORDER_WIDTH);
        }
        break;
    default: return QGraphicsItem::itemChange(change, value);
    }
    return QGraphicsItem::itemChange(change, value);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CCaption::showClientOptions()
{
    gWindow()->client()->showOptions();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CCaption::closeWindow()
{
    gWindow()->close();
}

}
}
}
}
