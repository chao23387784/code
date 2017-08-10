#include "sqliteengine.h"
#include <QVariant>

SqliteEngine::SqliteEngine()
{
    /*CloseDatabase();
    InitDatabase("NtCrt.db","neat","123");
    OpenDatabase();*/
}

SqliteEngine::~SqliteEngine()
{
    CloseDatabase();
}

void SqliteEngine::InitDatabase(QString pathName, QString userName, QString password)
{
    conn = QSqlDatabase::addDatabase("QSQLITE");
    conn.setDatabaseName(pathName);
    conn.setUserName(userName);
    conn.setPassword(password);
}

QString SqliteEngine::GetSqlError()
{
    QSqlError se = conn.lastError();
    if(se.isValid())
        return se.text();
    return "";
}

bool SqliteEngine::ExeNoQuery(const QString &sql)
{
    if(!conn.isOpen())return false;
    QSqlQuery sq;
    if(!sq.exec(sql))
    {
        QString error = sq.lastError().text();
        error = "";
    }
    return sq.exec(sql);
}

bool SqliteEngine::ExeQuery(const QString &sql,QSqlQuery& query)
{
    if(!conn.isOpen())return false;
    bool bRes = query.exec(sql);

    return bRes;
}

bool SqliteEngine::OpenDatabase()
{
    if(conn.isOpen())return true;
    return conn.open();
}

bool SqliteEngine::IsConnAlive()
{
    return conn.isOpen();
}

void SqliteEngine::CloseDatabase()
{
    if(conn.isOpen())conn.close();
}

bool SqliteEngine::IsTableExist(const QString &tableName)
{
    if(OpenDatabase())
    {
        QSqlQuery query(conn);
        query.exec(QString("select count(*) from sqlite_master where type='table' and name='%1'").arg(tableName));
        if(query.next())
        {
            if(query.value(0).toInt() == 0)  //not exist
            {
                return false;
            }
            else //existed
            {
                return true;
            }
        }
    }
    return false;
}

bool SqliteEngine::CreateDefaultCrtTables()
{
    if(!conn.isOpen())return false;
    QSqlQuery sq;
    if(!IsTableExist("UserTb"))
    {
        sq.exec("create table UserTb("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "name VARCHAR(255),"
                "password VARCHAR(255),"
                "authority INT);");
        sq.exec("insert into UserTb(""name,password,authority) values('admin','1',3),('power','1',2),('user','1',1);");
    }
    if(!IsTableExist("PortSettingTb"))
    {
        sq.exec("create table PortSettingTb("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "name VARCHAR(10),"
                "baudrate INT,"
                "password VARCHAR(8),"
                "protocol VARCHAR(1),"
                "netid VARCHAR(2),"
                "checktime VARCHAR(1));");
    }
    if(!IsTableExist("ProjectTb"))
    {
        sq.exec("create table ProjectTb("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "name VARCHAR(255));");
    }
    if(!IsTableExist("ControllerTb"))
    {
        sq.exec("create table ControllerTb("
                "key INTEGER PRIMARY KEY AUTOINCREMENT,"
                "id INT,"
                "name VARCHAR(255),"
                "project_id INT);");
    }
    if(!IsTableExist("LoopTb"))
    {
        sq.exec("create table LoopTb("
                "key INTEGER PRIMARY KEY AUTOINCREMENT,"
                "id INT,"
                "name VARCHAR(255),"
                "controller_id INT);");
    }
    if(!IsTableExist("BuildingTb"))
    {
        sq.exec("create table BuildingTb("
                "key INTEGER PRIMARY KEY AUTOINCREMENT,"
                "id INT,"
                "name VARCHAR(255),"
                "project_id INT);");
    }
    if(!IsTableExist("LayerTb"))
    {
        sq.exec("create table LayerTb("
                "key INTEGER PRIMARY KEY AUTOINCREMENT,"
                "id INT,"
                "name VARCHAR(255),"
                "building_id INT);");
    }
    if(!IsTableExist("DeviceTb"))
    {
        sq.exec("create table DeviceTb("
                "key INTEGER PRIMARY KEY AUTOINCREMENT,"
                "id INT,"
                "name VARCHAR(255),"
                "loop_id INT,"
                "layer_id INT,"
                "type INT,"
                "type_name VARCHAR(255));");
    }
    return true;
}

bool SqliteEngine::beginTransaction()
{
    if(!conn.isOpen())return false;
    return conn.transaction();
}

bool SqliteEngine::endTransaction()
{
    if(!conn.isOpen())return false;
    return conn.commit();
}

bool SqliteEngine::rollback()
{
    if(!conn.isOpen())return false;
    return conn.rollback();
}
