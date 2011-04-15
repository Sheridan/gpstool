#ifndef CSTRINGOPTION_H
#define CSTRINGOPTION_H

#include "coption.h"
#include <QObject>
#include <QMap>

namespace options
{

class COptionString : public QObject, public COption<QString>
{
    Q_OBJECT
public: // ####################################################
    COptionString(COptions *parent, const QString &section, const QString &key, const QString &defaultValue)
        : QObject(), COption<QString>(parent, section, key, defaultValue) { load(); }
        ~COptionString() { save(); }
protected: // ####################################################
    void load();
    void save();
    void emitChanged() { emit changed(value()); emit changed(); };
signals: // ####################################################
    void changed(const QString &);
    void changed();

};

typedef QMap<QString, COptionString *> TOptionsString;

}
#endif // CSTRINGOPTION_H
