#include "cgpsdataupdateinterfasebase.h"
#include "st.h"
#include "optionsdefines.h"
namespace gps
{
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsDataUpdateInterfaseBase::CGpsDataUpdateInterfaseBase() : CGpsInterface()
{
    initialize();
}
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsDataUpdateInterfaseBase::CGpsDataUpdateInterfaseBase(CGpsSource *gps) : CGpsInterface(gps)
{
    initialize();
}
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsDataUpdateInterfaseBase::CGpsDataUpdateInterfaseBase(const TGpsSourceId &id) : CGpsInterface(id)
{
    initialize();
}
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsDataUpdateInterfaseBase::~CGpsDataUpdateInterfaseBase()
{
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsDataUpdateInterfaseBase::initialize()
{
    m_gpsDataUpdateConnected = false;
    m_unavialableDataCount   = 0;
    m_goodDataWait           = GT_OPTIONS_APP->requestOption(GT_OPTION_GOOD_DATA_WAIT);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsDataUpdateInterfaseBase::gpsDataIncomingBase(const data::CGpsData *segment)
{
    if(canGpsDataUpdating())
    {
        if(gpsDataSegmentIsValid(segment))
        {
            newGpsDataAvialable(segment);
            m_unavialableDataCount = 0;
        }
        else
        {
            if(m_unavialableDataCount == m_goodDataWait->value())
            {
                gpsDataSegmentInvalid();
            }
            else
            {
                m_unavialableDataCount++;
            }
        }
    }
    segment->free();
}
}
