#ifndef CSATELLITEDATA_H
#define CSATELLITEDATA_H
#include <QtGlobal>
#include <QList>
#include "ccoordinatessatellite.h"
#include "cvalidatedvalue.h"

namespace data
{

class CSatelliteData
{
public: // ####################################################
    CSatelliteData();
    CSatelliteData(const qint16 &satPrn, const qint16 &signalStrength, const bool &usedInLastFix,
                   const TSatelliteCoordinate & azimuth, const TSatelliteCoordinate & elevation);
    ~CSatelliteData();
    bool isEmpty() const;
    bool isEqual(const CSatelliteData *other) const { return satPrn() == other->satPrn(); }
    void set(const CSatelliteData * other);


    //get
    const qint16                & satPrn()          const { return m_satPrn          .value      (); }
    const qint16                & signalStrength()  const { return m_signalStrength  .value      (); }
    const bool                  & usedInLastFix()   const { return m_usedInLastFix   .value      (); }
    const TSatelliteCoordinate  & azimuth()         const { return m_position        ->azimuth   (); }
    const TSatelliteCoordinate  & elevation()       const { return m_position        ->elevation (); }
private: // ####################################################
    TValidatedInt16           m_satPrn;
    TValidatedInt16           m_signalStrength;
    TValidatedBool            m_usedInLastFix;
    CCoordinatesSatellite   * m_position;
    void init();
};

typedef QList<CSatelliteData *> TSatellitesData;

}
#endif // CSATELLITEDATA_H
