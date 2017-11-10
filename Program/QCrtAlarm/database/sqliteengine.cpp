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
    closeDatabase();
}

void SqliteEngine::initDatabase(QString pathName, QString userName, QString password)
{
    m_conn = QSqlDatabase::addDatabase("QSQLITE");
    m_conn.setDatabaseName(pathName);
    m_conn.setUserName(userName);
    m_conn.setPassword(password);
}

QString SqliteEngine::getSqlError()
{
    QSqlError se = m_conn.lastError();
    if(se.isValid())
        return se.text();
    return "";
}

bool SqliteEngine::exeNoQuery(const QString &sql)
{
    if(!m_conn.isOpen())return false;
    QSqlQuery sq;
    if(!sq.exec(sql))
    {
        QString error = sq.lastError().text();
        error = "";
    }
    return sq.exec(sql);
}

bool SqliteEngine::exeQuery(const QString &sql,QSqlQuery& query)
{
    if(!m_conn.isOpen())return false;
    bool bRes = query.exec(sql);

    return bRes;
}

bool SqliteEngine::openDatabase()
{
    if(m_conn.isOpen())return true;
    return m_conn.open();
}

bool SqliteEngine::isConnAlive()
{
    return m_conn.isOpen();
}

void SqliteEngine::closeDatabase()
{
    if(m_conn.isOpen())m_conn.close();
}

bool SqliteEngine::isTableExist(const QString &tableName)
{
    if(openDatabase())
    {
        QSqlQuery query(m_conn);
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

bool SqliteEngine::createDefaultCrtTables()
{
    if(!m_conn.isOpen())return false;
    QSqlQuery sq;
    if(!isTableExist("UserTb"))
    {
        sq.exec("create table UserTb("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "name VARCHAR(255),"
                "password VARCHAR(255),"
                "authority INT);");
        sq.exec("insert into UserTb(""name,password,authority) values('admin','1',3),('power','1',2),('user','1',1);");
    }
    if(!isTableExist("PortSettingTb"))
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
    if(!isTableExist("ProjectTb"))
    {
        sq.exec("create table ProjectTb("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "name VARCHAR(255));");
    }
    if(!isTableExist("ControllerTb"))
    {
        sq.exec("create table ControllerTb("
                "key INTEGER PRIMARY KEY AUTOINCREMENT,"
                "id INT,"
                "name VARCHAR(255),"
                "type INT,"
                "type_name VARCHAR(255),"
                "system INT,"
                "system_name VARCHAR(255),"
                "netid INT,"
                "project_id INT);");
    }
    if(!isTableExist("LoopTb"))
    {
        sq.exec("create table LoopTb("
                "key INTEGER PRIMARY KEY AUTOINCREMENT,"
                "id INT,"
                "name VARCHAR(255),"
                "controller_id INT,"
                "project_id INT);");
    }
    if(!isTableExist("BuildingTb"))
    {
        sq.exec("create table BuildingTb("
                "key INTEGER PRIMARY KEY AUTOINCREMENT,"
                "id INT,"
                "name VARCHAR(255),"
                "project_id INT);");
    }
    if(!isTableExist("LayerTb"))
    {
        sq.exec("create table LayerTb("
                "key INTEGER PRIMARY KEY AUTOINCREMENT,"
                "id INT,"
                "name VARCHAR(255),"
                "file VARCHAR(255),"
                "building_id INT,"
                "project_id INT);");
    }
    if(!isTableExist("DeviceTb"))
    {
        sq.exec("create table DeviceTb("
                "key INTEGER PRIMARY KEY AUTOINCREMENT,"
                "id INT,"
                "name VARCHAR(255),"
                "type INT,"
                "type_name VARCHAR(255),"
                "x REAL,"
                "y REAL,"
                "scale REAL,"
                "loop_id INT,"
                "controller_id INT,"
                "layer_id INT,"
                "building_id INT,"
                "project_id INT,"
                "zone INT,"
                "address VARCHAR(255));");
    }
    return true;
}

bool SqliteEngine::beginTransaction()
{
    if(!m_conn.isOpen())return false;
    return m_conn.transaction();
}

bool SqliteEngine::endTransaction()
{
    if(!m_conn.isOpen())return false;
    return m_conn.commit();
}

bool SqliteEngine::rollback()
{
    if(!m_conn.isOpen())return false;
    return m_conn.rollback();
}
