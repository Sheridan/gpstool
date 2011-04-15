#ifndef COPTIONPOINTF_H
#define COPTIONPOINTF_H

#include "coption.h"
#include <QMap>
#include <QObject>
#include <QPointF>
namespace options
{

class COptionPointF : public QObject, public COption<QPointF>
{
    Q_OBJECT
public: // ####################################################
    COptionPointF(COptions *parent, const QString &section, const QString &key, const QPointF &defaultValue)
        : QObject(), COption<QPointF>(parent, section, key, defaultValue) { load(); }
        ~COptionPointF() { save(); }
protected: // ####################################################
    void load();
    void save();
    void emitChanged() { emit changed(value()); emit changed(); };
signals: // ####################################################
    void changed(const QPointF &);
    void changed();

};

typedef QMap<QString, COptionPointF *> TOptionsPointF;

}

#endif // COPTIONPOINTF_H
