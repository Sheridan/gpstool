#include "csatelliteitem.h"
#include "st.h"
#include "cpolarcoordinates.h"
#include "optionsdefines.h"
#define __defaultAlpha 100
#define __minSignal 40

#define __maxRadius 50
#define __zoom 1.4
#define __baseCircleRadius __maxRadius/6
#define prepare_scale(_from) float __scale = ((_from/2)/__maxRadius)
#define item_scale __scale

namespace ui
{
namespace graphics
{
// --------------------------------------------------------------------------------------------------------------------------------------
CSatelliteItem::CSatelliteItem(CSatellitesBackground * background) : CCachedGraphicsItem(gitSomething, background)
{
    m_satellite = new data::CSatelliteData();
    m_maxAvialableCount = GT_OPTIONS_APP->requestOption(GT_OPTION_SATELLITE_SIGNAL_WAIT);
    m_usedColor.setNamedColor("lawngreen");
    m_usedColor.setAlpha(__defaultAlpha);
    m_unusedColor.setNamedColor("salmon");
    m_unusedColor.setAlpha(__defaultAlpha);
    m_unavialableColor.setNamedColor("slategray");
    m_unavialableColor.setAlpha(__defaultAlpha);
    m_gaugeBgColor.setNamedColor("oldlace");
    m_gaugeBgColor.setAlpha(__defaultAlpha);
    QColor sigBad("red"), sigGood("gold"), sigBest("chartreuse");
    sigBad.setAlpha(150);
    sigGood.setAlpha(150);
    sigBest.setAlpha(150);
    m_signalGradient.setColorAt(0, sigBad);
    m_signalGradient.setColorAt(0.35, sigGood);
    m_signalGradient.setColorAt(1, sigBest);
    m_signalPen.setStyle(Qt::SolidLine);
    m_signalPen.setCapStyle(Qt::RoundCap);
    m_signalPen.setJoinStyle(Qt::RoundJoin);
    m_signalPen.setWidth(0);
    m_signalFont = QFont(m_stdFont);
    m_prnFont = QFont(m_stdFont);
    m_coordFont = QFont(m_stdFont);
    m_signalFont.setPointSizeF(10);
    m_prnFont.setPointSizeF(14);
    m_coordFont.setPointSizeF(12);

}
// --------------------------------------------------------------------------------------------------------------------------------------
CSatelliteItem::~CSatelliteItem()
{
    delete m_satellite;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CSatelliteItem::paintToCache(QPainter * painter)
{
    painter->translate(size().width()/2, size().height()/2);
    prepare_scale(size().width());
    painter->scale(item_scale, item_scale);

    //painter->setCompositionMode(QPainter::CompositionMode_Source);

    // path
    //QPolygonF path;
    //foreach(gps::SSatelliteCoordinate pathPoint, _pathPoints)
    //{
        //path << _background->satelliteCoordinate(pathPoint.elevation, pathPoint.azimuth);
    //}
    //_pathPen.setWidthF(diameter()/50);
    //painter->setPen(_pathPen);
    //painter->setTransform(QTransform().rotate(-_rotationAngle), true);
    //painter->drawPolyline(path);
    //painter->setTransform(QTransform().rotate(_rotationAngle), true);
    //painter->setPen(_stdPen);

    painter->setBrush(
            QBrush(
                    (m_maxAvialableCount->value() == m_unavialableCount) && !m_satellite->isEmpty() ?
                        (
                            m_satellite->usedInLastFix() ?
                            m_usedColor :
                            m_unusedColor
                        ) :
                        m_unavialableColor
                    ));
    painter->drawEllipse(-__baseCircleRadius, -__baseCircleRadius, __baseCircleRadius*2, __baseCircleRadius*2);
    painter->setBrush(m_stdBrush);

    // sig Db
    // bad - 6, good 12-20, best: > 20
    painter->drawPolyline(QPolygonF()
        << math::polar::getPoint(__baseCircleRadius, 315)
        << QPointF(-40, -32)
        << QPointF(40, -32)
        );
    QRectF signalRect = QRectF(-40, -45, 55, 10);
    painter->drawRect(signalRect);
    m_signalGradient.setStart(signalRect.left(), signalRect.top() + signalRect.height()/2);
    m_signalGradient.setFinalStop(signalRect.right(), signalRect.top() + signalRect.height()/2);
    QBrush signalBrush(m_signalGradient);
    m_signalPen.setBrush(signalBrush);
    painter->setPen(m_signalPen);
    painter->setBrush(QBrush(m_gaugeBgColor));
    qreal sigWidth =
            (
                m_satellite->signalStrength() > __minSignal ?
                __minSignal :
                m_satellite->signalStrength()
            ) * (signalRect.width() / __minSignal);
    painter->setBrush(signalBrush);
    painter->drawRect(QRectF(signalRect.topLeft()+QPointF(1,1), QPointF(signalRect.left()+sigWidth-1, signalRect.bottom()-1)));
    painter->setBrush(QBrush());
    painter->setPen(m_stdPen);
    painter->setFont(m_signalFont);
    painter->drawText(signalRect.bottomRight()+QPointF(5,0), QString("%1dB").arg(m_satellite->signalStrength()));

    // prn
    painter->drawPolyline(QPolygonF()
        << math::polar::getPoint(__baseCircleRadius, 45)
        << math::polar::getPoint(20, 45)
        << math::polar::getPoint(40, 70));
    painter->setFont(m_prnFont);
    painter->drawText(20, -18, QString::number(m_satellite->satPrn()));

    // az/el
    painter->drawPolyline(QPolygonF()
        << math::polar::getPoint(__baseCircleRadius, 135)
        << QPointF(40, 32)
        << QPointF(-40, 33));
    painter->setFont(m_coordFont);
    painter->drawText(-38, 30, QString("Az:%1, El:%2").arg(m_satellite->azimuth()).arg(m_satellite->elevation()));

}
// --------------------------------------------------------------------------------------------------------------------------------------
void CSatelliteItem::boundingRectChanged()
{
    updateCache();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CSatelliteItem::setSatellite(const data::CSatelliteData *data)
{
    m_satellite->set(data);
    m_unavialableCount = m_maxAvialableCount->value();
    updateCache();
}
// --------------------------------------------------------------------------------------------------------------------------------------
const data::CSatelliteData * CSatelliteItem::satellite() const
{
    return m_satellite;
}
// --------------------------------------------------------------------------------------------------------------------------------------
bool CSatelliteItem::canBeRemoved()
{
    m_unavialableCount--;
    return m_unavialableCount <= 0;
}

// --------------------------------------------------------------------------------------------------------------------------------------
void CSatelliteItem::mouseMoveEvent ( QGraphicsSceneMouseEvent * event )
{
    Q_UNUSED(event);
}

}
}
