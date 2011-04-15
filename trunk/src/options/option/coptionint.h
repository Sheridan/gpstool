#ifndef CINTOPTION_H
#define CINTOPTION_H

#include "coption.h"
#include <QObject>
#include <QMap>
namespace options
{

class COptionInt : public QObject, public COption<int>
{
    Q_OBJECT
public: // ####################################################
    COptionInt(COptions *parent, const QString &section, const QString &key, const int &defaultValue)
        : QObject(), COption<int>(parent, section, key, defaultValue) { load(); }
        ~COptionInt() { save(); }
protected: // ####################################################
    void load();
    void save();
    void emitChanged() { emit changed(value()); emit changed(); };
signals: // ####################################################
    void changed(const int &);
    void changed();
};

typedef QMap<QString, COptionInt *> TOptionsInt;

}
#endif // CINTOPTION_H


