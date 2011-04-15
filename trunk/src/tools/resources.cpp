#include "resources.h"
#include <QFile>
#include "gtdebug.h"
#include "st.h"

namespace tools
{
namespace resources
{
// --------------------------------------------------------------------------------------------------------------------------------------
QString readText(const QString &resource)
{
    QFile file(resource);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        GT_DEBUG(QString("Resource %1 open").arg(resource));
        QString content = "";
        while (!file.atEnd())
        {
            content += QString(file.readLine());
        }
        file.close();
        return content;
    }
    GT_LOGGER->append(QObject::tr("Cannot open resource %1").arg(resource), mtError);
    return "";
}

}
}
