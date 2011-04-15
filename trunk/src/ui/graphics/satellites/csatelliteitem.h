#ifndef CSAtellITEITEM_H
#define CSAtellITEITEM_H
#include <QHash>
#include "csatellitesbackground.h"
#include "csatellitedata.h"
#include "coptionint.h"

namespace ui
{
namespace graphics
{

class CSatelliteItem : public CCachedGraphicsItem
{
    Q_OBJECT
public: // ####################################################
    CSatelliteItem                              (CSatellitesBackground * background);
    virtual ~CSatelliteItem                     ();
    void                         setSatellite   (const data::CSatelliteData *data);
    const data::CSatelliteData * satellite      () const;
    bool                         canBeRemoved   ();

private: // ####################################################
    void paintToCache       (QPainter * painter);
    void boundingRectChanged();
    QColor                    m_usedColor;
    QColor                    m_unusedColor;
    QColor                    m_unavialableColor;
    QColor                    m_gaugeBgColor;
    QLinearGradient           m_signalGradient;
    QPen                      m_signalPen;
    data::CSatelliteData    * m_satellite;
    char                      m_unavialableCount;
    options::COptionInt     * m_maxAvialableCount;
    QFont                     m_signalFont;
    QFont                     m_prnFont;
    QFont                     m_coordFont;
    void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );

};

typedef QHash<int, CSatelliteItem *> TSatellitesItems;

}
}
#endif
