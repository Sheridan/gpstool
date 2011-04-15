#include "cclienttext.h"
#include "st.h"
#include "ctextwindowoptions.h"
#include <QFontMetricsF>
namespace ui
{
namespace graphics
{
namespace primitive
{
namespace window
{
// --------------------------------------------------------------------------------------------------------------------------------------
CClientText::CClientText() : CClient()
{
    m_font = GT_APPLICATION->font();
    checkSize();
    reset();
}
// --------------------------------------------------------------------------------------------------------------------------------------
CClientText::~CClientText()
{

}
// --------------------------------------------------------------------------------------------------------------------------------------
void CClientText::paint(QPainter *painter)
{
    painter->setFont(m_font);
    painter->drawText(boundingRect(), Qt::AlignCenter, m_text);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CClientText::setText(const QString &text)
{
    prepareGeometryChange();
    m_text = text;
    checkSize();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CClientText::reset()
{
    setText("NaN");
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CClientText::setFont(const QFont &font)
{
    prepareGeometryChange();
    m_font = font;
    checkSize();
}
// --------------------------------------------------------------------------------------------------------------------------------------
const QSizeF CClientText::correctMinSize(const QSizeF & value)
{
    Q_UNUSED(value);
    QFontMetricsF fm(m_font);
    return fm.size(Qt::TextSingleLine, m_text);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CClientText::showOptions()
{
    ui::dialogs::CTextWindowOptions dlg;
    dlg.setSelectedFont(m_font);
    if(dlg.exec() == QDialog::Accepted)
    {
        setFont(dlg.selectedFont());
    }
}

}
}
}
}
