#ifndef CCOLOROPTION_H
#define CCOLOROPTION_H

#include "coption.h"
#include <QObject>
#include <QRgb>
#include <QMap>

namespace options
{

class COptionColor : public QObject, public COption<QRgb>
{
    Q_OBJECT
public: // ####################################################
    COptionColor(COptions *parent, const QString &section, const QString &key, const QRgb &defaultValue)
        : QObject(), COption<QRgb>(parent, section, key, defaultValue) { load(); }
        ~COptionColor() { save(); }
protected: // ####################################################
    void load();
    void save();
    void emitChanged() { emit changed(value()); emit changed(); };
signals: // ####################################################
    void changed(const QRgb &);
    void changed();

};

typedef QMap<QString, COptionColor *> TOptionsColor;

}
#endif // CCOLOROPTION_H
