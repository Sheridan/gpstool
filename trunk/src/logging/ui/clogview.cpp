//	Author: Sheridan <sheridan@stavcom.ru>, (C) 2006
//	Copyright: See COPYING file that comes with this distribution
//
#include "clogview.h"
#include "st.h"
#include "resources.h"
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QClipboard>

namespace logging
{
namespace ui
{
// --------------------------------------------------------------------------------------------------------------------------------------
CLogView::CLogView(QWidget * pWidget, bool loadAll) : QListWidget(pWidget)
{
    setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
    //Messages
    if(loadAll)
    {
        connect(GT_LOGGER, SIGNAL(msgSend(const logging::SLogMessage &)), this, SLOT(append(const logging::SLogMessage &)));
        GT_LOGGER->sendAll();
        disconnect(GT_LOGGER, 0,0,0);
    }
    connect(GT_LOGGER, SIGNAL(msgAppend(const logging::SLogMessage &)), this, SLOT(append(const logging::SLogMessage &)));

    //DoubleClick
    connect(this, SIGNAL(itemDoubleClicked ( QListWidgetItem * )), this, SLOT(showAdvanced( QListWidgetItem * )));

    //PopupMenu
    QAction *actionCopyMessage  = new QAction(QIcon(GT_RESOURCE(icons, edit-copy)), tr("&Copy"),            this);
    QAction *actionShowAdvanced = new QAction(QIcon(GT_RESOURCE(icons, log-view )), tr("Show &advanced"),   this);

    actionCopyMessage   ->setShortcut(tr("Ctrl+C"));
    actionShowAdvanced  ->setShortcut(tr("Ctrl+A"));

    connect(actionCopyMessage,  SIGNAL(triggered()), this, SLOT(slotCopyToClipBoard())  );
    connect(actionShowAdvanced, SIGNAL(triggered()), this, SLOT(showAdvanced())         );

    setContextMenuPolicy(Qt::ActionsContextMenu);
    addAction(actionShowAdvanced);
    addAction(actionCopyMessage );
}
// --------------------------------------------------------------------------------------------------------------------------------------
CLogView::~CLogView()
{}
// --------------------------------------------------------------------------------------------------------------------------------------
void CLogView::append(const logging::SLogMessage &msg)
{
    CLogViewItem *i = new CLogViewItem(msg, this);
    addItem(i);
//    _lvItems.append(i);
    scrollToBottom();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CLogView::showAdvanced()
{
    if (currentItem())
    {
        showAdvanced(currentItem());
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CLogView::showAdvanced(QListWidgetItem * item)
{
    static_cast<CLogViewItem *>(item)->showDialog();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CLogView::slotCopyToClipBoard()
{
    if (currentItem())
    {
        QApplication::clipboard()->setText(static_cast<CLogViewItem *>(currentItem())->getFullText());
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CLogView::setFilter(logging::ELogMsgType type)
{
    for (int i = 0; i<count(); i++)
    {
        static_cast<CLogViewItem *>(item(i))->hideNoMatch(type);
    }
}


}
}
