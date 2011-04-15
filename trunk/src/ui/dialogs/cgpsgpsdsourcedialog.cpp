#include "cgpsgpsdsourcedialog.h"
#include "ui_cgpsgpsdsourcedialog.h"

#include "st.h"
#include "uidefines.h"
#include "cgpsgpsdsource.h"
namespace ui
{
namespace dialogs
{
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsGpsdSourceDialog::CGpsGpsdSourceDialog(const QString & name, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CGpsGpsdSourceDialog)
{
    init();
    m_name = name;
    m_edit = false;
}
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsGpsdSourceDialog::CGpsGpsdSourceDialog(const gps::TGpsSourceId & id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CGpsGpsdSourceDialog)
{
    init();
    m_id = id;
    m_edit = true;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsGpsdSourceDialog::init()
{
    ui->setupUi(this);
    GT_RESTORE_DIALOG_STATE("gpsdsrcdlg");
    check();
    connect(ui->leHost,     SIGNAL(textChanged(QString)), this, SLOT(check()));
    connect(ui->lePort,     SIGNAL(textChanged(QString)), this, SLOT(check()));
    connect(ui->pbAccept,   SIGNAL(clicked())           , this, SLOT(accept()));
}
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsGpsdSourceDialog::~CGpsGpsdSourceDialog()
{
    GT_SAVE_DIALOG_STATE("gpsdsrcdlg");
    delete ui;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsGpsdSourceDialog::changeEvent(QEvent *e)
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
void CGpsGpsdSourceDialog::check()
{
    ui->pbAccept->setEnabled(!ui->leHost->text().isEmpty() && !ui->lePort->text().isEmpty());
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsGpsdSourceDialog::accept()
{
    if(m_edit)
    {
        static_cast<gps::CGpsGpsdSource *>(GT_GPS_MANAGER->source(m_id))->setHost(ui->leHost->text());
        static_cast<gps::CGpsGpsdSource *>(GT_GPS_MANAGER->source(m_id))->setPort(ui->lePort->text().toInt());
    }
    else
    {
        GT_GPS_MANAGER->add(m_name, ui->leHost->text(), ui->lePort->text().toInt());
    }
    QDialog::accept();
}

}
}
