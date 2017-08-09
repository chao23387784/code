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
    foreach(CrtObject* item,m_lstModifyObjects)
    {
        if(item->Status() == Delete)
            SAFE_DELETE(item);
    }
    m_lstModifyObjects.clear();

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
                obj->setKey(query.value(0).toInt());
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
                item->setKey(query.value(0).toInt());
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
                item->setKey(query.value(0).toInt());
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
                item->setKey(query.value(0).toInt());
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
                item->setKey(query.value(0).toInt());
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
                item->setKey(query.value(0).toInt());
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

    if(obj->Type().compare("project"))
    {
        QSqlQuery query;
        switch(obj->Status())
        {
        case New:
        {
            query.prepare("insert into ProjectTb(id,name) values(:id,:name)");
            query.bindValue(":id",obj->ID());
            query.bindValue(":name",obj->Name());
        }
            break;
        case Modify:
        {
            query.prepare("update ProjectTb set name = :name where id = :id");
            query.bindValue(":id",obj->Key());
            query.bindValue(":name",obj->Name());
        }
            break;
        case Delete:
        {
            query.prepare("delete * from ProjectTb where id = :id");
            query.bindValue(":id",obj->Key());
        }
            break;
        default:{return false;}
        }

        if(!query.exec())return false;
    }
    else if(obj->Type().compare("controller"))
    {
        QSqlQuery query;
        switch(obj->Status())
        {
        case New:
        {
            query.prepare("insert into ControllerTb(number,name,project_id) values(:number,:name,:proj_id)");
            query.bindValue(":number",obj->ID());
            query.bindValue(":name",obj->Name());
            query.bindValue(":proj_id",obj->Parent()->ID());
        }
            break;
        case Modify:
        {
            query.prepare("update ControllerTb set number = :number,name = :name,project_id = :proj_id where id = :id");
            query.bindValue(":number",obj->ID());
            query.bindValue(":name",obj->Name());
            query.bindValue(":proj_id",obj->Parent()->ID());
            query.bindValue(":id",obj->Key());
        }
            break;
        case Delete:
        {
            query.prepare("delete * from ControllerTb where id = :id");
            query.bindValue(":id",obj->Key());
        }
            break;
        default:{return false;}
        }

        if(!query.exec())return false;
    }
    else if(obj->Type().compare("loop"))
    {
        QSqlQuery query;
        switch(obj->Status())
        {
        case New:
        {
            query.prepare("insert into LoopTb(number,name,controller_id) values(:number,:name,:controller_id)");
            query.bindValue(":number",obj->ID());
            query.bindValue(":name",obj->Name());
            query.bindValue(":controller_id",obj->Parent()->ID());
        }
            break;
        case Modify:
        {
            query.prepare("update LoopTb set number = :number,name = :name,controller_id = :controller_id where id = :id");
            query.bindValue(":number",obj->ID());
            query.bindValue(":name",obj->Name());
            query.bindValue(":controller_id",obj->Parent()->ID());
            query.bindValue(":id",obj->Key());
        }
            break;
        case Delete:
        {
            query.prepare("delete * from LoopTb where id = :id");
            query.bindValue(":id",obj->Key());
        }
            break;
        default:{return false;}
        }

        if(!query.exec())return false;
    }
    else if(obj->Type().compare("building"))
    {
        QSqlQuery query;
        switch(obj->Status())
        {
        case New:
        {
            query.prepare("insert into BuildingTb(number,name,project_id) values(:number,:name,:proj_id)");
            query.bindValue(":number",obj->ID());
            query.bindValue(":name",obj->Name());
            query.bindValue(":proj_id",obj->Parent()->ID());
        }
            break;
        case Modify:
        {
            query.prepare("update BuildingTb set number = :number,name = :name,project_id = :proj_id where id = :id");
            query.bindValue(":number",obj->ID());
            query.bindValue(":name",obj->Name());
            query.bindValue(":proj_id",obj->Parent()->ID());
            query.bindValue(":id",obj->Key());
        }
            break;
        case Delete:
        {
            query.prepare("delete * from BuildingTb where id = :id");
            query.bindValue(":id",obj->Key());
        }
            break;
        default:{return false;}
        }

        if(!query.exec())return false;
    }
    else if(obj->Type().compare("layer"))
    {
        QSqlQuery query;
        switch(obj->Status())
        {
        case New:
        {
            query.prepare("insert into LayerTb(number,name,building_id) values(:number,:name,:building_id)");
            query.bindValue(":number",obj->ID());
            query.bindValue(":name",obj->Name());
            query.bindValue(":building_id",obj->Parent()->ID());
        }
            break;
        case Modify:
        {
            query.prepare("update LayerTb set number = :number,name = :name,building_id = :building_id where id = :id");
            query.bindValue(":number",obj->ID());
            query.bindValue(":name",obj->Name());
            query.bindValue(":building_id",obj->Parent()->ID());
            query.bindValue(":id",obj->Key());
        }
            break;
        case Delete:
        {
            query.prepare("delete * from LayerTb where id = :id");
            query.bindValue(":id",obj->Key());
        }
            break;
        default:{return false;}
        }

        if(!query.exec())return false;
    }
    else if(obj->Type().compare("device"))
    {
        QSqlQuery query;
        switch(obj->Status())
        {
        case New:
        {
            query.prepare("insert into DeviceTb(number,name,loop_id,layer_id,type,type_name) values(:number,:name,:loop_id,:layer_id,:type,:type_name)");
            query.bindValue(":number",obj->ID());
            query.bindValue(":name",obj->Name());
            query.bindValue(":loop_id",obj->Parent()->ID());
            //query.bindValue(":layer_id",static_cast<CrtDevice*>(obj)->LayerID());
            query.bindValue(":type_name",obj->Type());
            //query.bindValue(":type",/*string type to int type*/);
        }
            break;
        case Modify:
        {
            query.prepare("update DeviceTb set number = :number,name = :name,loop_id = :loop_id,layer_id = :layer_id,type = :type,type_name = :type_name where id = :id");
            query.bindValue(":number",obj->ID());
            query.bindValue(":name",obj->Name());
            query.bindValue(":loop_id",obj->Parent()->ID());
            //query.bindValue(":layer_id",static_cast<CrtDevice*>(obj)->LayerID());
            query.bindValue(":type_name",obj->Type());
            //query.bindValue(":type",/*string type to int type*/);
            query.bindValue(":id",obj->Key());
        }
            break;
        case Delete:
        {
            query.prepare("delete * from DeviceTb where id = :id");
            query.bindValue(":id",obj->Key());
        }
            break;
        default:{return false;}
        }

        if(!query.exec())return false;
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

int EntityManager::getAvaliableControllerNumber(int proj_id)
{
    return -1;
}

int EntityManager::getAvaliableLoopNumber(int controller_id, int proj_id)
{
    return -1;
}

int EntityManager::getAvaliableBuildingNumber(int proj_id)
{
    return -1;
}

int EntityManager::getAvaliableLayerNumber(int building_id, int proj_id)
{
    return -1;
}

int EntityManager::getAvaliableDeviceNumber(int loop_id, int controller_id, int proj_id)
{
    return -1;
}

void EntityManager::addModifyEntity(CrtObject *obj, int type)
{
    switch(type)
    {
    case New:
    {

    }
        break;
    case Modify:
    {

    }
        break;
    case Delete:
    {

    }
        break;
    default:{}
    }
}


bool EntityManager::save(CrtProject *proj)
{
    if(proj && engine->IsConnAlive())
    {
        if(engine->beginTransaction())
        {
            foreach(CrtObject* obj,m_lstModifyObjects)
            {
                if(!saveEntity(obj))
                {
                    engine->rollback();
                    return false;
                }
            }

            return engine->endTransaction();
        }
    }

    return false;
}
