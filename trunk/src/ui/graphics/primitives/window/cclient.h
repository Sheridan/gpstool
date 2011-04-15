#ifndef CCLIENT_H
#define CCLIENT_H
#include <QGraphicsItem>
#include <QPainter>
#include "cwindowchild.h"

namespace ui
{
namespace graphics
{
namespace primitive
{
namespace window
{

class CClient : public QGraphicsItem, public CWindowChild
{

public: // ####################################################
    CClient();
    virtual ~CClient();
    QRectF boundingRect() const;
    const QSizeF & size   () { return m_size   ; }
    const QSizeF & minSize() { return m_minSize; }
    void setSize   (const QSizeF & value);
    void setMinSize(const QSizeF & value);
    virtual void showOptions() = 0;
    virtual void reset() = 0;
    void setClientTitle(const QString & value) { m_clientTitle = value; }
    const QString &clientTitle() { return m_clientTitle; }

protected: // ####################################################
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = NULL);
    virtual void paint(QPainter *painter) = 0;
    virtual const QSizeF correctMinSize(const QSizeF & value) = 0;
    void checkSize();

private: // ####################################################
    QSizeF m_size;
    QSizeF m_minSize;
    QString m_clientTitle;
};

}
}
}
}
#endif // CCLIENT_H
