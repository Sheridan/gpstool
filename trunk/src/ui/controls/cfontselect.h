#ifndef CFONTSELECT_H
#define CFONTSELECT_H

#include <QWidget>
#include <QFont>

namespace Ui {
    class CFontSelect;
}
namespace ui
{
namespace controls
{

class CFontSelect : public QWidget
{
    Q_OBJECT
public: // ####################################################
    CFontSelect(QWidget *parent = 0);
    ~CFontSelect();
    const QFont & selectedFont();
    void setSelectedFont(const QFont & value);

protected: // ####################################################
    void changeEvent(QEvent *e);

private: // ####################################################
    Ui::CFontSelect *ui;

private slots: // ####################################################
    void on_tbSelectFont_clicked();
};

}
}
#endif // CFONTSELECT_H
