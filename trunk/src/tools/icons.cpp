#include "icons.h"
#include <QPainter>

#define GT_BEGIN_PAINTER(_icon, _painter) \
    QSize size##_painter = _icon.availableSizes()[0]; \
    QImage img##_painter = QImage(size##_painter, QImage::Format_ARGB32); \
    QPainter *_painter = new QPainter(); \
    img##_painter.fill(0); \
    _painter->begin(&img##_painter); \
    _painter->setRenderHint(QPainter::Antialiasing); \
    _painter->setRenderHint(QPainter::HighQualityAntialiasing);

#define GT_RETURN_RESULT(_painter) \
    _painter->end(); \
    delete _painter; \
    return QIcon(QPixmap::fromImage(img##_painter));

namespace tools
{
namespace icons
{
// --------------------------------------------------------------------------------------------------------------------------------------
QIcon stratificateIcons(const QIcon &source, const QIcon &layer)
{
    GT_BEGIN_PAINTER(source, painter);

    painter->drawPixmap(0, 0, source.pixmap(16));
    painter->drawPixmap(0, 0, layer.pixmap(16));

    GT_RETURN_RESULT(painter);
}
// --------------------------------------------------------------------------------------------------------------------------------------
QIcon stratificateIcons(const QString &sourceFile, const QString &layerFile)
{
    return stratificateIcons(QIcon(sourceFile), QIcon(layerFile));
}
// --------------------------------------------------------------------------------------------------------------------------------------
QIcon stratificateIcons	(const QIcon &source, const QString &layerFile)
{
    return stratificateIcons(source, QIcon(layerFile));
}
// --------------------------------------------------------------------------------------------------------------------------------------
QIcon setIconOpacity(const QIcon &icon, float opacity)
{
    GT_BEGIN_PAINTER(icon, painter);

    painter->setOpacity(opacity);
    painter->drawPixmap(0, 0, icon.pixmap(16));

    GT_RETURN_RESULT(painter);
}
// --------------------------------------------------------------------------------------------------------------------------------------
QIcon setIconOpacity(const QString &iconFile, float opacity)
{
    return setIconOpacity(QIcon(iconFile), opacity);
}


}
}
