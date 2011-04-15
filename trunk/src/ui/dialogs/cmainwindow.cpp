#include "cmainwindow.h"
#include "ui_cmainwindow.h"

#include "st.h"
#include "uidefines.h"
#include "optionsdefines.h"

#include <QFileDialog>


namespace ui
{
namespace dialogs
{
// --------------------------------------------------------------------------------------------------------------------------------------
CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow)
{
    ui->setupUi(this);
    GT_RESTORE_DIALOG_STATE("main");
    ui->leApplicatioPath->setText       (GT_OPTIONS_APP->requestOption(GT_OPTION_APPLICATION_HOME         )->value());
    ui->sliderZoom->setValue            (GT_OPTIONS_APP->requestOption(GT_OPTION_MAPZOOM                  )->value());
    ui->sbSatelliteSignalWait->setValue (GT_OPTIONS_APP->requestOption(GT_OPTION_SATELLITE_SIGNAL_WAIT    )->value());
    ui->sbGoodDataWait->setValue        (GT_OPTIONS_APP->requestOption(GT_OPTION_GOOD_DATA_WAIT           )->value());
    ui->teDayStartTime->setTime         (GT_OPTIONS_APP->requestOption(GT_OPTION_DAY_START                )->value());
    ui->teNightStartTime->setTime       (GT_OPTIONS_APP->requestOption(GT_OPTION_NIGHT_START              )->value());
    ui->pteMainStyle->setPlainText      (GT_OPTIONS_APP->requestOption(GT_OPTION_MAIN_STYLESHEET          )->value().text);
    ui->pteDayStyle->setPlainText       (GT_OPTIONS_APP->requestOption(GT_OPTION_DAY_STYLESHEET           )->value().text);
    ui->pteNightStyle->setPlainText     (GT_OPTIONS_APP->requestOption(GT_OPTION_NIGHT_STYLESHEET         )->value().text);
    ui->cbUseStyles->setChecked         (GT_OPTIONS_APP->requestOption(GT_OPTION_USESTYLES                )->value());
    ui->cbUseAnimation->setChecked      (GT_OPTIONS_APP->requestOption(GT_OPTION_ANIMATION_ENABLED        )->value());
    ui->cbSStoreSatellites->setChecked  (GT_OPTIONS_APP->requestOption(GT_OPTION_STORE_SATELLITES         )->value());
    ui->leDBFile->setText               (GT_DATABASE_GPS->dbFile());
    ui->leAnimationDuration->setText    (QString::number(GT_OPTIONS_APP->requestOption(GT_OPTION_ANIMATION_DURATION)->value()));
}
// --------------------------------------------------------------------------------------------------------------------------------------
CMainWindow::~CMainWindow()
{
    GT_SAVE_DIALOG_STATE("main");
    delete ui;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CMainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CMainWindow::on_pbApplyStyles_clicked()
{
    GT_OPTIONS_APP->requestOption(GT_OPTION_MAIN_STYLESHEET   )->set(ui->pteMainStyle->toPlainText());
    GT_OPTIONS_APP->requestOption(GT_OPTION_DAY_STYLESHEET    )->set(ui->pteDayStyle->toPlainText());
    GT_OPTIONS_APP->requestOption(GT_OPTION_NIGHT_STYLESHEET  )->set(ui->pteNightStyle->toPlainText());
    GT_APPLICATION->refreshStyleSheet(GT_DAYNIGHT->current());
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CMainWindow::on_sliderZoom_valueChanged(int value)
{
    emit mapZoomChanged(value);
    ui->lZoomLevel->setText(QString("%1").arg(value));
    GT_OPTIONS_APP->requestOption(GT_OPTION_MAPZOOM)->set(value);
    GT_LOGGER->append(QString("Map zoom level changed to %1").arg(value));
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CMainWindow::on_teNightStartTime_timeChanged(QTime date)
{
    GT_OPTIONS_APP->requestOption(GT_OPTION_NIGHT_START)->set(date);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CMainWindow::on_teDayStartTime_timeChanged(QTime date)
{
    GT_OPTIONS_APP->requestOption(GT_OPTION_DAY_START)->set(date);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CMainWindow::on_tbSelectDBFile_clicked()
{
    GT_DATABASE_GPS->selectDatabase();
    ui->leDBFile->setText(GT_DATABASE_GPS->dbFile());
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CMainWindow::on_cbUseStyles_clicked(bool checked)
{
    GT_OPTIONS_APP->requestOption(GT_OPTION_USESTYLES)->set(checked);
    GT_DAYNIGHT->setActive(checked);
    GT_APPLICATION->refreshStyleSheet(GT_DAYNIGHT->current());
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CMainWindow::on_cbUseAnimation_clicked(bool checked)
{
    GT_OPTIONS_APP->requestOption(GT_OPTION_ANIMATION_ENABLED)->set(checked);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CMainWindow::on_leAnimationDuration_editingFinished()
{
    GT_OPTIONS_APP->requestOption(GT_OPTION_ANIMATION_DURATION)->set(ui->leAnimationDuration->text().toInt());
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CMainWindow::on_sbSatelliteSignalWait_editingFinished()
{
    GT_OPTIONS_APP->requestOption(GT_OPTION_SATELLITE_SIGNAL_WAIT)->set(ui->sbSatelliteSignalWait->value());
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CMainWindow::on_sbGoodDataWait_editingFinished()
{
    GT_OPTIONS_APP->requestOption(GT_OPTION_GOOD_DATA_WAIT)->set(ui->sbGoodDataWait->value());
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CMainWindow::on_cbSStoreSatellites_clicked(bool checked)
{
    GT_OPTIONS_APP->requestOption(GT_OPTION_STORE_SATELLITES)->set(checked);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CMainWindow::on_tbSelectApplicationPath_clicked()
{
    QFileDialog fdlg(this);
    fdlg.setWindowTitle(tr("Select application home path"));
    fdlg.setDirectory(ui->leApplicatioPath->text());
    fdlg.setOption(QFileDialog::ShowDirsOnly, true);
    fdlg.setFileMode(QFileDialog::Directory);

    if(fdlg.exec() == QDialog::Accepted)
    {
        ui->leApplicatioPath->setText(fdlg.selectedFiles()[0]);
        GT_OPTIONS_APP->requestOption(GT_OPTION_APPLICATION_HOME)->set(ui->leApplicatioPath->text());
    }
}

}
}


