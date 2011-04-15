#include "gtdebug.h"
#ifndef QT_NO_DEBUG
#include <QDebug>
#include "st.h"
namespace tools
{
namespace debug
{
// --------------------------------------------------------------------------------------------------------------------------------------
void gt_debug(const QString &msg, const QString &advanced)
{
    if(GT_SINGLETON->loggerAvialable())
    {
        GT_LOGGER->append(msg, advanced, mtDebug);
    }
    else
    {
        qDebug() << "Debug" << msg << advanced;
    }
}

}
}

#endif
