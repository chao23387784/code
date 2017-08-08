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
    void InitDatabase(QString pathName,QString userName,QString password);
    QString GetSqlError();
    bool ExeNoQuery(const QString& sql);
    bool ExeQuery(const QString& sql,QSqlQuery& query);
    bool OpenDatabase();
    bool IsConnAlive();
    void CloseDatabase();
    bool IsTableExist(const QString& tableName);
    bool CreateDefaultCrtTables();
    QString PathName(){return pathName;}
    bool beginTransaction();
    bool endTransaction();
    bool rollback();
private:
    QSqlDatabase conn;
    QString pathName;
};

#endif // SQLITEENGINE_H
