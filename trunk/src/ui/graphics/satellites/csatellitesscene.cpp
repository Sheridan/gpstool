#include "csatellitesscene.h"
#include "st.h"
#include "optionsdefines.h"
#include <QPropertyAnimation>
namespace ui
{
namespace graphics
{
// --------------------------------------------------------------------------------------------------------------------------------------
CSatellitesScene::CSatellitesScene() : CGraphicsScene("satellite_scene")
{
    m_satelliteBackground = new CSatellitesBackground();
    addItem(m_satelliteBackground);
    connect(GT_GPS_MANAGER, SIGNAL(activeSourceUpdated(const gps::TGpsSourceId &)), this, SLOT(updateActiveGps(const gps::TGpsSourceId &)));
    connect(this, SIGNAL(sceneRectChanged(QRectF)), this, SLOT(sceneRectHasBeenChanged(QRectF)));
}
// --------------------------------------------------------------------------------------------------------------------------------------
CSatellitesScene::~CSatellitesScene()
{
    delete m_satelliteBackground;
}

// --------------------------------------------------------------------------------------------------------------------------------------
void CSatellitesScene::updateActiveGps(const gps::TGpsSourceId & id)
{
    m_satelliteBackground->setGps(GT_GPS_MANAGER->source(id));
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CSatellitesScene::sceneRectHasBeenChanged(const QRectF & rect)
{
    m_satelliteBackground->resize(rect.size());
    m_satelliteBackground->setPosition(rect.topLeft());
}

}
}
