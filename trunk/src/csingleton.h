#ifndef CSINGLETON_H
#define CSINGLETON_H

#include "capplication.h"
#include "clogger.h"
#include "coptionspool.h"
#include "cgpssourcemanager.h"
#include "cdaynight.h"
#include "cgpsdatabase.h"
#include "gtdebug.h"

#define GT_SIMPLE_ST_NAME(_name) m_##_name

#define GT_ST_DEBUG(_name,_text) GT_DEBUG(QString("Class %1 %2").arg(#_name).arg(_text));

#define GT_SIMPLE_DELETE(_name) { delete GT_SIMPLE_ST_NAME(_name); GT_SIMPLE_ST_NAME(_name) = NULL; GT_ST_DEBUG(_name, "destruct"); }
#define GT_SIMPLE_THREAD_DELETE(_name) { GT_SIMPLE_ST_NAME(_name)->stop(); GT_ST_DEBUG(_name, "quit thread"); GT_SIMPLE_DELETE(_name); }

#define GT_ST_BOTH(_name, _class) \
    private: \
        _class *GT_SIMPLE_ST_NAME(_name); \
    public: \
        bool _name##Avialable() { return !!GT_SIMPLE_ST_NAME(_name); }

#define GT_SIMPLE_ST_DEFINITION(_name, _class) \
    GT_ST_BOTH(_name, _class) \
    public: \
        _class *_name() { if(!GT_SIMPLE_ST_NAME(_name)) { GT_SIMPLE_ST_NAME(_name) = new _class(); GT_ST_DEBUG(_name, "construct"); } return GT_SIMPLE_ST_NAME(_name); }

#define GT_SIMPLE_THREAD_ST_DEFINITION(_name, _class) \
    GT_ST_BOTH(_name, _class) \
    public: \
        _class *_name() \
        { \
          if(!GT_SIMPLE_ST_NAME(_name)) \
          { \
            GT_SIMPLE_ST_NAME(_name) = new _class(); \
            GT_SIMPLE_ST_NAME(_name)->start(); \
            GT_ST_DEBUG(_name, "construct and run"); \
          } return GT_SIMPLE_ST_NAME(_name); \
        }

class CSingleton
{
    friend class CApplication;
    GT_SIMPLE_ST_DEFINITION         (dayNight        , CDayNight             );
    GT_SIMPLE_THREAD_ST_DEFINITION  (optionsPool     , options::COptionsPool );
    GT_SIMPLE_THREAD_ST_DEFINITION  (logger          , logging::CLogger      );
    GT_SIMPLE_THREAD_ST_DEFINITION  (gpsDatabase     , data::db::CGpsDatabase);
    GT_SIMPLE_THREAD_ST_DEFINITION  (gpsSourceManager, gps::CGpsSourceManager);
private: // ####################################################
    CSingleton();
    ~CSingleton();
    CApplication *m_application;

protected: // ####################################################
    static void destroy();
    void initialize(CApplication* app) { m_application = app; };

public: // ####################################################
    static CSingleton *instance();
    CApplication* application() { return m_application; }
};
#endif

