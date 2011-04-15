#ifndef CGPSSOURCEMANAGER_H
#define CGPSSOURCEMANAGER_H
#include <QThread>
#include <QMap>
#include <QList>
#include <QString>
#include <QStringList>
#include "cgpssource.h"
#include "cgpsgpsdsource.h"
#include "coptionsgps.h"

namespace gps
{

typedef QList<gps::TGpsSourceId> TGpsIds;
typedef QMap <gps::TGpsSourceId, CGpsSource *> TGpsSourcesMap;

class CGpsSourceManager : public QThread
{
    Q_OBJECT

public: // ####################################################
    CGpsSourceManager();
    ~CGpsSourceManager();
    void             load               ();
    TGpsIds          ids                ();
    CGpsSource     * source             (const gps::TGpsSourceId &id);
    CGpsSource     * source             (const QString &name);
    void             add                (const QString &name, const QString &host, const int &port);
    void             remove             (const gps::TGpsSourceId &id);
    bool             exists             (const gps::TGpsSourceId &id);
    CGpsSource     * activeSource       ();
    bool             activeSourceIsSet  ();
    void             run                ();
    void connectSourceUpdates   (const QObject *receiver, const char *newSrcSlot, const char *removeSrcSlot, const char *activeSrcSlot = 0);
    void disconnectSourceUpdates(const QObject *receiver);

private: // ####################################################
    TGpsSourcesMap        m_allSources;
    CGpsSource          * m_activeSource;
    void plugSource(CGpsSource *src);

public slots: // ####################################################
    void setActiveSource            (const gps::TGpsSourceId &id);
    void stop();

signals: // ####################################################
    void newSourceAvialable         (const gps::TGpsSourceId &);
    void sourceRemoved              (const gps::TGpsSourceId &);
    void activeSourceUpdated        (const gps::TGpsSourceId &);

    void emulateNewSourceAvialable  (const gps::TGpsSourceId &);
    void emulateActiveSourceUpdated (const gps::TGpsSourceId &);
};

}
#endif
