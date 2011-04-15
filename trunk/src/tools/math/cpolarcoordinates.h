#ifndef CPOLARCOORDINATES_H
#define CPOLARCOORDINATES_H
#include <QRectF>
#include <QLineF>
#include <QPointF>
#include <QSizeF>

namespace math
{

namespace polar
{
    QPointF polarToDecard   (const qreal & length   , const qreal & fi                                                      );
    QRectF  getCircle       (const qreal & lengthC  , const qreal & angleC  , const qreal & radius                          );
    QRectF  getRect         (const qreal & lengthLT , const qreal & angleLT , const qreal & lengthRB, const qreal & angleRB );
    QLineF  getLine         (const qreal & lengthF  , const qreal & angleF  , const qreal & lengthT , const qreal & angleT  );
    QPointF getPoint        (const qreal & length   , const qreal & angle                                                   );
}

}
#endif
