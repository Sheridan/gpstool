#include "cstatuswidget.h"
#include "ui_cstatuswidget.h"
#include "st.h"
#include "cdbiconlabel.h"
namespace ui
{
namespace controls
{
// --------------------------------------------------------------------------------------------------------------------------------------
CStatusWidget::CStatusWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CStatusWidget)
{
    setObjectName("StatusWidget");
    ui->setupUi(this);
    GT_GPS_MANAGER->connectSourceUpdates(this, SLOT(appendGpsSource(const gps::TGpsSourceId &)), SLOT(removeGpsSource(const gps::TGpsSourceId &)));
    ui->layIcons->addWidget(new ui::controls::CDbIconLabel(GT_DATABASE_GPS, this));
    connect(ui->pwGpsSourceSelect, SIGNAL(selected(const gps::TGpsSourceId &)), GT_GPS_MANAGER, SLOT(setActiveSource(const gps::TGpsSourceId &)));
}
// --------------------------------------------------------------------------------------------------------------------------------------
CStatusWidget::~CStatusWidget()
{
    GT_GPS_MANAGER->disconnectSourceUpdates(this);
    delete ui;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CStatusWidget::changeEvent(QEvent *e)
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
void CStatusWidget::appendGpsSource(const gps::TGpsSourceId &id)
{
    gps::CGpsSource *src = GT_GPS_MANAGER->source(id);
    if(src && !m_gpsLabels.contains(id))
    {
        ui::controls::CGpsIconLabel *l = new ui::controls::CGpsIconLabel(src, this);
        m_gpsLabels[src->id()] = l;
        ui->layIcons->addWidget(l);
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CStatusWidget::removeGpsSource(const gps::TGpsSourceId &id)
{
    gps::CGpsSource *src = GT_GPS_MANAGER->source(id);
    ui::controls::CGpsIconLabel *l = m_gpsLabels.value(src->id());
    ui->layIcons->removeWidget(l);
    m_gpsLabels.remove(src->id());
    delete l;
}

}
}
