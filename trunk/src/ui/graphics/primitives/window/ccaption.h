#ifndef CCAPTION_H
#define CCAPTION_H
#include <QGraphicsObject>
#include <QGraphicsSimpleTextItem>
#include <QBrush>
#include <QPen>
#include <QLinearGradient>
#include "cwindowchild.h"
#include "ctoolbutton.h"
namespace ui
{
namespace graphics
{
namespace primitive
{
namespace window
{

class CWindow;

class CCaption : public QGraphicsObject, public CWindowChild
{
    Q_OBJECT
public: // ####################################################
    CCaption(const QString &text, CWindow *parent);
    virtual ~CCaption();
    QRectF boundingRect() const;
    const QSizeF & minSize() const { return m_minSize; }
    const QSizeF & size   () const { return m_size   ; }
    void setSize(const QSizeF & value);
    void setPos (qreal x, qreal y);
    void setPos (const QPointF &value) { setPos(value.x(), value.y()); };

private: // ####################################################
    ui::graphics::primitive::CToolButton    * m_tbClose;
    ui::graphics::primitive::CToolButton    * m_tbOptions;
    QGraphicsSimpleTextItem                 * m_caption;
    QRectF                                    m_boundingRect;
    QSizeF                                    m_minSize;
    QSizeF                                    m_size;

    QPen            m_pen;
    QLinearGradient m_gradient;

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = NULL);

private slots: // ####################################################
    void showClientOptions();
    void closeWindow();
};

}
}
}
}
#endif // CWINDOWCAPTION_H
