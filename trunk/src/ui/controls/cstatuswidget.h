#ifndef CSTATUSWIDGET_H
#define CSTATUSWIDGET_H

#include <QWidget>
#include "cgpsiconlabel.h"
#include <QMap>
namespace Ui {
    class CStatusWidget;
}
namespace ui
{
namespace controls
{

class CStatusWidget : public QWidget
{
    Q_OBJECT
public: // ####################################################
    CStatusWidget(QWidget *parent = 0);
    ~CStatusWidget();

protected: // ####################################################
    void changeEvent(QEvent *e);

private: // ####################################################
    Ui::CStatusWidget *ui;
    QMap<gps::TGpsSourceId, ui::controls::CGpsIconLabel *> m_gpsLabels;

private slots: // ####################################################
    void appendGpsSource(const gps::TGpsSourceId &id);
    void removeGpsSource(const gps::TGpsSourceId &id);

signals: // ####################################################
    void otherSourceSelected(const gps::TGpsSourceId &id);
};

}
}
#endif // CSTATUSWIDGET_H
