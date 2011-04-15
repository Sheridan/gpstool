#ifndef CGPSDATA_H
#define CGPSDATA_H
#include <QString>
#include "cmode.h"
#include "cstatus.h"
#include "ccoordinatesposition.h"
#include "csatellitedata.h"
#include "cvalidatedvalue.h"
#include "gpsdefines.h"

namespace data
{

class CGpsData
{
public: // ####################################################
    CGpsData(const QString &srcName, const gps::TGpsSourceId &srcId, const quint16 &ttl);
    ~CGpsData();
    void free() const;

    // set
    void setTimestamp           (const double  &value) { m_timestamp                    .set(value); }
    void setCourseFromNorth     (const float   &value) { m_courseFromNorth              .set(value); }
    void setAltitude            (const float   &value) { m_altitude                     .set(value); }
    void setSpeedOverGround     (const float   &value) { m_speedOverGround              .set(value); }
    void setRateOfClimb         (const float   &value) { m_rateOfClimb                  .set(value); }
    void setMode                (const EMode   &value) { m_mode                         .set(value); }
    void setStatus              (const EStatus &value) { m_status                       .set(value); }
    void setSatellitesSentence  (const QString &value) { m_satellitesSentence           .set(value); }
    void setPositionQualityH    (const float   &value) { m_positionQualityHorizontal    .set(value); }
    void setPositionQualityV    (const float   &value) { m_positionQualityVertical      .set(value); }
    void setPositionQualityT    (const float   &value) { m_positionQualityTotal         .set(value); }

    void setPosition            (const TPositionCoordinate & latitude,
                                 const TPositionCoordinate & longitude)
                                                        { m_position->setCoordintes(latitude, longitude); }

    void setDilutionOfPrecision (const quint8 &satellitesInLastFix  ,
                                 const float  &dopSpherical         ,
                                 const float  &dopHorizontal        ,
                                 const float  &dopVertical          ,
                                 const float  &dopTime              ,
                                 const float  &dopTotalGeometric    )
                                                        {   m_satellitesInLastFix    .set(satellitesInLastFix  ) ;
                                                            m_dopSpherical           .set(dopSpherical         ) ;
                                                            m_dopHorizontal          .set(dopHorizontal        ) ;
                                                            m_dopVertical            .set(dopVertical          ) ;
                                                            m_dopTime                .set(dopTime              ) ;
                                                            m_dopTotalGeometric      .set(dopTotalGeometric    ) ; }

    void appendSatellite        (const qint16               &satPrn         ,
                                 const qint16               &signalStrength ,
                                 const bool                 &usedInLastFix  ,
                                 const TSatelliteCoordinate & azimuth       ,
                                 const TSatelliteCoordinate & elevation     )
                                                        { m_satellites.append(new CSatelliteData(satPrn          ,
                                                                                                 signalStrength  ,
                                                                                                 usedInLastFix   ,
                                                                                                 azimuth         ,
                                                                                                 elevation       )); }

    // get
    const double    & timestamp                     () const { return m_timestamp                    .value(); }
    const float     & courseFromNorth               () const { return m_courseFromNorth              .value(); }
    const float     & altitude                      () const { return m_altitude                     .value(); }
    const float     & speedOverGround               () const { return m_speedOverGround              .value(); }
    const float     & rateOfClimb                   () const { return m_rateOfClimb                  .value(); }
    const float     & dopSpherical                  () const { return m_dopSpherical                 .value(); }
    const float     & dopHorizontal                 () const { return m_dopHorizontal                .value(); }
    const float     & dopVertical                   () const { return m_dopVertical                  .value(); }
    const float     & dopTime                       () const { return m_dopTime                      .value(); }
    const float     & dopTotalGeometric             () const { return m_dopTotalGeometric            .value(); }
    const float     & positionQualityHorizontal     () const { return m_positionQualityHorizontal    .value(); }
    const float     & positionQualityVertical       () const { return m_positionQualityVertical      .value(); }
    const float     & positionQualityTotal          () const { return m_positionQualityTotal         .value(); }
    const EMode     & mode                          () const { return m_mode                         .value(); }
    const EStatus   & status                        () const { return m_status                       .value(); }
    const quint8    & satellitesInLastFix           () const { return m_satellitesInLastFix          .value(); }
    const QString   & satellitesSentence            () const { return m_satellitesSentence           .value(); }
    const QString   & gpsSourceName                 () const { return m_gpsSourceName                        ; }
    const gps::TGpsSourceId     & gpsSourceId       () const { return m_gpsSourceId                          ; }
    const TPositionCoordinate   & latitude          () const { return m_position->latitude                 (); }
    const TPositionCoordinate   & longitude         () const { return m_position->longitude                (); }
    const TSatellitesData       & satellites        () const { return m_satellites                           ; }
    quint8                        satellitesCount   () const { return m_satellites.count                   (); }

    // valid
    const bool & isTimestampValid                   () const { return m_timestamp                    .isValid(); }
    const bool & isCourseFromNorthValid             () const { return m_courseFromNorth              .isValid(); }
    const bool & isAltitudeValid                    () const { return m_altitude                     .isValid(); }
    const bool & isSpeedOverGroundValid             () const { return m_speedOverGround              .isValid(); }
    const bool & isRateOfClimbValid                 () const { return m_rateOfClimb                  .isValid(); }
    const bool & isDopSphericalValid                () const { return m_dopSpherical                 .isValid(); }
    const bool & isDopHorizontalValid               () const { return m_dopHorizontal                .isValid(); }
    const bool & isDopVerticalValid                 () const { return m_dopVertical                  .isValid(); }
    const bool & isDopTimeValid                     () const { return m_dopTime                      .isValid(); }
    const bool & isDopTotalGeometricValid           () const { return m_dopTotalGeometric            .isValid(); }
    const bool & isPositionQualityHorizontalValid   () const { return m_positionQualityHorizontal    .isValid(); }
    const bool & isPositionQualityVerticalValid     () const { return m_positionQualityVertical      .isValid(); }
    const bool & isPositionQualityTotalValid        () const { return m_positionQualityTotal         .isValid(); }
    const bool & isSatellitesInLastFixValid         () const { return m_satellitesInLastFix          .isValid(); }
    const bool & isModeValid                        () const { return m_mode                         .isValid(); }
    const bool & isStatusValid                      () const { return m_status                       .isValid(); }
    const bool & isSatellitesSentenceValid          () const { return m_satellitesSentence           .isValid(); }
    const bool & isLatitudeValid                    () const { return m_position->isLatitudeValid            (); }
    const bool & isLongitudeValid                   () const { return m_position->isLongitudeValid           (); }
//	const bool & isValid () const { return .isValid(); }

private: // ####################################################
    TValidatedDouble        m_timestamp                 ;
    TValidatedFloat         m_courseFromNorth           ;
    TValidatedFloat         m_altitude                  ;
    TValidatedFloat         m_speedOverGround           ;
    TValidatedFloat         m_rateOfClimb               ;
    TValidatedFloat         m_dopSpherical              ;
    TValidatedFloat         m_dopHorizontal             ;
    TValidatedFloat         m_dopVertical               ;
    TValidatedFloat         m_dopTime                   ;
    TValidatedFloat         m_dopTotalGeometric         ;
    TValidatedFloat         m_positionQualityHorizontal ;
    TValidatedFloat         m_positionQualityVertical   ;
    TValidatedFloat         m_positionQualityTotal      ;
    TValidatedMode          m_mode                      ;
    TValidatedStatus        m_status                    ;
    TValidatedUInt8         m_satellitesInLastFix       ;
    TValidatedString        m_satellitesSentence        ;
    QString                 m_gpsSourceName             ;
    gps::TGpsSourceId       m_gpsSourceId               ;
    TSatellitesData         m_satellites                ;
    CCoordinatesPosition  * m_position                  ;
    mutable quint16         m_ttl                       ;
};

}

#endif // CGPSDATA_H
