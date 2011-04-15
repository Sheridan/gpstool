#ifndef CICONLABEL_H
#define CICONLABEL_H

#include <QLabel>
#include <QList>
#include <QPixmap>

namespace ui
{
namespace controls
{

class CIconLabel : public QLabel
{
    Q_OBJECT
public: // ####################################################
    CIconLabel(QWidget *parent);
protected: // ####################################################
    void loadAddIcon(const QString & file);
    void addIcon(QIcon icon);
    void setActiveIcon(const int &index);
    void setActiveIcon();
    void clear();
private: // ####################################################
    QList<QPixmap> m_icons;
    int m_activeIconIndex;
};

}
}
#endif // CICONLABEL_H
