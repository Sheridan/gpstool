#ifndef CICONSELECT_H
#define CICONSELECT_H

#include <QToolButton>
namespace ui
{
namespace controls
{

class CIconSelect : public QToolButton
{
    Q_OBJECT
public: // ####################################################
    CIconSelect(QWidget *parent = NULL);

private slots: // ####################################################
    void selectIcon();
};

}
}
#endif // CICONSELECT_H
