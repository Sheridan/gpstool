#ifndef CICONTOOL_H
#define CICONTOOL_H

#include <QIcon>
#include <QSize>

namespace tools
{
namespace icons
{

QIcon stratificateIcons (const QIcon &source        , const QIcon   &layer      );
QIcon stratificateIcons (const QString &sourceFile  , const QString &layerFile  );
QIcon stratificateIcons (const QIcon &source        , const QString &layerFile  );
QIcon setIconOpacity    (const QIcon &icon          , float opacity             );
QIcon setIconOpacity    (const QString &iconFile    , float opacity             );

}
}

#endif // CICONTOOL_H
