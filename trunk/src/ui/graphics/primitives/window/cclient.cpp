#include "cclient.h"
#include "graphicsdefines.h"
#include "primitivesdefines.h"
#include "cwindow.h"

namespace ui
{
namespace graphics
{
namespace primitive
{
namespace window
{
// --------------------------------------------------------------------------------------------------------------------------------------
CClient::CClient() : QGraphicsItem(), CWindowChild()
{
}
// --------------------------------------------------------------------------------------------------------------------------------------
CClient::~CClient()
{
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CClient::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    GT_GI_PAINTER_MODE(painter);
    paint(painter);
    GT_DEBUG_GI_DRAW_BORDERS(painter);
}
// --------------------------------------------------------------------------------------------------------------------------------------
QRectF CClient::boundingRect() const
{
    return QRectF(QPointF(0,0), m_size);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CClient::setSize (const QSizeF & value)
{
    prepareGeometryChange();
    m_size = value;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CClient::setMinSize(const QSizeF & value)
{
    QSizeF correctedMinSize = correctMinSize(value);
    if(m_minSize .width() != correctedMinSize .width() ||
       m_minSize.height() != correctedMinSize.height())
    {
        m_minSize = correctedMinSize;
        if(gWindow()) { gWindow()->updateMinSize(); }
        if(m_size.width() < m_minSize.width() ||
           m_size.height() < m_minSize.height())
        {
            setSize(m_minSize);
        }
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CClient::checkSize()
{
    QSizeF miSize = correctMinSize(m_minSize);
    if(miSize != m_minSize)
    {
        setMinSize(m_minSize);
    }
}

}
}
}
}
