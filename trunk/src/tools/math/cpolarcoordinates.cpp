#include "cpolarcoordinates.h"
#include <math.h>

namespace math
{

namespace polar
{
// --------------------------------------------------------------------------------------------------------------------------------------
QRectF getCircle(const qreal & lengthC, const qreal & angleC, const qreal & radius)
{
    QPointF center = polarToDecard(lengthC, angleC);
    return QRectF
        (
            center.rx() - radius,
            center.ry() - radius,
            radius*2,
            radius*2
        );
}
// --------------------------------------------------------------------------------------------------------------------------------------
QRectF getRect(const qreal & lengthLT, const qreal & angleLT, const qreal & lengthRB, const qreal & angleRB)
{
    return QRectF(polarToDecard(lengthLT, angleLT), polarToDecard(lengthRB, angleRB));
}
// --------------------------------------------------------------------------------------------------------------------------------------
QLineF getLine(const qreal & lengthF, const qreal & angleF, const qreal & lengthT, const qreal & angleT)
{
    return QLineF(polarToDecard(lengthF, angleF), polarToDecard(lengthT, angleT));
}
// --------------------------------------------------------------------------------------------------------------------------------------
QPointF getPoint(const qreal & length, const qreal & angle)
{
    return polarToDecard(length, angle);
}
// --------------------------------------------------------------------------------------------------------------------------------------
QPointF polarToDecard(const qreal & length, const qreal & fi)
{
    qreal realFi = (fi - 90)*M_PI/180;
    return QPointF
        (
            length * cos(realFi),
            length * sin(realFi)
        );
}


}
}
