#include "cgraphicsitem.h"
#include "st.h"
#include <math.h>
#include <QTransform>
#include <QStyleOptionGraphicsItem>
#include "optionsdefines.h"
#include "graphicsdefines.h"

namespace ui
{
namespace graphics
{
// --------------------------------------------------------------------------------------------------------------------------------------
CGraphicsItem::CGraphicsItem(const EGraphicsItemType &giType, QGraphicsItem * parent) : QGraphicsObject(parent), m_itemType(giType)
{
    m_goodDataWait       = GT_OPTIONS_APP->requestOption(GT_OPTION_GOOD_DATA_WAIT    );
    m_animationDuration  = GT_OPTIONS_APP->requestOption(GT_OPTION_ANIMATION_DURATION);
    m_animationEnabled   = GT_OPTIONS_APP->requestOption(GT_OPTION_ANIMATION_ENABLED );
    connect(m_animationDuration, SIGNAL(changed(const int &)),   this, SLOT(setAnimationDuration(const int &)));
    connect(m_animationEnabled,	SIGNAL(changed(const bool &)),  this, SLOT(setAnimationEnabled(const bool &)));

    // animation
    m_angle              = 180;
    m_rotateAnimation    = NULL;
    m_sizeAnimation      = NULL;
    m_posAnimation       = NULL;
    setAnimationEnabled(m_animationEnabled->value());

    m_transparentColor.setAlpha(0);
    m_stdColor   = QColor("darkslategray");
    m_stdBrush   = QBrush(m_transparentColor, Qt::SolidPattern);
    m_stdPen     = QPen(QBrush(m_stdColor, Qt::SolidPattern), 0.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    m_stdFont    = QFont(GT_APPLICATION->font());
}
// --------------------------------------------------------------------------------------------------------------------------------------
CGraphicsItem::~CGraphicsItem()
{
    delete m_rotateAnimation;
    delete m_sizeAnimation;
    delete m_posAnimation;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGraphicsItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    Q_UNUSED(widget);
    if(painter->isActive())
    {
        painter->setClipRect( option->exposedRect );
        painter->setPen(m_stdPen);
        painter->setBrush(m_stdBrush);
        painter->setFont(m_stdFont);
        paint(painter);
        GT_DEBUG_GI_DRAW_BORDERS(painter);
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGraphicsItem::setSize(const QSizeF & value)
{
    if(m_size != value)
    {
        m_size = value;
        m_boundingRect = QRectF(QPointF(0,0), m_size);
        m_center = QPointF(m_size.width()/2, m_size.height()/2);
        //setCacheMode(QGraphicsItem::DeviceCoordinateCache, _size.toSize());
        prepareGeometryChange();
        boundingRectChanged();
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGraphicsItem::resize(const QSizeF & value)
{
    if(m_sizeAnimation)
    {
        m_sizeAnimation->setEndValue(value);
        m_sizeAnimation->start();
    }
    else
    {
        setSize(value);
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGraphicsItem::setAngle(const int & value)
{
    if(m_angle != value)
    {
        m_angle = value;
        prepareGeometryChange();
        setTransformOriginPoint(m_center);
        setRotation(-m_angle);
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGraphicsItem::rotate(const int & rotateAngle)
{
    if(m_rotateAnimation)
    {
        m_rotateAnimation->setEndValue(rotateAngle);
        m_rotateAnimation->start();
    }
    else
    {
        setAngle(rotateAngle);
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGraphicsItem::setPosition(const QPointF & position)
{
    if(m_posAnimation)
    {
        m_posAnimation->setEndValue(position);
        m_posAnimation->start();
    }
    else
    {
        setPos(position);
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGraphicsItem::setAnimationDuration(const int & msec)
{
    m_rotateAnimation->setDuration(msec);
    m_sizeAnimation->setDuration(msec);
    m_posAnimation->setDuration(msec);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGraphicsItem::setAnimationEnabled(const bool & enabled)
{
    if(enabled)
    {
        m_rotateAnimation = new QPropertyAnimation(this, "angle");
        m_rotateAnimation->setEasingCurve(QEasingCurve::OutQuint);
        m_sizeAnimation =  new QPropertyAnimation(this, "size");
        m_rotateAnimation->setEasingCurve(QEasingCurve::OutQuint);
        m_posAnimation =  new QPropertyAnimation(this, "position");
        m_posAnimation->setEasingCurve(QEasingCurve::OutQuint);
        setAnimationDuration(m_animationDuration->value());
    }
    else
    {
        delete m_rotateAnimation;
        delete m_sizeAnimation;
        delete m_posAnimation;
        m_rotateAnimation = NULL;
        m_sizeAnimation = NULL;
        m_posAnimation = NULL;
    }
}

}
}
