#include "csatellitesbackground.h"
#include "cgraphicsscene.h"
#include "csatelliteitem.h"
#include "cpolarcoordinates.h"
#include <QDebug>

#define __lineAnglesStep 30
#define __maxRadius 110
#define prepare_scale(_from) float __scale = ((_from/2)/__maxRadius)
#define item_scale __scale

#define satellite_real_size 35
#define prepare_satellite_size QSizeF _satSize(__scale*satellite_real_size, __scale*satellite_real_size)
#define satellite_size _satSize

namespace ui
{
namespace graphics
{
// --------------------------------------------------------------------------------------------------------------------------------------
CSatellitesBackground::CSatellitesBackground() : CCachedGraphicsItem(gitSomething), gps::CGpsDataUpdateInterfaseBase()
{
    setObjectName("SatellitesBackground");
    QColor colorGrad("lightsteelblue");
    colorGrad.setAlpha(150);

    m_circleGradient.setColorAt(0    , m_transparentColor );
    m_circleGradient.setColorAt(0.7  , m_transparentColor );
    m_circleGradient.setColorAt(1    , colorGrad         );

    m_wSidesFont     = QFont(m_stdFont);
    m_azimuthFont    = QFont(m_stdFont);
    m_elevationFont  = QFont(m_stdFont);
    m_wSidesFont     .setPointSizeF(10);
    m_azimuthFont    .setPointSizeF(6);
    m_elevationFont  .setPointSizeF(4);

    m_nordColor  .setNamedColor  ("steelblue");
    m_nordColor  .setAlpha       (150);
    m_southColor .setNamedColor  ("crimson");
    m_southColor .setAlpha       (150);

    for(int i = 90; i >= 10; i -= 10)
    {
        m_elevations[i] = QString("%1%2").arg(90-i).arg(QChar(176));
    }

    for(int i = 0; i < 360; i+=__lineAnglesStep)
    {
        m_angles[i] = QString("%1%2").arg(i).arg(QChar(176));
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
CSatellitesBackground::~CSatellitesBackground()
{}
// --------------------------------------------------------------------------------------------------------------------------------------
void CSatellitesBackground::paintToCache(QPainter * painter)
{
    prepare_scale(size().width());
    painter->translate(size().width()/2, size().height()/2);
    painter->scale(item_scale, item_scale);
    painter->setOpacity(0.5);

    // circles
    for(int i = 90; i >= 10; i -= 10)
    {
        m_circleGradient.setRadius(i);
        painter->setBrush(QBrush(m_circleGradient));
        painter->drawEllipse(math::polar::getCircle(0,0,i));
    }

    painter->setBrush(m_stdBrush);
    // lines
    for(int i = 0; i < 360; i+=__lineAnglesStep)
    {
        painter->drawLine(math::polar::getLine(5,i,95,i));
    }

    // arrows
    painter->setPen(QPen(QColor(0,0,0,0)));
    // North
    painter->setBrush(QBrush(m_nordColor));
    painter->drawPolygon(QPolygonF()
        << QPointF(-15, 0)
        << QPointF(0,-95)
        << QPointF(15, 0)
        << QPointF(-15, 0)
        );
    // South
    painter->setBrush(QBrush(m_southColor));
    painter->drawPolygon(QPolygonF()
        << QPointF(-15, 0)
        << QPointF(0,95)
        << QPointF(15, 0)
        << QPointF(-15, 0)
        );
    painter->setPen(m_stdPen);
    painter->setBrush(m_stdBrush);

    //text
    painter->setFont(m_elevationFont);
    for(int i = 90; i >= 10; i -= 10)
    {
        for(int j = 0; j < 360; j+=__lineAnglesStep)
        {
            painter->drawText(QPointF(1, -i-1), m_elevations[i]);
            painter->rotate(__lineAnglesStep);
        }
    }
    painter->setFont(m_azimuthFont);
    for(int i = 0; i < 360; i+=__lineAnglesStep)
    {
        painter->drawText(QPointF(1, -96), m_angles[i]);
        painter->rotate(__lineAnglesStep);
    }
    painter->setFont(m_wSidesFont);
    painter->drawText(QRectF(-30, -110, 60, 10), Qt::AlignCenter, tr("North"));
    painter->rotate(90);
    painter->drawText(QRectF(-30, -110, 60, 10), Qt::AlignCenter, tr("East"));
    painter->rotate(90);
    painter->drawText(QRectF(-30, -110, 60, 10), Qt::AlignCenter, tr("South"));
    painter->rotate(90);
    painter->drawText(QRectF(-30, -110, 60, 10), Qt::AlignCenter, tr("West"));
    painter->rotate(90);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CSatellitesBackground::boundingRectChanged()
{
    updateCache();
    prepare_scale(size().width());
    prepare_satellite_size;
    foreach(QGraphicsItem *item, childItems())
    {
        static_cast<CSatelliteItem *>(item)->resize(satellite_size);
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CSatellitesBackground::updateSatellites(const data::TSatellitesData &satellites)
{
    prepare_scale(size().width());
    prepare_satellite_size;
    CSatelliteItem *satItem = NULL;
    bool itemExists;
    foreach(data::CSatelliteData *satellite, satellites)
    {
        if (satellite->isEmpty())
        {
            continue;
        }
        itemExists = false;
        foreach(QGraphicsItem *item, childItems())
        {
            satItem = static_cast<CSatelliteItem *>(item);
            if(satItem->satellite()->isEqual(satellite))
            {
                itemExists = true;
                break;
            }
        }
        if(!itemExists)
        {
            satItem = new CSatelliteItem(this);
            satItem->setSize(satellite_size);
        }
        satItem->setSatellite(satellite);
        QPointF satPos = math::polar::getPoint(90-satellite->elevation(), satellite->azimuth());
        satPos = QPointF(satPos.x()*item_scale, satPos.y()*item_scale)+center()-satItem->center();
        //qDebug() << boundingRect() << ": " << satPos << "->" << QPointF(satPos.x()*item_scale, satPos.y()*item_scale)+center()-satItem->center();
        if(itemExists)
        {
            satItem->setPosition(satPos);
        }
        else
        {
            satItem->setPos(satPos);
        }
    }

    foreach(QGraphicsItem *item, childItems())
    {
        CSatelliteItem *satItem = static_cast<CSatelliteItem *>(item);
        if(satItem->canBeRemoved())
        {
            delete satItem;
        }
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CSatellitesBackground::rotate(const int & rotateAngle)
{
    CGraphicsItem::rotate(rotateAngle);
    foreach(QGraphicsItem *item, childItems())
    {
        static_cast<CSatelliteItem *>(item)->rotate(360-rotateAngle);
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CSatellitesBackground::setGps(gps::CGpsSource * value)
{
    disconnectGpsData();
    foreach(QGraphicsItem *item, childItems())
    {
        delete static_cast<CSatelliteItem *>(item);
    }
    rotate(0);
    gps::CGpsDataUpdateInterfaseBase::setGps(value);
    connectGpsData();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CSatellitesBackground::newGpsDataAvialable(const data::CGpsData *segment)
{
    if(segment->isCourseFromNorthValid()) { rotate(segment->courseFromNorth()); }
    updateSatellites(segment->satellites());
}
// --------------------------------------------------------------------------------------------------------------------------------------
bool CSatellitesBackground::gpsDataSegmentIsValid(const data::CGpsData *segment)
{
    return segment->satellitesCount() && segment->isCourseFromNorthValid();
}
// --------------------------------------------------------------------------------------------------------------------------------------
bool CSatellitesBackground::canGpsDataUpdating()
{
    return isActive();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CSatellitesBackground::gpsDataSegmentInvalid()
{
    rotate(0);
    foreach(QGraphicsItem *item, childItems())
    {
        delete static_cast<CSatelliteItem *>(item);
    }
}


}
}
