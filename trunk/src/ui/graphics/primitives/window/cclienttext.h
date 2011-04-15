#ifndef CCLIENTTEXT_H
#define CCLIENTTEXT_H
#include "cclient.h"
#include <QFont>

namespace ui
{
namespace graphics
{
namespace primitive
{
namespace window
{

class CClientText : public CClient
{
public: // ####################################################
    CClientText();
    ~CClientText();
    void setText(const QString &text);
    void reset();
    void setFont(const QFont &font);
    void showOptions();
    const QFont & font() const { return m_font; }

private: // ####################################################
    QString m_text;
    QFont   m_font;
    void paint(QPainter *painter);
    const QSizeF correctMinSize(const QSizeF & value);

};

}
}
}
}
#endif // CCLIENTTEXT_H
