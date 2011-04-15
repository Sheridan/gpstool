#include "clogmessageshowdialog.h"
#include "ui_clogmessageshowdialog.h"
#include "uidefines.h"
namespace logging
{
namespace ui
{
// --------------------------------------------------------------------------------------------------------------------------------------
CLogMessageShowDialog::CLogMessageShowDialog(logging::SLogMessage &msg, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CLogMessageShowDialog)
{
    ui->setupUi(this);
    ui->lType->setText(LOGG_TYPE_DATA(msg.messageType, "", tr("Info"), tr("Warning"), tr("Error"), tr("Debug")));
    ui->lMessage->setText(msg.message);
    ui->lTime->setText(msg.time.toString("dd.MM.yyyy hh:mm:ss"));
    ui->tbAdvanced->setHtml(QString("<pre>%1</pre>").arg(msg.advanced));
    GT_RESTORE_DIALOG_STATE("logshow");
}
// --------------------------------------------------------------------------------------------------------------------------------------
CLogMessageShowDialog::~CLogMessageShowDialog()
{
    GT_SAVE_DIALOG_STATE("logshow");
    delete ui;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CLogMessageShowDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

}
}
