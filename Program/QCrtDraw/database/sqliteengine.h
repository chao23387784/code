#ifndef SQLITEENGINE_H
#define SQLITEENGINE_H

#include <QtSql/QSqlDatabase>
//#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>
#include <QObject>

class SqliteEngine : QObject
{
public:
    SqliteEngine();
    ~SqliteEngine();
    void initDatabase(QString pathName,QString userName,QString password);
    QString getSqlError();
    bool exeNoQuery(const QString& sql);
    bool exeQuery(const QString& sql,QSqlQuery& query);
    bool openDatabase();
    bool isConnAlive();
    void closeDatabase();
    bool isTableExist(const QString& tableName);
    bool createDefaultCrtTables();
    QString getPathName(){return m_strPathName;}
    bool beginTransaction();
    bool endTransaction();
    bool rollback();
private:
    QSqlDatabase m_conn;
    QString m_strPathName;
};

#endif // SQLITEENGINE_H
