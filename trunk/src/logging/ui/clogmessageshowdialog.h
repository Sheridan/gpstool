#ifndef CLOGMESSAGESHOWDIALOG_H
#define CLOGMESSAGESHOWDIALOG_H

#include <QDialog>
#include "clogger.h"

namespace Ui {
    class CLogMessageShowDialog;
}

namespace logging
{
namespace ui
{

class CLogMessageShowDialog : public QDialog
{
    Q_OBJECT
public: // ####################################################
    CLogMessageShowDialog(logging::SLogMessage &msg, QWidget *parent = 0);
    ~CLogMessageShowDialog();

protected: // ####################################################
    void changeEvent(QEvent *e);

private: // ####################################################
    Ui::CLogMessageShowDialog *ui;
};

}
}
#endif // CLOGMESSAGESHOWDIALOG_H
