//	Author: Sheridan <sheridan@stavcom.ru>, (C) 2006
//	Copyright: See COPYING file that comes with this distribution
//
#include "clogviewitem.h"
#include "clogmessageshowdialog.h"
#include "resources.h"
#include <QObject>

namespace logging
{
namespace ui
{
// --------------------------------------------------------------------------------------------------------------------------------------
CLogViewItem::CLogViewItem(const SLogMessage &msg, QListWidget *lwParent) : QListWidgetItem(lwParent)
{
    m_logMessage = msg;
    setIcon(
            QIcon(
                    GT_RESOURCE_DYNAMIC_ALIAS(icons, LOGG_TYPE_DATA(m_logMessage.messageType, "", "log-info", "log-warning", "log-error", "log-debug"))
                 )
            );
    setText(m_logMessage.time.toString("[dd.MM.yyyy hh:mm:ss] ") + m_logMessage.message);
    setToolTip(m_logMessage.advanced);
}
// --------------------------------------------------------------------------------------------------------------------------------------
QString CLogViewItem::getFullText(bool includeTime)
{
    QStringList fullText;
    QString errType = LOGG_TYPE_DATA(m_logMessage.messageType, "", QObject::tr("Info"), QObject::tr("Warning"), QObject::tr("Error"), QObject::tr("Debug"));
        fullText.append(QObject::tr("Type: <b>%1</b><br />")        .arg(errType));
    if(includeTime) {
        fullText.append(QObject::tr("Timestamp: <b>%1</b><br />")   .arg(m_logMessage.time.toString("dd.MM.yyyy hh:mm:ss"))); }
        fullText.append(QObject::tr("%1 message: <b>%2</b><br />")  .arg(errType).arg(m_logMessage.message));
    if(!m_logMessage.advanced.isEmpty())
    {
        fullText.append(QObject::tr("<center>%1 text</center><br />").arg(errType));
        fullText.append("<hr /><pre>");
        fullText.append(m_logMessage.advanced);
        fullText.append("</pre><hr />");
    }
    return fullText.join("\n");
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CLogViewItem::hideNoMatch(logging::ELogMsgType type)
{
    switch (type)
    {
        case mtEmpty: setHidden(false); break;
        default: setHidden(m_logMessage.messageType != type);
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CLogViewItem::showDialog()
{
    logging::ui::CLogMessageShowDialog dlg(m_logMessage);
    dlg.exec();
}

}
}
