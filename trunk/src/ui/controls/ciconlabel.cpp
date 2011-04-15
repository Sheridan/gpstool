#include "ciconlabel.h"
#include <QIcon>
namespace ui
{
namespace controls
{
// --------------------------------------------------------------------------------------------------------------------------------------
CIconLabel::CIconLabel(QWidget *parent) : QLabel(parent)
{
    resize(16,16);
    setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    m_activeIconIndex = 0;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CIconLabel::loadAddIcon(const QString & file)
{
    addIcon(QIcon(file));
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CIconLabel::addIcon(QIcon icon)
{
    m_icons.append(icon.pixmap(16));
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CIconLabel::setActiveIcon(const int &index)
{
    m_activeIconIndex = index;
    setActiveIcon();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CIconLabel::setActiveIcon()
{
    setPixmap(m_icons.at(m_activeIconIndex));
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CIconLabel::clear()
{
    setPixmap(QPixmap(16,16));
    m_icons.clear();
}

}
}
