#ifndef CSAtellITESBACKGROUND_H
#define CSAtellITESBACKGROUND_H

#include <QRadialGradient>
#include "ccachedgraphicsitem.h"
#include "csatellitedata.h"
#include "cgpsdata.h"
#include "cgpssource.h"
#include "cgpsdataupdateinterfasebase.h"

namespace ui
{
namespace graphics
{

typedef QMap<int, QString> TStrings;

class CSatellitesBackground : public CCachedGraphicsItem, public gps::CGpsDataUpdateInterfaseBase
{
    Q_OBJECT
    GT_GPSUPDATEINTERFACE_CONNECTION;

public: // ####################################################
    CSatellitesBackground   ();
    ~CSatellitesBackground  ();
    void updateSatellites   (const data::TSatellitesData &satellites);
    void rotate             (const int & rotateAngle);
    void setGps             (gps::CGpsSource * value);

private: // ####################################################
    void boundingRectChanged();
    void paintToCache(QPainter * painter);
    QRadialGradient       m_circleGradient;
    QColor                m_nordColor;
    QColor                m_southColor;
    QFont                 m_wSidesFont;
    QFont                 m_azimuthFont;
    QFont                 m_elevationFont;
    TStrings              m_elevations;
    TStrings              m_angles;

    void newGpsDataAvialable  (const data::CGpsData *segment);
    bool gpsDataSegmentIsValid(const data::CGpsData *segment);
    bool canGpsDataUpdating   (                             );
    void gpsDataSegmentInvalid(                             );

private slots:  // ####################################################
  void gpsDataIncoming(const data::CGpsData *segment) { gpsDataIncomingBase(segment); }
};

}
}
#endif
