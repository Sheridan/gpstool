#include "coptiontext.h"
#include "coptions.h"
#include <QByteArray>

#define TEXT_SEP QString(":sep:")

namespace options
{
// --------------------------------------------------------------------------------------------------------------------------------------
void COptionText::load()
{
    set     (
            QString
            (
                    QByteArray::fromBase64
                    (
                            m_parent->getSectionValue
                            (
                                    section(),
                                    key(),
                                    value().text.toUtf8().toBase64()
                            ).toString().toUtf8()

                    )
            )
            );
}
// --------------------------------------------------------------------------------------------------------------------------------------
void COptionText::save() { m_parent->setSectionValue(section(), key(), value().text.toUtf8().toBase64()); }

}
