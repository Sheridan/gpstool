#ifndef CBOOLOPTION_H
#define CBOOLOPTION_H

#include "coption.h"
#include <QObject>
#include <QMap>

namespace options
{

class COptionBool : public QObject, public COption<bool>
{
    Q_OBJECT
public: // ####################################################
    COptionBool(COptions *parent, const QString &section, const QString &key, const bool &defaultValue)
        : QObject(), COption<bool>(parent, section, key, defaultValue) { load(); }
        ~COptionBool() { save(); }
protected: // ####################################################
    void load();
    void save();
    void emitChanged() { emit changed(value()); emit changed(); };
signals: // ####################################################
    void changed(const bool &);
    void changed();

};

typedef QMap<QString, COptionBool *> TOptionsBool;

}
#endif // CBOOLOPTION_H
