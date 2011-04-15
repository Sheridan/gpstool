#ifndef COPTIONICON_H
#define COPTIONICON_H

#include "coption.h"
#include <QObject>
#include <QMap>
#include <QIcon>

namespace options
{

class COptionIcon : public QObject, public COption<QIcon>
{
    Q_OBJECT
public: // ####################################################
    COptionIcon(COptions *parent, const QString &section, const QString &key, const QIcon &defaultValue)
        : QObject(), COption<QIcon>(parent, section, key, defaultValue) { load(); }
        ~COptionIcon() { save(); }
protected: // ####################################################
    void load();
    void save();
    void emitChanged() { emit changed(value()); emit changed(); };

signals: // ####################################################
    void changed(const QIcon &);
    void changed();

};

typedef QMap<QString, COptionIcon *> TOptionsIcon;

}
#endif // COPTIONICON_H
