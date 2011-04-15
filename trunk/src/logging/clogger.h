//	Author: Sheridan <sheridan@stavcom.ru>, (C) 2006
//	Copyright: See COPYING file that comes with this distribution
//
#ifndef __CLOGGER_H__
#define __CLOGGER_H__

#ifndef QT_NO_DEBUG
    #include <QDebug>
#endif
#include <QMetaType>
#include <QObject>
#include <QString>
#include <QMutex>
#include <QThread>
#include "loggingdata.h"

namespace logging
{

class CLogger : public QThread
{
Q_OBJECT
public: // ####################################################
    CLogger ();
    ~CLogger();
    void append (const QString& msg, const QString& adv = QString(), ELogMsgType msgType = mtInfo );
    void append (const QString& msg,                                 ELogMsgType msgType          );
    void sendAll();

private: // ####################################################
    TLogMessagesList    m_logList;
    QMutex              m_mutex;
    void                run();

public slots: // ####################################################
    void stop();

signals: // ####################################################
    void msgAppend  ( const logging::SLogMessage & );
    void msgSend    ( const logging::SLogMessage & );
};

}

#ifndef QT_NO_DEBUG

#define LOGG_TYPE_DATA(_type,_empty,_info,_warning,_error,_debug) \
    (_type == mtInfo ? _info : \
     (_type == mtWarning ? _warning : \
      (_type == mtError ? _error : \
       (_type == mtDebug ? _debug : (_empty)))))

#else

#define LOGG_TYPE_DATA(_type,_empty,_info,_warning,_error,_debug) \
    (_type == mtInfo ? _info : \
     (_type == mtWarning ? _warning : \
      (_type == mtError ? _error : (_empty))))

#endif

#endif // __CLOGGER_H__
