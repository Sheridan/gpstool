//	Author: Sheridan <sheridan@stavcom.ru>, (C) 2006
//	Copyright: See COPYING file that comes with this distribution
//
#ifndef CLogViewITEM_H
#define CLogViewITEM_H

#include <QListWidget>
//#include <QVector>
#include "loggingdata.h"

namespace logging
{
namespace ui
{

class CLogViewItem : public QListWidgetItem
{
public: // ####################################################
    CLogViewItem        (const logging::SLogMessage &msg, QListWidget *lwParent);
    QString getFullText (bool includeTime = false);
    void hideNoMatch    (logging::ELogMsgType type);
    void showDialog     ();

private: // ####################################################
    logging::SLogMessage m_logMessage;

};

//typedef QVector<CLogViewItem *> TLogViewItems;

}
}
#endif
