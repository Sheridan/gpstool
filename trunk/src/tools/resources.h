#ifndef RESOURCES_H
#define RESOURCES_H

#include <QString>

namespace tools
{
namespace resources
{

QString readText(const QString &resource);

}
}

#define GT_RESOURCE(_prefix,_alias) ":/" #_prefix "/" #_alias ".png"
#define GT_RESOURCE_DYNAMIC_ALIAS(_prefix,_dyalias) QString(":/" #_prefix "/%1.png").arg(_dyalias)

#endif // RESOURCES_H
