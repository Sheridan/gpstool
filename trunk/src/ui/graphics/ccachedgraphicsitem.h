#ifndef CCACHEDGRAPHICSITEM_H
#define CCACHEDGRAPHICSITEM_H
#include "cgraphicsitem.h"
#include <QPixmap>

namespace ui
{
namespace graphics
{

class CCachedGraphicsItem : public CGraphicsItem
{
public: // ####################################################
    CCachedGraphicsItem(const EGraphicsItemType &giType, QGraphicsItem * parent = NULL);
    virtual ~CCachedGraphicsItem();

private: // ####################################################
    QPixmap *m_pixmap;
    void paint(QPainter * painter);

protected: // ####################################################
    virtual void paintToCache(QPainter * painter) = 0;
    void updateCache();
};

}
}
#endif // CCACHEDGRAPHICSITEM_H
