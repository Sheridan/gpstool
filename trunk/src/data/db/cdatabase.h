#ifndef CDATABASE_H
#define CDATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDriver>
#include <QObject>
#include <QVariantList>
#include <QThread>
#include <QList>
#include <QMutex>
#include "coptionstring.h"


namespace data
{
namespace db
{

class CDatabase : public QThread
{
    Q_OBJECT
public: // ####################################################
    CDatabase               (const QString& name);
    virtual ~CDatabase      ();
    void    selectDatabase  ();
    QString dbFile          () { return m_dbFile->value(); }
    bool    isOpen          () { return m_db.isOpen();     }
    bool    open            ();

    virtual void run() = 0;

protected: // ####################################################
    options::COptionString *m_dbFile;
    QSqlDatabase            m_db;

    QString   lastErrorToLogDescription (const QSqlError& sqlError, const QString& sql, const QVariantList &parameters = QVariantList());
    QString   readableSql               (QString sql);
    QString   parametresToString        (const QVariantList &parameters);
    void      create                    (const QString &resourceDdl);
    void      close                     ();
    QSqlQuery execQuery                 (const QString &sql, const QVariantList &parameters = QVariantList(), bool isExec = false);
    QSqlQuery query                     (const QString &sql, const QVariantList &parameters = QVariantList());
    bool      exec                      (const QString &sql, const QVariantList &parameters = QVariantList());

    virtual void afterDatabaseOpen  () = 0;
    virtual void beforeDatabaseClose() = 0;
    virtual void create             () = 0;

public slots: // ####################################################
    void stop();

signals: // ####################################################
    void readStart     ();
    void writeStart    ();
    void operationDone ();
    void disconnected  ();
    void connected     ();
};

}
}
#endif // CDATABASE_H
