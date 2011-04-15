#ifndef INFOTEXTITEMS_H
#define INFOTEXTITEMS_H
#include "cgpsinfotext.h"

#define GT_TEXTITEM(_class,_title,_type,_isvalid,_textData) \
class _class : public CGpsInfoText { \
public: \
    _class(gps::CGpsSource *gpssrc, tools::TId iid = 0) : CGpsInfoText(gpssrc, _title, iid) {} \
    ~_class() {}; \
    void newGpsDataAvialable  (const data::CGpsData *segment) { setText(_textData);       } \
    bool gpsDataSegmentIsValid(const data::CGpsData *segment) { return segment->_isvalid; } \
    bool canGpsDataUpdating      () { return isActive(); } \
    void gpsDataSegmentInvalid   () { reset          (); } \
    EGpsInfoTextItemType textType() { return _type     ; } \
};

namespace ui
{
namespace graphics
{

GT_TEXTITEM(CGpsInfoTextItemSpeeOverGround             , tr("Speed over ground")           , gititSpeedOverGround            ,isSpeedOverGroundValid(),           QString("%1 km/h")  .arg(segment->speedOverGround()));
GT_TEXTITEM(CGpsInfoTextItemCourseFromNorth            , tr("Course from north")           , gititCourseFromNorth            ,isCourseFromNorthValid(),           QString("%1%2")     .arg(segment->courseFromNorth()).arg(QChar(176)));
GT_TEXTITEM(CGpsInfoTextItemAltitude                   , tr("Altitude")                    , gititAltitude                   ,isAltitudeValid(),                  QString("%1 m")     .arg(segment->altitude()));
GT_TEXTITEM(CGpsInfoTextItemLatitude                   , tr("Latitude")                    , gititLatitude                   ,isLatitudeValid(),                  QString("%1%2")     .arg(segment->latitude()).arg(QChar(176)));
GT_TEXTITEM(CGpsInfoTextItemLongitude                  , tr("Longitude")                   , gititLongitude                  ,isLongitudeValid(),                 QString("%1%2")     .arg(segment->longitude()).arg(QChar(176)));
GT_TEXTITEM(CGpsInfoTextItemMode                       , tr("Mode")                        , gititMode                       ,isModeValid(),                      QString("%1")       .arg(segment->mode()));
GT_TEXTITEM(CGpsInfoTextItemStatus                     , tr("Status")                      , gititStatus                     ,isStatusValid(),                    QString("%1")       .arg(segment->status()));
GT_TEXTITEM(CGpsInfoTextItemPositionQualityTotal       , tr("Position quality total")      , gititPositionQualityTotal       ,isPositionQualityTotalValid(),      QString("%1")       .arg(segment->positionQualityTotal()));
GT_TEXTITEM(CGpsInfoTextItemPositionQualityHorizontal  , tr("Position quality horizontal") , gititPositionQualityHorizontal  ,isPositionQualityHorizontalValid(), QString("%1")       .arg(segment->positionQualityHorizontal()));
GT_TEXTITEM(CGpsInfoTextItemPositionQualityVertical    , tr("Position quality vertical")   , gititPositionQualityVertical    ,isPositionQualityVerticalValid(),   QString("%1")       .arg(segment->positionQualityVertical()));
GT_TEXTITEM(CGpsInfoTextItemSattelitesInLastFix        , tr("Sattelites in last fix")      , gititSattelitesInLastFix        ,isSatellitesInLastFixValid(),       QString("%1")       .arg(segment->satellitesInLastFix()));
GT_TEXTITEM(CGpsInfoTextItemRateOfClimb                , tr("Vertical speed")              , gititRateOfClimb                ,isRateOfClimbValid(),               QString("%1")       .arg(segment->rateOfClimb()));
GT_TEXTITEM(CGpsInfoTextItemSentence                   , tr("Sentence")                    , gititSentence                   ,isSatellitesSentenceValid(),        segment->satellitesSentence());

}
}

#endif // INFOTEXTITEMS_H
