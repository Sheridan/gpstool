//	Author: Sheridan <sheridan@stavcom.ru>, (C) 2006
//	Copyright: See COPYING file that comes with this distribution
//
#ifndef __CLOGVIEW_H__
#define __CLOGVIEW_H__

#include <QListWidget>
#include "clogger.h"
#include "clogviewitem.h"

namespace logging
{
namespace ui
{

class CLogView : public QListWidget
{
    Q_OBJECT
public: // ####################################################
    CLogView                (QWidget * pWidget = 0, bool loadAll = true);
    void setFilter          (logging::ELogMsgType type);
    ~CLogView               ();
private slots: // ####################################################
    void append             (const logging::SLogMessage &msg);
    void showAdvanced       (QListWidgetItem * item);
    void showAdvanced       ();
    void slotCopyToClipBoard();

};

}
}
#endif // __CLOGVIEW_H__
