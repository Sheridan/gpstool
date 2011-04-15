#ifndef COPTIONTEXT_H
#define COPTIONTEXT_H

#include "coption.h"
#include <QObject>
#include <QMap>
#include <QStringList>

namespace options
{

struct SText
{
    QString text;
    SText() { text = ""; }
    SText(const QString & t) { text = t; }
};

class COptionText : public QObject, public COption<SText>
{
    Q_OBJECT
public: // ####################################################
    COptionText(COptions *parent, const QString &section, const QString &key, const SText &defaultValue)
        : QObject(), COption<SText>(parent, section, key, defaultValue) { load(); }
    ~COptionText() { save(); }
    void set(const QString & value) { COption<SText>::set(SText(value)); };
protected: // ####################################################
    void load();
    void save();
    void emitChanged() { emit changed(value()); emit changed(); };
signals: // ####################################################
    void changed(const SText &);
    void changed();

};

typedef QMap<QString, COptionText *> TOptionsText;

}

#endif // COPTIONTEXT_H
