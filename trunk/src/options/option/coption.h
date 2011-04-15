#ifndef COPTION_H
#define COPTION_H

#include <QString>
#include <QMutex>

namespace options
{
class COptions;
template <typename T> class COption
{
public: // ####################################################
    COption(COptions *parent, const QString &optSection, const QString &optKey, const T &optDefaultValue)
    {
        m_mutex.lock();
        m_parent         = parent;
        m_section        = optSection;
        m_key            = optKey;
        m_defaultValue   = optDefaultValue;
        m_mutex.unlock();
        reset();
    }

    virtual ~COption()                          {                                                                           }
    const T & value () const                    { return m_value;                                                           }
    void reset      ()                          { m_mutex.lock(); m_value   = m_defaultValue;             m_mutex.unlock(); }
    void set        (const T &val)              { m_mutex.lock(); m_value   = val; save(); emitChanged(); m_mutex.unlock(); }
    void setSection (const QString &optSection) { m_mutex.lock(); m_section = optSection;                 m_mutex.unlock(); }
    void setKey     (const QString &optKey)     { m_mutex.lock(); m_key     = optKey;                     m_mutex.unlock(); }
    const QString   & section		()	const   { return m_section;                                                         }
    const QString   & key			()	const   { return m_key;                                                             }
    const T         & defaultValue	()	const   { return m_defaultValue;                                                    }

protected: // ####################################################
    virtual void    load            () = 0;
    virtual void    save            () = 0;
    virtual void    emitChanged     () = 0;
    COptions      * m_parent;

private: // ####################################################
    T       m_value;
    T       m_defaultValue;
    QString m_section;
    QString m_key;
    QMutex  m_mutex;
};

}

#endif // COPTION_H
