#ifndef __ST_H__
#define __ST_H__

#include "csingleton.h"

#define GT_SINGLETON             CSingleton::instance()
#define GT_APPLICATION           GT_SINGLETON->application()
#define GT_LOGGER                GT_SINGLETON->logger()
#define GT_OPTIONS_APP           GT_SINGLETON->optionsPool()->optionsApplication()
#define GT_OPTIONS_GPS           GT_SINGLETON->optionsPool()->optionsGps()
#define GT_OPTIONS_WINDOWS_ITEMS GT_SINGLETON->optionsPool()->optionsWindowItems()
#define GT_GPS_MANAGER           GT_SINGLETON->gpsSourceManager()
#define GT_DAYNIGHT              GT_SINGLETON->dayNight()
#define GT_DATABASE_GPS          GT_SINGLETON->gpsDatabase()

#endif // __ST_H__
