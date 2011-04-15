//	Author: Sheridan <sheridan@stavcom.ru>, (C) 2006
//	Copyright: See COPYING file that comes with this distribution
//
#include "clogger.h"

namespace logging
{
// --------------------------------------------------------------------------------------------------------------------------------------
CLogger::CLogger () : QThread ()
{}
// --------------------------------------------------------------------------------------------------------------------------------------
CLogger::~CLogger()
{}
// --------------------------------------------------------------------------------------------------------------------------------------
void CLogger::run()
{
    exec();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CLogger::stop()
{
    disconnect(this, 0,0,0);
    quit();
    wait();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CLogger::append(const QString& msg, const QString& adv, ELogMsgType msgType)
{
    SLogMessage lm;
    #ifndef QT_NO_DEBUG
        qDebug() << msgType << msg << adv;
    #endif
    lm.set(msg, adv, msgType, QDateTime::currentDateTime());
    m_mutex.lock();
    m_logList.append (lm);
    emit msgAppend (lm);
    m_mutex.unlock();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CLogger::append (const QString& msg, ELogMsgType msgType          )
{
    append(msg, "", msgType);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CLogger::sendAll()
{
    m_mutex.lock();
    TLogMessagesList::iterator it = m_logList.begin();
    while ( it < m_logList.end() )
    {
        emit msgSend ( *it );
        it++;
    }
    m_mutex.unlock();
}

}
