#ifndef CMAPSOURCESTABLEWIDGET_H
#define CMAPSOURCESTABLEWIDGET_H

#include <QWidget>

namespace Ui {
    class CMapSourcesTableWidget;
}
namespace ui
{
namespace controls
{
class CMapSourcesTableWidget : public QWidget
{
    Q_OBJECT
public: // ####################################################
    CMapSourcesTableWidget(QWidget *parent = 0);
    ~CMapSourcesTableWidget();

protected: // ####################################################
    void changeEvent(QEvent *e);

private: // ####################################################
    Ui::CMapSourcesTableWidget *ui;
};

}
}
#endif // CMAPSOURCESTABLEWIDGET_H
