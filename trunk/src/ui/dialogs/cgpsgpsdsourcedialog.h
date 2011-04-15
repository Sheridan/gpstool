#ifndef CGPSGPSDSOURCEDIALOG_H
#define CGPSGPSDSOURCEDIALOG_H

#include <QDialog>
#include "gpsdefines.h"

namespace Ui {
    class CGpsGpsdSourceDialog;
}
namespace ui
{
namespace dialogs
{

class CGpsGpsdSourceDialog : public QDialog {
    Q_OBJECT
public: // ####################################################
    CGpsGpsdSourceDialog(const QString & name, QWidget *parent = 0);
    CGpsGpsdSourceDialog(const gps::TGpsSourceId & id, QWidget *parent = 0);
    ~CGpsGpsdSourceDialog();

protected: // ####################################################
    void changeEvent(QEvent *e);

private: // ####################################################
    Ui::CGpsGpsdSourceDialog *ui;
    bool    m_edit;
    QString m_name;
    gps::TGpsSourceId    m_id;
    void accept();
    void init();

private slots: // ####################################################
    void check();
};

}
}
#endif // CGPSGPSDSOURCEDIALOG_H
