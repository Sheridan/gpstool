#ifndef CCOORDINATESSATELLITE_H
#define CCOORDINATESSATELLITE_H

#include "ccoordinates.h"
#define GT_SATC_T qint16

namespace data
{

typedef qint16 TSatelliteCoordinate;

class CCoordinatesSatellite : public CCoordinates<TSatelliteCoordinate>
{
public: // ####################################################
    CCoordinatesSatellite() : CCoordinates<TSatelliteCoordinate>(0, 0) {}
    CCoordinatesSatellite(const TSatelliteCoordinate & azimuth, const TSatelliteCoordinate & elevation)
        : CCoordinates<TSatelliteCoordinate>(azimuth, elevation) {}

    void setCoordintes(const TSatelliteCoordinate &azimuth, const TSatelliteCoordinate &elevation) { m_alpha.set(azimuth); m_beta.set(elevation); }
    const TSatelliteCoordinate  & azimuth           () const { return m_alpha   .value(); }
    const TSatelliteCoordinate  & elevation         () const { return m_beta    .value(); }
    const bool                  & isAzimuthValid    () const { return m_alpha .isValid(); }
    const bool                  & isElevationValid  () const { return m_beta  .isValid(); }
};

//typedef QList<CSatelliteCoordinates> TSatelliteCoordinatesList;

}

#endif // CCOORDINATESSATELLITE_H
