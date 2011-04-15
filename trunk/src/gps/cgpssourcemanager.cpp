#include "cgpssourcemanager.h"
#include "cgpsgpsdsource.h"
#include "gtdebug.h"
#include "st.h"

namespace gps
{
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsSourceManager::CGpsSourceManager() : QThread()
{
    m_activeSource = NULL;
    load();
}
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsSourceManager::~CGpsSourceManager()
{
    foreach (CGpsSource * src, m_allSources)
    {
        emit sourceRemoved(src->id());
        src->stop();
        m_allSources.remove(src->id());
        delete src;
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsSourceManager::run()
{
    exec();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsSourceManager::stop()
{
    quit();
    wait();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsSourceManager::add(const QString &name, const QString &host, const int &port)
{
    gps::CGpsGpsdSource *src = new gps::CGpsGpsdSource(host, port);
    src->setName(name);
    plugSource(src);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsSourceManager::remove(const gps::TGpsSourceId &id)
{
    CGpsSource *src = source(id);
    src->cleanConfig();
    emit sourceRemoved(id);
    m_allSources.remove(id);
    src->stop();
    delete src;
}
// --------------------------------------------------------------------------------------------------------------------------------------
bool CGpsSourceManager::exists(const gps::TGpsSourceId &id)
{
    return m_allSources.contains(id);
}
// --------------------------------------------------------------------------------------------------------------------------------------
TGpsIds CGpsSourceManager::ids()
{
    return m_allSources.keys();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsSourceManager::load()
{
    QStringList sourcesNames = GT_OPTIONS_GPS->sections();
    foreach(QString idStr, sourcesNames)
    {
        EGpsSourceTypes t = static_cast<EGpsSourceTypes>(GT_OPTIONS_GPS->getSectionValue(idStr, "type", static_cast<int>(gstNone)).toInt());
        switch(t)
        {
            case gstGpsd:
            {
                CGpsGpsdSource *src = new CGpsGpsdSource(idStr.toUInt());
                plugSource(src);
                if(src->autoConnect()) { src->connectGps(); }
            }
            break;
            case gstNone: break;
        }
    }
//    TGpsSourcesList online = onlineSources();
//    if(!online.isEmpty()) {
//        setActiveSource(online.first()->id()); }
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsSourceManager::plugSource(CGpsSource *src)
{
    m_allSources.insert(src->id(), src);
    src->start();
    emit newSourceAvialable(src->id());
}
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsSource * CGpsSourceManager::source(const gps::TGpsSourceId &id)
{
    return m_allSources.contains(id) ? m_allSources.value(id) : NULL;
}
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsSource * CGpsSourceManager::source(const QString &name)
{
    foreach (CGpsSource * src, m_allSources)
    {
        if (src->name() == name) { return src; }
    }
    return NULL;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsSourceManager::setActiveSource(const gps::TGpsSourceId &id)
{
    m_activeSource = m_allSources.value(id);
    emit activeSourceUpdated(id);
}
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsSource * CGpsSourceManager::activeSource()
{
    return m_activeSource;
}
// --------------------------------------------------------------------------------------------------------------------------------------
bool CGpsSourceManager::activeSourceIsSet()
{
    return m_activeSource != NULL;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsSourceManager::connectSourceUpdates(const QObject *receiver, const char *newSrcSlot, const char *removeSrcSlot, const char *activeSrcSlot)
{
    connect(this, SIGNAL(emulateNewSourceAvialable(const gps::TGpsSourceId &)), receiver, newSrcSlot, Qt::QueuedConnection);
    foreach(CGpsSource *src, m_allSources)
    {
        emit emulateNewSourceAvialable(src->id());
    }
    if(activeSrcSlot && activeSourceIsSet())
    {
        connect(this, SIGNAL(emulateActiveSourceUpdated(const gps::TGpsSourceId &)), receiver, activeSrcSlot, Qt::QueuedConnection);
        emit emulateActiveSourceUpdated(m_activeSource->id());
    }
    disconnect(receiver);

    connect(this, SIGNAL(newSourceAvialable(const gps::TGpsSourceId &)), receiver, newSrcSlot, Qt::QueuedConnection);
    connect(this, SIGNAL(sourceRemoved(const gps::TGpsSourceId &)), receiver, removeSrcSlot, Qt::QueuedConnection);
    if(activeSrcSlot)
        connect(this, SIGNAL(activeSourceUpdated(const gps::TGpsSourceId &)), receiver, activeSrcSlot, Qt::QueuedConnection);
    GT_DEBUG_ADV
            (
            QString("Object `%1` connected to GPS sources updates").arg(receiver->objectName()),
            QString("newSourceAvialable -> %1\nsourceRemoved -> %2\nactiveSourceUpdated -> %3")
                .arg(newSrcSlot)
                .arg(removeSrcSlot)
                .arg(activeSrcSlot ? activeSrcSlot : "[not connected]")
            );
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsSourceManager::disconnectSourceUpdates(const QObject *receiver)
{
    disconnect(receiver);
    GT_DEBUG
            (
                    QString("Object `%1` disconnected from GPS sources updates").arg(receiver->objectName())
            );
}

}
