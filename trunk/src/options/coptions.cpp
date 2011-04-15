//	Author: Sheridan <sheridan@stavcom.ru>, (C) 2006
//	Copyright: See COPYING file that comes with this distribution
//
#include "coptions.h"
#include "gtdebug.h"
namespace options
{
// --------------------------------------------------------------------------------------------------------------------------------------
COptions::COptions() : QSettings()
{}
// --------------------------------------------------------------------------------------------------------------------------------------
COptions::COptions(const QString &filename) : QSettings(filename, QSettings::IniFormat)
{}
// --------------------------------------------------------------------------------------------------------------------------------------
#define GT_OPT_DESTROY(_class, _map) \
{ foreach(_class *o##_class, _map) \
{\
 GT_DEBUG(QString("Option destroy. Class: %1").arg(#_class)); \
    delete o##_class; o##_class = NULL; \
} _map.clear(); }

COptions::~COptions()
{
    GT_OPT_DESTROY(COptionInt     , m_optionsInt     );
    GT_OPT_DESTROY(COptionString  , m_optionsString  );
    GT_OPT_DESTROY(COptionColor   , m_optionsColor   );
    GT_OPT_DESTROY(COptionBool    , m_optionsBool    );
    GT_OPT_DESTROY(COptionText    , m_optionsText    );
    GT_OPT_DESTROY(COptionIcon    , m_optionsIcon    );
    GT_OPT_DESTROY(COptionTime    , m_optionsTime    );
    GT_OPT_DESTROY(COptionQreal   , m_optionsQreal   );
    GT_OPT_DESTROY(COptionPointF  , m_optionsPointF  );
    sync();
}
// --------------------------------------------------------------------------------------------------------------------------------------
QVariant COptions::getSectionValue ( const QString & section, const QString & key, const QVariant & defaultValue )
{
    m_mutex.lock();
    beginGroup ( section );
    QVariant result = value ( key, defaultValue );
    endGroup();
    m_mutex.unlock();
    return result;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void COptions::setSectionValue ( const QString & section, const QString & key, const QVariant & value )
{
    m_mutex.lock();
    beginGroup ( section );
    setValue ( key, value );
    endGroup();
    sync();
    emit optionChanged(section, key, value);
    m_mutex.unlock();
}
// --------------------------------------------------------------------------------------------------------------------------------------
QStringList	COptions::sectionKeys(const QString & section)
{
    m_mutex.lock();
    beginGroup ( section );
    QStringList keys = childKeys();
    endGroup();
    m_mutex.unlock();
    return keys;
}
// --------------------------------------------------------------------------------------------------------------------------------------
const QStringList COptions::sections()
{
    return childGroups();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void COptions::removeSectionValue(const QString &section, const QString & key)
{
    m_mutex.lock();
    beginGroup ( section );
    remove ( key );
    endGroup();
    m_mutex.unlock();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void COptions::removeSection(const QString & section)
{
    m_mutex.lock();
    beginGroup ( section );
    foreach(QString key, childKeys()) {	remove ( key ); }
    endGroup();
    m_mutex.unlock();
}
// --------------------------------------------------------------------------------------------------------------------------------------
#define GT_OPT_REQUEST(_class, _type, _map) \
_class *COptions::requestOption(const QString & section, const QString & key, const _type &defaultValue) \
{ \
    QString str = QString("%1%2").arg(section).arg(key); \
    GT_DEBUG(QString("Option request. Type: %1 (%2), Section: %3, Key: %4. %5").arg(#_type).arg(#_class).arg(section).arg(key).arg(_map.contains(str) ? "Exists" : "Construct")); \
    if(_map.contains(str)) { return _map.value(str); } \
    _class *opt = new _class(this, section, key, defaultValue); \
    _map[str] = opt; \
    return opt; \
}

GT_OPT_REQUEST(COptionInt    , int      , m_optionsInt    );
GT_OPT_REQUEST(COptionString , QString  , m_optionsString );
GT_OPT_REQUEST(COptionColor  , QRgb     , m_optionsColor  );
GT_OPT_REQUEST(COptionBool   , bool     , m_optionsBool   );
GT_OPT_REQUEST(COptionText   , SText    , m_optionsText   );
GT_OPT_REQUEST(COptionIcon   , QIcon    , m_optionsIcon   );
GT_OPT_REQUEST(COptionTime   , QTime    , m_optionsTime   );
GT_OPT_REQUEST(COptionQreal  , qreal    , m_optionsQreal  );
GT_OPT_REQUEST(COptionPointF , QPointF  , m_optionsPointF );

}
