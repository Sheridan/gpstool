#ifndef GRAPHICSDEFINES_H
#define GRAPHICSDEFINES_H

#include "primitivesdefines.h"

#ifndef QT_NO_DEBUG // ------------------------ Debug -----------------------------------------------------------------

#define GT_DEBUG_GI_DRAW_BORDERS(_painter) \
{ \
    QColor tclr; tclr.setAlpha(0); \
    _painter->setBrush(QBrush(tclr, Qt::SolidPattern)); \
    _painter->setPen(QPen(QBrush(QColor("firebrick")), 1.0, Qt::DotLine)); \
    _painter->drawRect(boundingRect()); \
}
#define GT_GI_PAINTER_MODE(_painter) \
    _painter->setRenderHints(QPainter::TextAntialiasing | QPainter::HighQualityAntialiasing, false); \
    _painter->setRenderHint (QPainter::Antialiasing, true);


#else // ----------------------------------------- Release ------------------------------------------------

#define GT_DEBUG_GI_DRAW_BORDERS(_painter)

#define GT_GI_PAINTER_MODE(_painter) \
    _painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::HighQualityAntialiasing, true);

#endif // -----------------------------------------------------------------------------------------
#endif // GRAPHICSDEFINES_H
