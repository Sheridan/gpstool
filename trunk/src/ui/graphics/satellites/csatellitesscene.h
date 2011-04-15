#ifndef CSAtellITESSCENE_H
#define CSAtellITESSCENE_H

#include "cgraphicsscene.h"
#include "csatellitesbackground.h"
#include "csatelliteitem.h"
//#include <QList>

namespace ui
{
namespace graphics
{

class CSatellitesScene : public CGraphicsScene
{
    Q_OBJECT
private: // ####################################################
    CSatellitesBackground * m_satelliteBackground;

public: // ####################################################
    CSatellitesScene();
    virtual ~CSatellitesScene();

private slots: // ####################################################
    void updateActiveGps(const gps::TGpsSourceId & id);
    void sceneRectHasBeenChanged (const QRectF & rect);
};

}
}
#endif
