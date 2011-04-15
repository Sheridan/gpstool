//	Author: Sheridan <sheridan@stavcom.ru>, (C) 2006
//	Copyright: See COPYING file that comes with this distribution
//
#ifndef __COPTIONS_H__
#define __COPTIONS_H__
#include <QSettings>
#include <QMutex>

#include "coptionint.h"
#include "coptionstring.h"
#include "coptioncolor.h"
#include "coptionbool.h"
#include "coptiontext.h"
#include "coptionicon.h"
#include "coptiontime.h"
#include "coptionqreal.h"
#include "coptionpointf.h"

namespace options
{

class COptions : public QSettings
{
    Q_OBJECT
public: // ####################################################

    COptions();
    COptions(const QString &filename);
    virtual ~COptions();

    void removeSection          (const QString & section);
    void removeSectionValue     (const QString &section, const QString & key);
    const QStringList sections  ();

    QStringList	sectionKeys     (const QString & section);
    QVariant getSectionValue    (const QString & section, const QString & key, const QVariant & defaultValue = QVariant() );
    void setSectionValue        (const QString & section, const QString & key, const QVariant & value        = QVariant() );



    COptionInt      * requestOption(const QString & section, const QString & key, const int         &defaultValue);
    COptionString   * requestOption(const QString & section, const QString & key, const QString     &defaultValue);
    COptionColor    * requestOption(const QString & section, const QString & key, const QRgb        &defaultValue);
    COptionBool     * requestOption(const QString & section, const QString & key, const bool        &defaultValue);
    COptionText     * requestOption(const QString & section, const QString & key, const SText       &defaultValue);
    COptionIcon     * requestOption(const QString & section, const QString & key, const QIcon       &defaultValue);
    COptionTime     * requestOption(const QString & section, const QString & key, const QTime       &defaultValue);
    COptionQreal    * requestOption(const QString & section, const QString & key, const qreal       &defaultValue);
    COptionPointF   * requestOption(const QString & section, const QString & key, const QPointF     &defaultValue);

signals: // ####################################################
    void optionChanged(const QString & section, const QString & key, const QVariant &);

protected: // ####################################################
    QMutex          m_mutex;

private: // ####################################################
    TOptionsInt     m_optionsInt;
    TOptionsBool    m_optionsBool;
    TOptionsString  m_optionsString;
    TOptionsColor   m_optionsColor;
    TOptionsText    m_optionsText;
    TOptionsIcon    m_optionsIcon;
    TOptionsTime    m_optionsTime;
    TOptionsQreal   m_optionsQreal;
    TOptionsPointF  m_optionsPointF;
};

}
#endif // __COPTIONS_H__
