#include "textitems.h"

namespace ui
{
namespace graphics
{

GT_TEXTITEM_UPDATE(CTextItemSpeeOverGround,             isSpeedOverGroundValid(),           QString("%1 km/h")  .arg(segment->speedOverGround()));
GT_TEXTITEM_UPDATE(CTextItemCourseFromNorth,            isCourseFromNorthValid(),           QString("%1%2")     .arg(segment->courseFromNorth()).arg(QChar(176)));
GT_TEXTITEM_UPDATE(CTextItemAltitude,                   isAltitudeValid(),                  QString("%1 m")     .arg(segment->altitude()));
GT_TEXTITEM_UPDATE(CTextItemLatitude,                   isLatitudeValid(),                  QString("%1%2")     .arg(segment->latitude()).arg(QChar(176)));
GT_TEXTITEM_UPDATE(CTextItemLongitude,                  isLongitudeValid(),                 QString("%1%2")     .arg(segment->longitude()).arg(QChar(176)));
GT_TEXTITEM_UPDATE(CTextItemMode,                       isModeValid(),                      QString("%1")       .arg(segment->mode()));
GT_TEXTITEM_UPDATE(CTextItemStatus,                     isStatusValid(),                    QString("%1")       .arg(segment->status()));
GT_TEXTITEM_UPDATE(CTextItemPositionQualityTotal,       isPositionQualityTotalValid(),      QString("%1")       .arg(segment->positionQualityTotal()));
GT_TEXTITEM_UPDATE(CTextItemPositionQualityHorizontal,  isPositionQualityHorizontalValid(), QString("%1")       .arg(segment->positionQualityHorizontal()));
GT_TEXTITEM_UPDATE(CTextItemPositionQualityVertical,    isPositionQualityVerticalValid(),   QString("%1")       .arg(segment->positionQualityVertical()));
GT_TEXTITEM_UPDATE(CTextItemSattelitesInLastFix,        isSatellitesInLastFixValid(),       QString("%1")       .arg(segment->satellitesInLastFix()));
GT_TEXTITEM_UPDATE(CTextItemRateOfClimb,                isRateOfClimbValid(),               QString("%1")       .arg(segment->rateOfClimb()));
GT_TEXTITEM_UPDATE(CTextItemSentence,                   isSatellitesSentenceValid(),        segment->satellitesSentence());

}
}
