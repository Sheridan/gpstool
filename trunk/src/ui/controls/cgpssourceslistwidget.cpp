#include "cgpssourceslistwidget.h"
#include "ui_cgpssourceslistwidget.h"
#include "cgpssource.h"
#include "cgpsgpsdsource.h"
#include "cgpsgpsdwidget.h"
#include "cgpssourcenewdialog.h"
#include "st.h"
namespace ui
{
namespace controls
{
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsSourcesListWidget::CGpsSourcesListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CGpsSourcesListWidget)
{
    setObjectName("GPSSourceListWidget");
    ui->setupUi(this);
    ui->vlSources->setAlignment(Qt::AlignTop);
    GT_GPS_MANAGER->connectSourceUpdates(this, SLOT(appendGpsSource(const gps::TGpsSourceId &)), SLOT(removeGpsSource(const gps::TGpsSourceId &)));
}
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsSourcesListWidget::~CGpsSourcesListWidget()
{
    GT_GPS_MANAGER->disconnectSourceUpdates(this);
    delete ui;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsSourcesListWidget::changeEvent(QEvent *e)
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
void CGpsSourcesListWidget::appendGpsSource(const gps::TGpsSourceId & id)
{
    gps::CGpsSource *src = GT_GPS_MANAGER->source(id);
    if(src)
    {
        QWidget *gpsWidget = NULL;
        switch(src->type())
        {
        case gstGpsd:
            {
                CGpsGpsdWidget *gw = new CGpsGpsdWidget(static_cast<gps::CGpsGpsdSource *>(src), ui->saGpsSources);
                ui->vlSources->addWidget(gw);
                gpsWidget = gw;
            }
            break;
        case gstNone:
        default:
            break;
        }
        m_gpsWidgets[src->id()] = gpsWidget;
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsSourcesListWidget::removeGpsSource(const gps::TGpsSourceId & id)
{
    gps::CGpsSource *src = GT_GPS_MANAGER->source(id);
    QWidget *gpsWidget = m_gpsWidgets.value(id);
    ui->vlSources->removeWidget(gpsWidget);
    m_gpsWidgets.remove(id);
    switch(src->type())
    {
    case gstGpsd:
        {
            CGpsGpsdWidget *gw = static_cast<CGpsGpsdWidget *>(gpsWidget);
            delete gw;
        }
        break;
    case gstNone:
    default:
        break;
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsSourcesListWidget::on_pbAdd_clicked()
{
    ui::dialogs::CGpsSourceNewDialog *dlg = new ui::dialogs::CGpsSourceNewDialog();
    dlg->exec();
    delete dlg;
}

}
}

