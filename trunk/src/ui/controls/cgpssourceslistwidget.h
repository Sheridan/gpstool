#ifndef CGPSSOURCESLISTWIDGET_H
#define CGPSSOURCESLISTWIDGET_H

#include <QWidget>
#include <QMap>
#include "gpsdefines.h"

namespace Ui {
    class CGpsSourcesListWidget;
}
namespace ui
{
namespace controls
{

class CGpsSourcesListWidget : public QWidget
{
    Q_OBJECT
public: // ####################################################
    CGpsSourcesListWidget (QWidget *parent = 0);
    ~CGpsSourcesListWidget();

protected: // ####################################################
    void changeEvent(QEvent *e);

private: // ####################################################
    Ui::CGpsSourcesListWidget *ui;
    QMap<gps::TGpsSourceId, QWidget *> m_gpsWidgets;

private slots: // ####################################################
    void appendGpsSource (const gps::TGpsSourceId & id);
    void removeGpsSource (const gps::TGpsSourceId & id);
    void on_pbAdd_clicked();
};

}
}
#endif // CGPSSOURCESLISTWIDGET_H
