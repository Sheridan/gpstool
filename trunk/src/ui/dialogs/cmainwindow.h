#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QMainWindow>
#include <QTime>

namespace Ui {
    class CMainWindow;
}

namespace ui
{
namespace dialogs
{

class CMainWindow : public QMainWindow
{
    Q_OBJECT
public: // ####################################################
    CMainWindow(QWidget *parent = 0);
    ~CMainWindow();

protected: // ####################################################
    void changeEvent(QEvent *e);

private: // ####################################################
    Ui::CMainWindow *ui;

private slots: // ####################################################
    void on_tbSelectApplicationPath_clicked();
    void on_cbSStoreSatellites_clicked(bool checked);
    void on_sbGoodDataWait_editingFinished();
    void on_sbSatelliteSignalWait_editingFinished();
    void on_cbUseStyles_clicked(bool checked);
    void on_leAnimationDuration_editingFinished();
    void on_cbUseAnimation_clicked(bool checked);
    void on_tbSelectDBFile_clicked();
    void on_teDayStartTime_timeChanged(QTime date);
    void on_teNightStartTime_timeChanged(QTime date);
    void on_sliderZoom_valueChanged(int value);
    void on_pbApplyStyles_clicked();

signals: // ####################################################
    void mapZoomChanged(int);
};

}
}
#endif // CMAINWINDOW_H
