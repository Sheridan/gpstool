#include "csatellitedata.h"

namespace data
{
// --------------------------------------------------------------------------------------------------------------------------------------
CSatelliteData::CSatelliteData()
{
    init();
}
// --------------------------------------------------------------------------------------------------------------------------------------
CSatelliteData::CSatelliteData(const qint16 &satPrn, const qint16 &signalStrength, const bool &usedInLastFix,
                               const TSatelliteCoordinate & azimuth, const TSatelliteCoordinate & elevation)
{
    init();
    m_satPrn         .set(satPrn);
    m_signalStrength .set(signalStrength);
    m_usedInLastFix  .set(usedInLastFix);
    m_position->setCoordintes(azimuth, elevation);
}
// --------------------------------------------------------------------------------------------------------------------------------------
CSatelliteData::~CSatelliteData()
{
    delete m_position;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CSatelliteData::set(const CSatelliteData * other)
{
    m_satPrn         .set(other->satPrn());
    m_signalStrength .set(other->signalStrength());
    m_usedInLastFix  .set(other->usedInLastFix());
    m_position->setCoordintes(other->azimuth(), other->elevation());
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CSatelliteData::init()
{
    m_satPrn         = 0;
    m_signalStrength = 0;
    m_usedInLastFix  = false;
    m_position       = new CCoordinatesSatellite();
}
// --------------------------------------------------------------------------------------------------------------------------------------
bool CSatelliteData::isEmpty() const
{
    return !(
            m_satPrn          .isValid() &&
            m_signalStrength  .isValid() &&
            m_usedInLastFix   .isValid() &&
            m_position       ->isValid()
            );
}

}
