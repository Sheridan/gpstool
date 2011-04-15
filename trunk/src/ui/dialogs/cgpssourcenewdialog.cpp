#include "cgpssourcenewdialog.h"
#include "ui_cgpssourcenewdialog.h"

#include "cgpsgpsdsourcedialog.h"
#include "uidefines.h"

namespace ui
{
namespace dialogs
{
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsSourceNewDialog::CGpsSourceNewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CGpsSourceNewDialog)
{
    ui->setupUi(this);
    GT_RESTORE_DIALOG_STATE("gpssrcnew");
    connect(ui->rbGPSd, SIGNAL(clicked()), this, SLOT(nextCheck()));
}
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsSourceNewDialog::~CGpsSourceNewDialog()
{
    GT_SAVE_DIALOG_STATE("gpssrcnew");
    delete ui;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsSourceNewDialog::changeEvent(QEvent *e)
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
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsSourceNewDialog::on_pbNext_clicked()
{
    hide();
    int result = 0;
    if(ui->rbGPSd->isChecked())
    {
        CGpsGpsdSourceDialog *dlg = new CGpsGpsdSourceDialog(ui->leGpsSourceName->text());
        result = dlg->exec();
        delete dlg;
    }
    done(result);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsSourceNewDialog::on_leGpsSourceName_textChanged(QString text)
{
    Q_UNUSED(text);
    nextCheck();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsSourceNewDialog::nextCheck()
{
    ui->pbNext->setEnabled(
            ! ui->leGpsSourceName->text().isEmpty() &&
                (
                    ui->rbGPSd->isChecked()
                )
            );
}


}
}
