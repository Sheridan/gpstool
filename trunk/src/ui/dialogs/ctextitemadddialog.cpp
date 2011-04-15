#include "ctextitemadddialog.h"
#include "ui_ctextitemadddialog.h"
#include "uidefines.h"
#include "st.h"

#include "infotextitems.h"

namespace ui
{
namespace dialogs
{
// --------------------------------------------------------------------------------------------------------------------------------------
CTextItemAddDialog::CTextItemAddDialog(ui::graphics::CGraphicsScene *scene) :
    QDialog(NULL),
    ui(new Ui::CTextItemAddDialog),
    m_scene(scene)
{
    ui->setupUi(this);
    connect(ui->pwGpsSourceSelect,      SIGNAL(selected(const gps::TGpsSourceId &)), this, SLOT(check()));
    connect(ui->rbAltitude,             SIGNAL(clicked()), this, SLOT(check()));
    connect(ui->rbCourseFromNorth,      SIGNAL(clicked()), this, SLOT(check()));
    connect(ui->rbLatitude,             SIGNAL(clicked()), this, SLOT(check()));
    connect(ui->rbLongitude,            SIGNAL(clicked()), this, SLOT(check()));
    connect(ui->rbMode,                 SIGNAL(clicked()), this, SLOT(check()));
    connect(ui->rbPQHorizontal,         SIGNAL(clicked()), this, SLOT(check()));
    connect(ui->rbPQTotal,              SIGNAL(clicked()), this, SLOT(check()));
    connect(ui->rbPQVertical,           SIGNAL(clicked()), this, SLOT(check()));
    connect(ui->rbRateOfClimb,          SIGNAL(clicked()), this, SLOT(check()));
    connect(ui->rbSatellitesInLastFix,  SIGNAL(clicked()), this, SLOT(check()));
    connect(ui->rbSentence,             SIGNAL(clicked()), this, SLOT(check()));
    connect(ui->rbSpeedOverGround,      SIGNAL(clicked()), this, SLOT(check()));
    connect(ui->rbStatus,               SIGNAL(clicked()), this, SLOT(check()));

    GT_RESTORE_DIALOG_STATE("textitemadddlg");
}
// --------------------------------------------------------------------------------------------------------------------------------------
CTextItemAddDialog::~CTextItemAddDialog()
{
    GT_SAVE_DIALOG_STATE("textitemadddlg");
    delete ui;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CTextItemAddDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

//ui->rbAltitude
//ui->rbCourseFromNorth
//ui->rbLatitude
//ui->rbLongitude
//ui->rbMode
//ui->rbPQHorizontal
//ui->rbPQTotal
//ui->rbPQVertical
//ui->rbRateOfClimb,
//ui->rbSatellitesInLastFix
//ui->rbSentence
//ui->rbSpeedOverGround
//ui->rbStatus
// --------------------------------------------------------------------------------------------------------------------------------------
void CTextItemAddDialog::check()
{
    ui->pbAdd->setEnabled(m_scene && !ui->pwGpsSourceSelect->isEmpty() &&
                             (
                                     ui->rbAltitude             ->isChecked() ||
                                     ui->rbCourseFromNorth      ->isChecked() ||
                                     ui->rbLatitude             ->isChecked() ||
                                     ui->rbLongitude            ->isChecked() ||
                                     ui->rbMode                 ->isChecked() ||
                                     ui->rbPQHorizontal         ->isChecked() ||
                                     ui->rbPQTotal              ->isChecked() ||
                                     ui->rbPQVertical           ->isChecked() ||
                                     ui->rbRateOfClimb          ->isChecked() ||
                                     ui->rbSatellitesInLastFix  ->isChecked() ||
                                     ui->rbSentence             ->isChecked() ||
                                     ui->rbSpeedOverGround      ->isChecked() ||
                                     ui->rbStatus               ->isChecked()
                             ));
}
// --------------------------------------------------------------------------------------------------------------------------------------
#define GT_APPEND_INFOTEXTITEM(_class,_checkbox) \
if(ui->_checkbox->isChecked()) \
{ \
  ui::graphics::_class *c = new ui::graphics::_class(GT_GPS_MANAGER->source(ui->pwGpsSourceSelect->selectedId())); \
  m_scene->addGpsInfoItem(c); \
  return; \
}

void CTextItemAddDialog::on_pbAdd_clicked()
{

    GT_APPEND_INFOTEXTITEM(CGpsInfoTextItemAltitude                    ,rbAltitude             );
    GT_APPEND_INFOTEXTITEM(CGpsInfoTextItemCourseFromNorth             ,rbCourseFromNorth      );
    GT_APPEND_INFOTEXTITEM(CGpsInfoTextItemLatitude                    ,rbLatitude             );
    GT_APPEND_INFOTEXTITEM(CGpsInfoTextItemLongitude                   ,rbLongitude            );
    GT_APPEND_INFOTEXTITEM(CGpsInfoTextItemMode                        ,rbMode                 );
    GT_APPEND_INFOTEXTITEM(CGpsInfoTextItemPositionQualityHorizontal   ,rbPQHorizontal         );
    GT_APPEND_INFOTEXTITEM(CGpsInfoTextItemPositionQualityTotal        ,rbPQTotal              );
    GT_APPEND_INFOTEXTITEM(CGpsInfoTextItemPositionQualityVertical     ,rbPQVertical           );
    GT_APPEND_INFOTEXTITEM(CGpsInfoTextItemRateOfClimb                 ,rbRateOfClimb          );
    GT_APPEND_INFOTEXTITEM(CGpsInfoTextItemSattelitesInLastFix         ,rbSatellitesInLastFix  );
    GT_APPEND_INFOTEXTITEM(CGpsInfoTextItemSentence                    ,rbSentence             );
    GT_APPEND_INFOTEXTITEM(CGpsInfoTextItemSpeeOverGround              ,rbSpeedOverGround      );
    GT_APPEND_INFOTEXTITEM(CGpsInfoTextItemStatus                      ,rbStatus               );
}

}
}
