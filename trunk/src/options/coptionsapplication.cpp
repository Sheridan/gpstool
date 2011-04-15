#include "coptionsapplication.h"
#include <QApplication>
#include <QDesktopWidget>
namespace options
{
// --------------------------------------------------------------------------------------------------------------------------------------
COptionsApplication::COptionsApplication() : COptions()
{}
// --------------------------------------------------------------------------------------------------------------------------------------
COptionsApplication::~COptionsApplication()
{}
// --------------------------------------------------------------------------------------------------------------------------------------
SDialogState COptionsApplication::getDialogState(const QString & name)
{
    m_mutex.lock();
    SDialogState state;
    beginGroup ( "Dialogs" );
    state.position = value
    (
            QString("%1_position").arg(name),
            QPoint
            (
                    (QApplication::desktop()->width()/2)-150,
                    (QApplication::desktop()->height()/2)-150
            )
    ).toPoint();
    state.size = value(QString("%1_size").arg(name), QPoint(500,600)).toSize();
    endGroup();
    m_mutex.unlock();
    return state;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void COptionsApplication::setDialogState(const QString & name, const SDialogState state)
{
    m_mutex.lock();
    beginGroup ( "Dialogs" );
    setValue(QString("%1_position").arg(name), state.position);
    setValue(QString("%1_size").arg(name), state.size);
    endGroup();
    m_mutex.unlock();
}

}
