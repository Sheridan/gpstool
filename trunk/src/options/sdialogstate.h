#ifndef __SDIALOHSTATE_H__
#define __SDIALOHSTATE_H__
#include <QPoint>
#include <QSize>
namespace options
{

struct SDialogState
{
    QPoint position;
    QSize size;
    SDialogState(const QPoint &p, const QSize &s)
    {
        position = p;
        size = s;
    }
    SDialogState() {}
};

}
#endif // __SDIALOHSTATE_H__
