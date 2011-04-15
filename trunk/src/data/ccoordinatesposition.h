#ifndef CCOORDINATESPOSITION_H
#define CCOORDINATESPOSITION_H

#include "ccoordinates.h"

namespace data
{

typedef float TPositionCoordinate;

class CCoordinatesPosition : public CCoordinates<TPositionCoordinate>
{
public: // ####################################################
    CCoordinatesPosition() : CCoordinates<TPositionCoordinate>(0.0, 0.0) {}
    CCoordinatesPosition(const TPositionCoordinate & latitude, const TPositionCoordinate & longitude)
        : CCoordinates<TPositionCoordinate>(latitude, longitude) {}

    void setCoordintes(const TPositionCoordinate &latitude, const TPositionCoordinate &longitude) { m_alpha.set(latitude); m_beta.set(longitude); }
    const TPositionCoordinate   & latitude          () const { return m_alpha   .value(); }
    const TPositionCoordinate   & longitude         () const { return m_beta    .value(); }
    const bool                  & isLatitudeValid   () const { return m_alpha .isValid(); }
    const bool                  & isLongitudeValid  () const { return m_beta  .isValid(); }
};

//typedef QList<CPositionCoordinates> TPositionCoordinatesList;

}

#endif // CCOORDINATESPOSITION_H
