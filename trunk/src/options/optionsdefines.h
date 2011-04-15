#ifndef __OPTIONSDEFINES_H__
#define __OPTIONSDEFINES_H__
#include <QTime>
#include <QDir>
#include <QString>
#include "resources.h"

// ---------------------------------------------------- primary

// default options
//#define GT_DO_
#define GT_DO_DAY_START             QTime(8,0,0,0)
#define GT_DO_NIGHT_START           QTime(20,0,0,0)
#define GT_DO_MAPZOOM               1
#define GT_DO_MAIN_STYLESHEET       options::SText("* { border-width: 1px; }")
#define GT_DO_DAY_STYLESHEET        options::SText()
#define GT_DO_NIGHT_STYLESHEET      options::SText()
#define GT_DO_USESTYLES             true
#define GT_DO_ANIMATION_DURATION    1000
#define GT_DO_ANIMATION_ENABLED     true
#define GT_DO_SATELLITE_SIGNAL_WAIT 60
#define GT_DO_GOOD_DATA_WAIT        3
#define GT_DO_GPS_NAME              QString("GPS source")
#define GT_DO_GPS_UPDATE_PERIOD     1000
#define GT_DO_GPS_AUTOCONNECT       false
#define GT_DO_GPS_COLOR             qRgba(200,0,0,200)
#define GT_DO_GPSD_HOST             QString("localhost")
#define GT_DO_GPSD_PORT             2947
#define GT_DO_GPS_ICON              QIcon(GT_RESOURCE(icons, satellite))
#define GT_DO_STORE_SATELLITES      true
#define GT_DO_APPLICATION_HOME      QString("%1/gpstool").arg(QDir::homePath())


// options
//#define GT_OPTION_
#define GT_OPTION_ANIMATION_DURATION        "animation"     , "duration"            , GT_DO_ANIMATION_DURATION
#define GT_OPTION_ANIMATION_ENABLED         "animation"     , "enabled"             , GT_DO_ANIMATION_ENABLED
#define GT_OPTION_USESTYLES                 "application"   , "usestyles"           , GT_DO_USESTYLES
#define GT_OPTION_DAY_STYLESHEET            "application"   , "daystylesheet"       , GT_DO_DAY_STYLESHEET
#define GT_OPTION_MAIN_STYLESHEET           "application"   , "mainstylesheet"      , GT_DO_MAIN_STYLESHEET
#define GT_OPTION_NIGHT_STYLESHEET          "application"   , "nightstylesheet"     , GT_DO_NIGHT_STYLESHEET
#define GT_OPTION_SATELLITE_SIGNAL_WAIT     "application"   , "satellitesignalwait" , GT_DO_SATELLITE_SIGNAL_WAIT
#define GT_OPTION_GOOD_DATA_WAIT            "application"   , "gooddatawait"        , GT_DO_GOOD_DATA_WAIT
#define GT_OPTION_MAPZOOM                   "map"           , "zoom"                , GT_DO_MAPZOOM
#define GT_OPTION_DAY_START                 "daynight"      , "daystarttime"        , GT_DO_DAY_START
#define GT_OPTION_NIGHT_START               "daynight"      , "nightstarttime"      , GT_DO_NIGHT_START
#define GT_OPTION_STORE_SATELLITES          "database"      , "storesatellites"     , GT_DO_STORE_SATELLITES
#define GT_OPTION_APPLICATION_HOME          "application"   , "home"                , GT_DO_APPLICATION_HOME

#define GT_OPTION_GPS_UPDATE_PERIOD(_gpsid) QString::number(_gpsid), "updateperiod", GT_DO_GPS_UPDATE_PERIOD
#define GT_OPTION_GPS_NAME(_gpsid)          QString::number(_gpsid), "name"        , GT_DO_GPS_NAME
#define GT_OPTION_GPS_AUTOCONNECT(_gpsid)   QString::number(_gpsid), "autoconnect" , GT_DO_GPS_AUTOCONNECT
#define GT_OPTION_GPS_COLOR(_gpsid)         QString::number(_gpsid), "color"       , GT_DO_GPS_COLOR
#define GT_OPTION_GPS_ICON(_gpsid)          QString::number(_gpsid), "icon"        , GT_DO_GPS_ICON

#define GT_OPTION_GPSD_HOST(_gpsid)         QString::number(_gpsid), "host"        , GT_DO_GPSD_HOST
#define GT_OPTION_GPSD_PORT(_gpsid)         QString::number(_gpsid), "port"        , GT_DO_GPSD_PORT

// ---------------------------------------------------- secondary
// default options
#define GT_DO_GPSDB_FILE           QString("%1/gps.gtdb").arg(GT_OPTIONS_APP->requestOption(GT_OPTION_APPLICATION_HOME)->value())

// options
#define GT_OPTION_GPSDB_FILE(_dbname)       "database", QString("%1_file").arg(_dbname), GT_DO_GPSDB_FILE

#endif // __OPTIONSDEFINES_H__
