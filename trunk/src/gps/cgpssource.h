#ifndef CGPSSOURCEBASE_H
#define CGPSSOURCEBASE_H
#include <QThread>
#include <QRgb>
#include <QTimer>
#include <QList>
#include "cgpsdata.h"
#include "coptionint.h"
#include "coptionbool.h"
#include "coptioncolor.h"
#include "coptionicon.h"
#include "coptionstring.h"
#include "gpsdefines.h"
#include "cid.h"
namespace gps
{

enum EGpsSourceTypes
{
    gstNone,
    #define gstNone gps::gstNone
    gstGpsd
    #define gstGpsd gps::gstGpsd
};

class CGpsSourceManager;

class CGpsSource : public QThread, public tools::CId
{
    Q_OBJECT
public: // ####################################################
    CGpsSource(EGpsSourceTypes gpsType, TGpsSourceId id_val = 0);
    virtual ~CGpsSource();
    void run();
    void cleanConfig();

    const int               & updatePeriod  () const { return m_updatePeriod    ->value(); }
    const bool              & autoConnect   () const { return m_autoConnect     ->value(); }
    const QString           & name          () const { return m_name            ->value(); }
    const QRgb              & color         () const { return m_color           ->value(); }
    const EGpsSourceTypes   & type          () const { return m_type;                      }
    const QIcon             & icon          () const { return m_icon            ->value(); }

    virtual bool            connectGps          () = 0; // connect to gps
    virtual void            disconnectGps       () = 0; // disconnect from gps
    virtual bool            isGpsConnected      () = 0; // connected or no
    virtual void            showOptionsDialog   () = 0; // advanced gps settings
    virtual QString         gpsInfo             () = 0; // gps info: name, type, etc...

    bool connectNewData     (const QObject *reciever, const char *slot);
    bool disconnectNewData  (const QObject *reciever);

private: // ####################################################
    options::COptionString      * m_name;
    options::COptionColor       * m_color;
    options::COptionBool        * m_autoConnect;
    options::COptionInt         * m_updatePeriod;
    options::COptionIcon        * m_icon;
    EGpsSourceTypes               m_type;
    unsigned int                  m_updateReceivers;

protected: // ####################################################
    QTimer                      * m_timer;
    const unsigned int          & updateReceivers() { return m_updateReceivers; }
    virtual void                  threadStop     () = 0;

protected slots: // ####################################################
    virtual void update()       = 0;

public slots: // ####################################################
    void changeStatus   ();
    void setAutoConnect (bool            value) { m_autoConnect  ->set(value); }
    void setName        (const QString & value) { m_name         ->set(value); }
    void setUpdatePeriod(const int     & value);
    void setColor       (const QRgb    & value) { m_color        ->set(value); }
    void setIcon        (const QIcon   & value) { m_icon         ->set(value); }
    void stop();

private slots: // ####################################################
    void sendConnected()    { emit connected(true);  }
    void sendDisconnected() { emit connected(false); }

signals: // ####################################################
    void updateBegin        ();
    void updateEnd          ();
    void statusChanging     ();
    void connectionError    ();
    void disconnected       ();
    void connected          ();
    void connected          (bool);
    void unusable           ();
    void usable             ();
    //data
    void newDataAvialable   (const data::CGpsData *);
};

}
#endif
