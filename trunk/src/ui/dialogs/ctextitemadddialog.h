#ifndef CTEXTITEMADDDIALOG_H
#define CTEXTITEMADDDIALOG_H

#include <QDialog>
#include <QGraphicsScene>
#include "cgraphicsscene.h"

namespace Ui {
    class CTextItemAddDialog;
}
namespace ui
{
namespace dialogs
{

class CTextItemAddDialog : public QDialog
{
    Q_OBJECT
public: // ####################################################
    CTextItemAddDialog(ui::graphics::CGraphicsScene *scene);
    ~CTextItemAddDialog();

protected: // ####################################################
    void changeEvent(QEvent *e);

private: // ####################################################
    Ui::CTextItemAddDialog *ui;
    ui::graphics::CGraphicsScene * m_scene;

private slots: // ####################################################
    void on_pbAdd_clicked();
    void check();
};

}
}
#endif // CTEXTITEMADDDIALOG_H
