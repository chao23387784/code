#include "entitymanager.h"
#include "qdebug.h"
#include "common.h"

EntityManager::EntityManager()
{
    engine = new SqliteEngine();
}

void EntityManager::InitEngine(QString dbPath, QString userName, QString password)
{
    engine->CloseDatabase();
    engine->InitDatabase(dbPath,userName,password);
    engine->OpenDatabase();
    engine->CreateDefaultCrtTables();
    engine->CloseDatabase();
}

bool EntityManager::load(CrtProject *proj)
{
    bool bRes = true;
    if(engine->OpenDatabase())
    {
        proj->setType("init");
        loadEntity(proj);
    }
    else
    {
        bRes = false;
    }

    if(bRes == false)
        qDebug("%s",engine->GetSqlError());
    engine->CloseDatabase();
    return bRes;
}

void EntityManager::loadEntity(CrtObject *obj)
{
    if(!engine->IsConnAlive())return;
    if(!obj)return;
    if(!obj->Type().compare("init"))
    {
        obj->setType("project");
        QString sql = "select * from ProjectTb";
        QSqlQuery query;
        if(engine->ExeQuery(sql,query))
        {
            if(query.first())
            {
                obj->setID(query.value(0).toInt());
                obj->setName(query.value(1).toString());
                loadEntity(obj);
            }
        }
    }
    else if(!obj->Type().compare("project"))
    {
        QString sql = "select * from ControllerTb";
        QSqlQuery query;
        if(engine->ExeQuery(sql,query))
        {
            while(query.next())
            {
                CrtController* item = new CrtController(obj);
                item->setID(query.value(1).toInt());
                item->setName(query.value(2).toString());
                static_cast<CrtProject*>(obj)->m_lstController.append(item);
                loadEntity(item);
            }
        }

        sql = "select * from BuildingTb";
        query.clear();
        if(engine->ExeQuery(sql,query))
        {
            while(query.next())
            {
                CrtBuilding* item = new CrtBuilding(obj);
                item->setID(query.value(1).toInt());
                item->setName(query.value(2).toString());
                static_cast<CrtProject*>(obj)->m_lstBuilding.append(item);
                loadEntity(item);
            }
        }
    }
    else if(!obj->Type().compare("controller"))
    {
        QString sql = QString("select * from LoopTb where controller_id = %1").arg(obj->ID());
        QSqlQuery query;
        if(engine->ExeQuery(sql,query))
        {
            while(query.next())
            {
                CrtLoop* item = new CrtLoop(obj);
                item->setID(query.value(1).toInt());
                item->setName(query.value(2).toString());
                static_cast<CrtController*>(obj)->m_lstLoop.append(item);
                loadEntity(item);
            }
        }
    }
    else if(!obj->Type().compare("loop"))
    {
        QString sql = QString("select * from DeviceTb where loop_id = %1").arg(obj->ID());
        QSqlQuery query;
        if(engine->ExeQuery(sql,query))
        {
            while(query.next())
            {
                CrtDevice* item = new CrtDevice(obj);
                item->setID(query.value(1).toInt());
                item->setName(query.value(2).toString());
                //item->setType(query.value(5).toInt());
                item->setDeviceType(query.value(6).toString());
                static_cast<CrtLoop*>(obj)->m_lstDevice.append(item);
            }
        }
    }
    else if(!obj->Type().compare("building"))
    {
        QString sql = QString("select * from LayerTb where building_id = %1").arg(obj->ID());
        QSqlQuery query;
        if(engine->ExeQuery(sql,query))
        {
            while(query.next())
            {
                CrtLayer* item = new CrtLayer(obj);
                item->setID(query.value(1).toInt());
                item->setName(query.value(2).toString());
                static_cast<CrtBuilding*>(obj)->m_lstLayer.append(item);
                //loadEntity(item);
            }
        }
    }
    else if(!obj->Type().compare("layer"))
    {
        //QString sql = QString("select * from DeviceTb where layer_id = %1").arg(obj->ID());
        //QSqlQuery query;
    }
}

int EntityManager::getAvaliableNumber(const QString &tableName)
{
    if(engine->IsConnAlive())
    {
        QSqlQuery query;
        QString sql = QString("select max(number) from %1").arg(tableName);
        if(engine->ExeQuery(sql,query))
        {
            if(query.first())
            {
                return query.value(0).toInt() + 1;
            }
        }
    }
    return -1;
}


bool EntityManager::save(CrtProject *proj)
{
    return true;
}
