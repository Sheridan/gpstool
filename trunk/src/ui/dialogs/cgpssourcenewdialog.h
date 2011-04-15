#ifndef CGPSSOURCENEWDIALOG_H
#define CGPSSOURCENEWDIALOG_H

#include <QDialog>

namespace Ui {
    class CGpsSourceNewDialog;
}
namespace ui
{
namespace dialogs
{

class CGpsSourceNewDialog : public QDialog {
    Q_OBJECT
public: // ####################################################
    CGpsSourceNewDialog(QWidget *parent = 0);
    ~CGpsSourceNewDialog();

protected: // ####################################################
    void changeEvent(QEvent *e);

private: // ####################################################
    Ui::CGpsSourceNewDialog *ui;

private slots: // ####################################################
    void on_leGpsSourceName_textChanged(QString );
    void on_pbNext_clicked();
    void nextCheck();
};

}
}
#endif // CGPSSOURCENEWDIALOG_H
