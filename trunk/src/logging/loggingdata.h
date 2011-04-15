#ifndef LOGGINGDATA_H
#define LOGGINGDATA_H

#include <QDateTime>
#include <QString>
#include <QList>

namespace logging
{

enum ELogMsgType
{
    mtEmpty,
    #define mtEmpty logging::mtEmpty
    #ifndef QT_NO_DEBUG
        mtDebug,
        #define mtDebug logging::mtDebug
    #endif
    mtInfo,
    #define mtInfo logging::mtInfo
    mtWarning,
    #define mtWarning logging::mtWarning
    mtError
    #define mtError logging::mtError
};

struct SLogMessage
{
    QString     message;
    QString     advanced;
    QDateTime   time;
    ELogMsgType messageType;
    void set(const QString &msg, const QString &adv, const ELogMsgType& type, const QDateTime& t)
    {
        message     = msg;
        advanced    = adv;
        messageType = type;
        time        = t;
    };
    SLogMessage& operator=(const SLogMessage& arg)
    {
        set(arg.message, arg.advanced, arg.messageType, arg.time);
        return *this;
    };
};

typedef QList<SLogMessage> TLogMessagesList;

}
#endif // LOGGINGDATA_H
