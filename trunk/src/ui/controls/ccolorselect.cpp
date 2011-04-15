#include "ccolorselect.h"
#include "ui_ccolorselect.h"
#include <QColorDialog>
namespace ui
{
namespace controls
{
// --------------------------------------------------------------------------------------------------------------------------------------
CColorSelect::CColorSelect(const QRgb &color, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CColorSelect)
{
    ui->setupUi(this);
    m_color = color;
    setControlColor(m_color);
}
// --------------------------------------------------------------------------------------------------------------------------------------
CColorSelect::CColorSelect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CColorSelect)
{
    ui->setupUi(this);
    m_color = qRgba(0,0,0,0);
}
// --------------------------------------------------------------------------------------------------------------------------------------
CColorSelect::~CColorSelect()
{
    delete ui;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CColorSelect::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    case QEvent::Show:
        setControlColor(m_color);
        break;
    default:
        break;
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CColorSelect::setEnabled(bool value)
{
    ui->tbSelect->setVisible(value);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CColorSelect::setControlColor(const QRgb &rgba)
{
    ui->teColor->setHtml(QString("<body style='background-color:  rgba(%1,%2,%3,%4);'></body>")
            .arg(qRed(rgba))
            .arg(qGreen(rgba))
            .arg(qBlue(rgba))
            .arg(qAlpha(rgba)));
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CColorSelect::on_tbSelect_clicked()
{
    QColor dlgColor = QColorDialog::getColor(m_color, this);
    if(dlgColor.isValid())
    {
        setColor(dlgColor.rgba());
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CColorSelect::setColor(const QRgb &color)
{
    m_color = color;
    setControlColor(m_color);
    emit colorChanged(m_color);
}

}
}
