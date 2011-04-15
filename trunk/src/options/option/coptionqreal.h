#ifndef COPTIONQREAL_H
#define COPTIONQREAL_H
#include "coption.h"
#include <QMap>
#include <QObject>
namespace options
{

class COptionQreal : public QObject, public COption<qreal>
{
    Q_OBJECT
public: // ####################################################
    COptionQreal(COptions *parent, const QString &section, const QString &key, const qreal &defaultValue)
        : QObject(), COption<qreal>(parent, section, key, defaultValue) { load(); }
        ~COptionQreal() { save(); }
protected: // ####################################################
    void load();
    void save();
    void emitChanged() { emit changed(value()); emit changed(); };
signals: // ####################################################
    void changed(const qreal &);
    void changed();

};

typedef QMap<QString, COptionQreal *> TOptionsQreal;

}
#endif // COPTIONQREAL_H

