#include "cfontselect.h"
#include "ui_cfontselect.h"
#include <QFontDialog>
namespace ui
{
namespace controls
{
// --------------------------------------------------------------------------------------------------------------------------------------
CFontSelect::CFontSelect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CFontSelect)
{
    ui->setupUi(this);
}
// --------------------------------------------------------------------------------------------------------------------------------------
CFontSelect::~CFontSelect()
{
    delete ui;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CFontSelect::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
const QFont & CFontSelect::selectedFont()
{
    return ui->lFont->font();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CFontSelect::setSelectedFont(const QFont & value)
{
    ui->lFont->setFont(value);
    ui->lFont->setText(QString("%1, %2").arg(value.family()).arg(value.pointSize()));
}
// --------------------------------------------------------------------------------------------------------------------------------------
void ui::controls::CFontSelect::on_tbSelectFont_clicked()
{
    bool ok;
    QFont f = QFontDialog::getFont(&ok, selectedFont(), this);
    if (ok)
    {
        setSelectedFont(f);
    }

}

}
}
