#ifndef GTDEBUG_H
#define GTDEBUG_H
#ifndef QT_NO_DEBUG
#include <QString>

namespace tools
{
namespace debug
{

void gt_debug(const QString &msg, const QString &advanced = "");

}
}

#define GT_DEBUG(_msg)          { tools::debug::gt_debug(_msg);      }
#define GT_DEBUG_ADV(_msg,_adv) { tools::debug::gt_debug(_msg,_adv); }

#else
    #define GT_DEBUG(_msg)
    #define GT_DEBUG_ADV(_msg,_adv)
#endif
#endif // GTDEBUG_H
