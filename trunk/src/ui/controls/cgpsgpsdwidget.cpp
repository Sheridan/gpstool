#include "cgpsgpsdwidget.h"
#include "ui_cgpsgpsdwidget.h"
#include <QMessageBox>

#include "st.h"

namespace ui
{
namespace controls
{
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsGpsdWidget::CGpsGpsdWidget(gps::CGpsGpsdSource *src, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CGpsGpsdWidget),
    m_src(src)
{
    ui->setupUi(this);
    connect(m_src, SIGNAL(connected(bool)), this, SLOT(sourceConnected(bool)));
    setEditMode(false);
    ui->gbOptions->setVisible(false);
    fillValues();
}
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsGpsdWidget::~CGpsGpsdWidget()
{
    delete ui;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsGpsdWidget::changeEvent(QEvent *e)
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
void CGpsGpsdWidget::fillValues()
{
    if(m_src)
    {
        ui->leHost->setText(m_src->host());
        ui->leName->setText(m_src->name());
        ui->lePort->setText(QString::number(m_src->port()));
        ui->leUpdatePeriod->setText(QString::number(m_src->updatePeriod()));
        ui->cbAutoconnect->setChecked(m_src->autoConnect());
        ui->pwColor->setColor(m_src->color());
        ui->lName->setText(m_src->name());
        ui->lName->setStyleSheet(QString("color:  rgba(%1,%2,%3,%4);")
                                 .arg(qRed(m_src->color()))
                                 .arg(qGreen(m_src->color()))
                                 .arg(qBlue(m_src->color()))
                                 .arg(qAlpha(m_src->color())));
        ui->gbOptions->setTitle(tr("Options of '%1' GPS source").arg(m_src->name()));
        ui->pwIconSelect->setIcon(m_src->icon());
        ui->lStatus->connectGps(m_src);
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsGpsdWidget::setEditMode(bool value)
{
    ui->leHost          ->setEnabled(value);
    ui->lePort          ->setEnabled(value);
    ui->leName          ->setEnabled(value);
    ui->pwIconSelect    ->setEnabled(value);
    ui->leUpdatePeriod  ->setEnabled(value);
    ui->pwColor         ->setEnabled(value);
    ui->cbAutoconnect   ->setEnabled(value);
    ui->tbApply         ->setVisible(value);
    ui->tbCancel        ->setVisible(value);
    ui->tbEdit          ->setVisible(!value);
    ui->tbDelete        ->setVisible(!value);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsGpsdWidget::on_tbEdit_clicked()
{
    setEditMode(true);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsGpsdWidget::on_tbApply_clicked()
{
    setEditMode(false);
    bool isconnected = m_src->isGpsConnected();
    if(isconnected)  m_src->disconnectGps();

    if(ui->cbAutoconnect->isChecked()       != m_src->autoConnect())     m_src->setAutoConnect    (ui->cbAutoconnect->isChecked()     );
    if(ui->pwColor->selectedColor()         != m_src->color())           m_src->setColor          (ui->pwColor->selectedColor()       );
    if(ui->leHost->text()                   != m_src->host())            m_src->setHost           (ui->leHost->text()                 );
    if(ui->lePort->text().toInt()           != m_src->port())            m_src->setPort           (ui->lePort->text().toInt()         );
    if(ui->leUpdatePeriod->text().toInt()   != m_src->updatePeriod())    m_src->setUpdatePeriod   (ui->leUpdatePeriod->text().toInt() );
    if(ui->pwIconSelect->icon().cacheKey()  != m_src->icon().cacheKey()) m_src->setIcon           (ui->pwIconSelect->icon()           );
    if(ui->leName->text()                   != m_src->name())            m_src->setName           (ui->leName->text()                 );

    if(isconnected) m_src->connectGps();
    fillValues();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsGpsdWidget::on_tbCancel_clicked()
{
    setEditMode(false);
    fillValues();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsGpsdWidget::on_pbConnect_clicked()
{
    if(m_src->isGpsConnected())
        m_src->disconnectGps();
    else
        m_src->connectGps();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsGpsdWidget::sourceConnected(bool connected)
{
    ui->pbConnect->setText(connected ? tr("Disconnect") : tr("Connect"));
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsGpsdWidget::on_tbDelete_clicked()
{
    GT_GPS_MANAGER->remove(m_src->id());
    delete this;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsGpsdWidget::on_tbInfo_clicked()
{
    QMessageBox msgBox	(
                    QMessageBox::Information,
                    tr("GPS info"),
                    m_src->gpsInfo()
                        );
    msgBox.exec();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsGpsdWidget::on_pbShowAdvanced_clicked()
{
    ui->pbShowAdvanced->setChecked(ui->pbShowAdvanced->isChecked());
    ui->gbOptions->setVisible(ui->pbShowAdvanced->isChecked());
}

}
}
