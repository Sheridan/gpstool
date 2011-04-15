#include "ctextwindowoptions.h"
#include "ui_ctextwindowoptions.h"
namespace ui
{
namespace dialogs
{
// --------------------------------------------------------------------------------------------------------------------------------------
CTextWindowOptions::CTextWindowOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CTextWindowOptions)
{
    ui->setupUi(this);
}
// --------------------------------------------------------------------------------------------------------------------------------------
CTextWindowOptions::~CTextWindowOptions()
{
    delete ui;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CTextWindowOptions::changeEvent(QEvent *e)
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
void CTextWindowOptions::setSelectedFont(const QFont & value)
{
    ui->pwFontSelect->setSelectedFont(value);
}
// --------------------------------------------------------------------------------------------------------------------------------------
const QFont & CTextWindowOptions::selectedFont()
{
    return ui->pwFontSelect->selectedFont();
}

}
}
