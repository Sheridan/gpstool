#include "cid.h"
#include <QDateTime>

namespace tools
{
// --------------------------------------------------------------------------------------------------------------------------------------
CId::CId(const TId &val) : m_value(val)
{
    if(m_value == 0)
    {
        m_value = QDateTime::currentDateTime().toTime_t();
    }
}

}
