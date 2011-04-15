#include "st.h"
#include "cdatabase.h"
#include "resources.h"
#include "gtdebug.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QSqlDriver>
#include "optionsdefines.h"

#define GT_DB_SESSION_NAME QString("gpstool_%1").arg(objectName())

namespace data
{
namespace db
{
// --------------------------------------------------------------------------------------------------------------------------------------
CDatabase::CDatabase(const QString& name) : QThread()
{
    setObjectName(name);
    m_dbFile = GT_OPTIONS_APP->requestOption(GT_OPTION_GPSDB_FILE(name));
}
// --------------------------------------------------------------------------------------------------------------------------------------
CDatabase::~CDatabase()
{}
// --------------------------------------------------------------------------------------------------------------------------------------
void CDatabase::stop()
{
    close();
    quit();
    wait();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CDatabase::create(const QString &resourceDdl)
{
    QString content = tools::resources::readText(resourceDdl);
    content.replace("\n", " ").replace(QRegExp("\\s+"), " ");
    QStringList sqlStrings = content.split(";");
    foreach(QString sqlLine, sqlStrings)
    {
        if(!sqlLine.isEmpty())
        {
            GT_DEBUG_ADV("Database DDL query", sqlLine);
            exec(sqlLine);
        }
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
bool CDatabase::open()
{
//    if(m_dbFile->)
//    {
//        QMessageBox::warning(NULL, tr("Database..."), tr("Database file for `%1` not selected. Please select it.").arg(objectName()));
//        selectDatabase();
//    }
    close();
    m_db = QSqlDatabase::addDatabase("QSQLITE", GT_DB_SESSION_NAME);
    m_db.setDatabaseName(m_dbFile->value());
    m_db.open();
    QFile dbf(m_dbFile->value());
    if(!dbf.exists() || dbf.size() == 0)
    {
        create();
    }
    if (!m_db.open() || m_db.lastError().isValid())
    {
        GT_LOGGER->append(tr("Database `%1` open error").arg(objectName()),
                         lastErrorToLogDescription(m_db.lastError(),
                                                   QString("Connect to %1").arg(m_dbFile->value()),
                                                   QVariantList()),
                         mtError);
        return false;
    }
    GT_LOGGER->append(tr("Database `%1` opened").arg(objectName()));

    afterDatabaseOpen();
    emit connected();

    return true;
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CDatabase::close()
{
    if(isOpen())
    {
        beforeDatabaseClose();
        m_db.close();
        QSqlDatabase::removeDatabase(GT_DB_SESSION_NAME);
        emit disconnected();
        GT_LOGGER->append(tr("Database `%1` closed").arg(objectName()));
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CDatabase::selectDatabase()
{
    QFileDialog dlg;
    dlg.setWindowTitle(tr("Open `%1` database file").arg(objectName()));
    dlg.setDirectory(QDir::homePath());
    dlg.setFilter(tr("DB file (*.gtdb)"));

    if(dlg.exec() == QDialog::Accepted && dlg.selectedFiles().count() > 0)
    {
        QString fileName = dlg.selectedFiles()[0];
        QFileInfo fi(fileName);
        if(fi.suffix() != "gtdb")
        {
            fileName += ".gtdb";
        }
        m_dbFile->set(fileName);
    }
    open();
}
// --------------------------------------------------------------------------------------------------------------------------------------
QString CDatabase::parametresToString(const QVariantList &parameters)
{
    QString valuesList;
    foreach(QVariant value, parameters)
    {
        valuesList += QString("{%1}").arg(value.toString());
    }
    return valuesList;
}
// --------------------------------------------------------------------------------------------------------------------------------------
QString CDatabase::readableSql(QString sql)
{
    return sql
            .replace(QRegExp("\\s+"), " "                            )
            .replace(", "           , ",\n\t"                        )
            .replace(" from"        , "\nfrom"  , Qt::CaseInsensitive)
            .replace(" where"       , "\nwhere" , Qt::CaseInsensitive)
            .replace(" order"       , "\norder" , Qt::CaseInsensitive)
            .replace(" group"       , "\ngroup" , Qt::CaseInsensitive)
            .replace(" left"        , "\nleft"  , Qt::CaseInsensitive)
            .replace(" right"       , "\nright" , Qt::CaseInsensitive)
            .replace(" inner"       , "\ninner" , Qt::CaseInsensitive)
            .replace(" outer"       , "\nouter" , Qt::CaseInsensitive)
            .replace(" values"      , "\nvalues", Qt::CaseInsensitive)
            ;
}
// --------------------------------------------------------------------------------------------------------------------------------------

QString CDatabase::lastErrorToLogDescription(const QSqlError& sqlError, const QString& sql, const QVariantList &parameters)
{
    QStringList result;
    result.append(tr     ("Database `%1`"    ).arg(objectName     ()));
    result.append(QString("#: %1"            ).arg(sqlError.number()));
    switch(sqlError.type())
    {
        case QSqlError::NoError:          result.append(tr("No error occurred."          )); break;
        case QSqlError::ConnectionError:  result.append(tr("Connection error."           )); break;
        case QSqlError::StatementError:   result.append(tr("SQL statement syntax error." )); break;
        case QSqlError::TransactionError: result.append(tr("Transaction failed error."   )); break;
        case QSqlError::UnknownError:     result.append(tr("Unknown error."              )); break;
    }
    result.append(tr("Database text:"       ));
    result.append(sqlError.databaseText(    ));
    result.append(tr("Database driver text:"));
    result.append(sqlError.driverText(      ));
    if(!sql.isEmpty())
    {
        result.append("SQL: "            );
        result.append(readableSql(sql)    );
    }
    if(!parameters.isEmpty())
    {
        result.append(tr("Parametres:"             ));
        result.append(parametresToString(parameters));
    }
    return result.join("\n");
}
// --------------------------------------------------------------------------------------------------------------------------------------
QSqlQuery CDatabase::execQuery(const QString &sql, const QVariantList &parameters, bool isExec)
{
    QSqlQuery q(m_db);
    q.prepare(sql);
    int _pos = 0;
    foreach(QVariant value, parameters)
    {
        q.bindValue(_pos, value);
        _pos++;
    }
    if(isExec)
    {
        m_db.driver()->beginTransaction();
    }
    if(!q.exec() || q.lastError().isValid())
    {
        GT_LOGGER->append(tr("Sql error"),
                         lastErrorToLogDescription(q.lastError(), sql, parameters),
                         mtError);
        if(isExec)
        {
            m_db.driver()->rollbackTransaction();
        }
    }
    else
    {
        if(isExec)
        {
            m_db.driver()->commitTransaction();
        }
    }
    return q;
}
// --------------------------------------------------------------------------------------------------------------------------------------
QSqlQuery CDatabase::query(const QString &sql, const QVariantList &parameters)
{
    return execQuery(sql, parameters, false);
}
// --------------------------------------------------------------------------------------------------------------------------------------
bool CDatabase::exec(const QString &sql, const QVariantList &parameters)
{
    return !execQuery(sql, parameters, true).lastError().isValid();
}

}
}
