#include "cmapsourcestablewidget.h"
#include "ui_cmapsourcestablewidget.h"
namespace ui
{
namespace controls
{
// --------------------------------------------------------------------------------------------------------------------------------------
CMapSourcesTableWidget::CMapSourcesTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CMapSourcesTableWidget)
{
    ui->setupUi(this);
}
// --------------------------------------------------------------------------------------------------------------------------------------
CMapSourcesTableWidget::~CMapSourcesTableWidget()
{
    delete ui;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CMapSourcesTableWidget::changeEvent(QEvent *e)
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

}
}
