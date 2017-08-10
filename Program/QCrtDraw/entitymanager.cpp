#include "entitymanager.h"
#include "qdebug.h"
#include "common.h"
#include <QMessageBox>

EntityManager::EntityManager()
{
    engine = new SqliteEngine();
}

EntityManager::~EntityManager()
{  
    if(engine->IsConnAlive())
        engine->CloseDatabase();
    SAFE_DELETE(engine);
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
                //obj->setKey(query.value(0).toInt());
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
                //item->setKey(query.value(0).toInt());
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
                //item->setKey(query.value(0).toInt());
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
                //item->setKey(query.value(0).toInt());
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
                //item->setKey(query.value(0).toInt());
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
                //item->setKey(query.value(0).toInt());
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

bool EntityManager::saveEntity(CrtObject *obj)
{
    if(!engine->IsConnAlive())return false;
    if(!obj)return true;

    if(!obj->Type().compare("project"))
    {
        QSqlQuery query;

        query.prepare("insert into ProjectTb(id,name) values(:id,:name)");
        query.bindValue(":id",obj->ID());
        query.bindValue(":name",obj->Name());

        if(!query.exec())return false;

        query.clear();

        foreach(CrtObject* item,static_cast<CrtProject*>(obj)->m_lstController)
        {
            if(!saveEntity(item))return false;
        }

        foreach(CrtObject* item,static_cast<CrtProject*>(obj)->m_lstBuilding)
        {
            if(!saveEntity(item))return false;
        }
    }
    else if(!obj->Type().compare("controller"))
    {
        QSqlQuery query;

        query.prepare("insert into ControllerTb(id,name,project_id) values(:id,:name,:proj_id)");
        query.bindValue(":id",obj->ID());
        query.bindValue(":name",obj->Name());
        query.bindValue(":proj_id",obj->Parent()->ID());

        if(!query.exec())return false;

        query.clear();

        foreach(CrtObject* item,static_cast<CrtController*>(obj)->m_lstLoop)
        {
            if(!saveEntity(item))return false;
        }
    }
    else if(!obj->Type().compare("loop"))
    {
        QSqlQuery query;

        query.prepare("insert into LoopTb(id,name,controller_id) values(:id,:name,:controller_id)");
        query.bindValue(":id",obj->ID());
        query.bindValue(":name",obj->Name());
        query.bindValue(":controller_id",obj->Parent()->ID());

        if(!query.exec())return false;

        query.clear();

        foreach(CrtObject* item,static_cast<CrtLoop*>(obj)->m_lstDevice)
        {
            if(!saveEntity(item))return false;
        }
    }
    else if(!obj->Type().compare("building"))
    {
        QSqlQuery query;

        query.prepare("insert into BuildingTb(id,name,project_id) values(:id,:name,:proj_id)");
        query.bindValue(":id",obj->ID());
        query.bindValue(":name",obj->Name());
        query.bindValue(":proj_id",obj->Parent()->ID());

        if(!query.exec())return false;

        query.clear();

        foreach(CrtObject* item,static_cast<CrtBuilding*>(obj)->m_lstLayer)
        {
            if(!saveEntity(item))return false;
        }
    }
    else if(!obj->Type().compare("layer"))
    {
        QSqlQuery query;

        query.prepare("insert into LayerTb(id,name,building_id) values(:id,:name,:building_id)");
        query.bindValue(":id",obj->ID());
        query.bindValue(":name",obj->Name());
        query.bindValue(":building_id",obj->Parent()->ID());

        if(!query.exec())return false;

        query.clear();
    }
    else if(!obj->Type().compare("device"))
    {
        QSqlQuery query;

        query.prepare("insert into DeviceTb(id,name,loop_id,layer_id,type,type_name) values(:id,:name,:loop_id,:layer_id,:type,:type_name)");
        query.bindValue(":id",obj->ID());
        query.bindValue(":name",obj->Name());
        query.bindValue(":loop_id",obj->Parent()->ID());
        //query.bindValue(":layer_id",static_cast<CrtDevice*>(obj)->LayerID());
        query.bindValue(":type_name",obj->Type());
        //query.bindValue(":type",//string type to int type);

        if(!query.exec())return false;

        query.clear();
    }

    return true;
}


bool EntityManager::save(CrtProject *proj)
{
    if(!engine->IsConnAlive())engine->OpenDatabase();
    if(engine->beginTransaction()){
        if(!engine->ExeNoQuery("delete from DeviceTb"))goto err;
        if(!engine->ExeNoQuery("delete from LayerTb"))goto err;
        if(!engine->ExeNoQuery("delete from BuildingTb"))goto err;
        if(!engine->ExeNoQuery("delete from LoopTb"))goto err;
        if(!engine->ExeNoQuery("delete from ControllerTb"))goto err;
        if(!engine->ExeNoQuery("delete from ProjectTb"))goto err;

        if(!saveEntity(proj))goto err;

        return engine->endTransaction();
        err:
        engine->rollback();
    }
    return false;
}
