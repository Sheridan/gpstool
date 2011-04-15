#include "coptionicon.h"
#include "coptions.h"
#include <QByteArray>
#include <QDataStream>
#include <QBuffer>
#include <QDebug>
namespace options
{
// --------------------------------------------------------------------------------------------------------------------------------------
void COptionIcon::load()
{
    set
    (
            qVariantValue<QIcon>
            (
                    m_parent->getSectionValue
                    (
                            section(),
                            key(),
                            defaultValue()
                    )
            )
    );
}
// --------------------------------------------------------------------------------------------------------------------------------------
void COptionIcon::save() { m_parent->setSectionValue(section(), key(), value()); }

}
