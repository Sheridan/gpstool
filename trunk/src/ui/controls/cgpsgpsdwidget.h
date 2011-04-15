#ifndef CGPSGPSDWIDGET_H
#define CGPSGPSDWIDGET_H

#include <QWidget>
#include "cgpsgpsdsource.h"

namespace Ui {
    class CGpsGpsdWidget;
}
namespace ui
{
namespace controls
{

class CGpsGpsdWidget : public QWidget
{
    Q_OBJECT
public: // ####################################################
    CGpsGpsdWidget(gps::CGpsGpsdSource *src, QWidget *parent = 0);
    ~CGpsGpsdWidget();

protected: // ####################################################
    void changeEvent(QEvent *e);

private: // ####################################################
    Ui::CGpsGpsdWidget *ui;
    gps::CGpsGpsdSource * m_src;
    void fillValues();
    void setEditMode(bool value);

private slots: // ####################################################
    void sourceConnected(bool connected);
    void on_pbShowAdvanced_clicked();
    void on_tbCancel_clicked();
    void on_tbApply_clicked();
    void on_tbInfo_clicked();
    void on_tbDelete_clicked();
    void on_pbConnect_clicked();
    void on_tbEdit_clicked();
};

}
}
#endif // CGPSGPSDWIDGET_H
