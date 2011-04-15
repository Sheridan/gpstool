#include "cgpsdata.h"
namespace data
{
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsData::CGpsData(const QString &srcName, const gps::TGpsSourceId &srcId, const quint16 &ttl)
{
    m_ttl                    = ttl;
    m_gpsSourceName          = srcName;
    m_gpsSourceId            = srcId;
    m_timestamp              = 0.0;
    m_courseFromNorth        = 0.0;
    m_altitude               = 0.0;
    m_speedOverGround        = 0.0;
    m_rateOfClimb            = 0.0;
    m_satellitesInLastFix    = 0;
    m_satellitesSentence     = "";
    m_dopSpherical           = 0.0;
    m_dopHorizontal          = 0.0;
    m_dopVertical            = 0.0;
    m_dopTime                = 0.0;
    m_dopTotalGeometric      = 0.0;
    m_mode                   = emNoset;
    m_status                 = esNoFix;
    m_position               = new CCoordinatesPosition();
}
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsData::~CGpsData()
{
    delete m_position;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsData::free() const
{
    m_ttl--;
    if(m_ttl == 0)
    {
        delete this;
    }
}

}
