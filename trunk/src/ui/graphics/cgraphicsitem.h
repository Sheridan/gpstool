#ifndef CGRAPHICSITEM_H
#define CGRAPHICSITEM_H
#include <QObject>
#include <QGraphicsObject>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QColor>
#include <QPropertyAnimation>
#include "coptionint.h"
#include "coptionbool.h"

namespace ui
{
namespace graphics
{

enum EGraphicsItemType
{
    gitSomething,
    gitTextItem
};

class CGraphicsItem : public QGraphicsObject
{
    Q_OBJECT
    // animation
    Q_PROPERTY(int angle READ angle WRITE setAngle);
    Q_PROPERTY(QSizeF size READ size WRITE setSize);
    Q_PROPERTY(QPointF position READ pos WRITE setPos);

public: // ####################################################
    CGraphicsItem(const EGraphicsItemType &giType, QGraphicsItem * parent = NULL);
    virtual ~CGraphicsItem();
    virtual QRectF          boundingRect()  const { return m_boundingRect;   }
    const EGraphicsItemType & itemType()    const { return m_itemType;       }
    const QPointF           & center()      const { return m_center;         }
    const int               & angle()       const { return m_angle;          }
    const QSizeF            & size()        const { return m_size;           }
    void setAngle   (const int & value          );
    void rotate     (const int & rotateAngle    );
    void setSize    (const QSizeF & value       );
    void resize     (const QSizeF & value       );
    void setPosition(const QPointF & position   );

private: // ####################################################
    int                       m_angle;
    QSizeF                    m_size;
    QPointF                   m_center;
    QRectF                    m_boundingRect;
    EGraphicsItemType         m_itemType;
    QPropertyAnimation      * m_rotateAnimation;
    QPropertyAnimation      * m_sizeAnimation;
    QPropertyAnimation      * m_posAnimation;
    options::COptionInt     * m_animationDuration;
    options::COptionBool    * m_animationEnabled;

    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);

protected: // ####################################################
    QPen                  m_stdPen;
    QBrush                m_stdBrush;
    QFont                 m_stdFont;
    QColor                m_stdColor;
    QColor                m_transparentColor;
    options::COptionInt * m_goodDataWait;
    virtual void paint(QPainter * painter) = 0;
    virtual void boundingRectChanged() {};

private slots: // ####################################################
    void setAnimationDuration(const int &msec);
    void setAnimationEnabled(const bool &enabled);
};

}
}
#endif
