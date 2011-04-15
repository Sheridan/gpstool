#ifndef CTEXTWINDOWOPTIONS_H
#define CTEXTWINDOWOPTIONS_H

#include <QDialog>

namespace Ui {
    class CTextWindowOptions;
}
namespace ui
{
namespace dialogs
{

class CTextWindowOptions : public QDialog {
    Q_OBJECT
public: // ####################################################
    CTextWindowOptions(QWidget *parent = 0);
    ~CTextWindowOptions();
    void setSelectedFont(const QFont & value);
    const QFont & selectedFont();

protected: // ####################################################
    void changeEvent(QEvent *e);

private: // ####################################################
    Ui::CTextWindowOptions *ui;
};

}
}
#endif // CTEXTWINDOWOPTIONS_H
