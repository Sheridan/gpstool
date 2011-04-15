#ifndef COPTIONTIME_H
#define COPTIONTIME_H

#include "coption.h"
#include <QObject>
#include <QMap>
#include <QTime>
namespace options
{

class COptionTime : public QObject, public COption<QTime>
{
    Q_OBJECT
public: // ####################################################
    COptionTime(COptions *parent, const QString &section, const QString &key, const QTime &defaultValue)
        : QObject(), COption<QTime>(parent, section, key, defaultValue) { load(); }
        ~COptionTime() { save(); }
protected: // ####################################################
    void load();
    void save();
    void emitChanged() { emit changed(value()); emit changed(); };
signals: // ####################################################
    void changed(const QTime &);
    void changed();

};

typedef QMap<QString, COptionTime *> TOptionsTime;

}

#endif // COPTIONTIME_H
