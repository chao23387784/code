#include "datamanager.h"
#include "qdebug.h"
#include "common.h"
#include <QMessageBox>
#include <QFileInfo>
#include "crtmaster.h"

DataManager::DataManager()
{
    engine = new SqliteEngine();
}

DataManager::~DataManager()
{  
    if(engine->IsConnAlive())
        engine->CloseDatabase();
    SAFE_DELETE(engine);
}

void DataManager::InitEngine(QString dbPath, QString userName, QString password)
{
    engine->CloseDatabase();
    engine->InitDatabase(dbPath,userName,password);
    engine->OpenDatabase();
    engine->CreateDefaultCrtTables();
    engine->CloseDatabase();
}

bool DataManager::load(CrtProject *proj)
{
    bool bRes = true;
    if(engine->OpenDatabase())
    {
        proj->setType("init");
        loadObject(proj);
    }
    else
    {
        bRes = false;
    }

    //if(bRes == false)
    //    qDebug("%s",engine->GetSqlError());
    engine->CloseDatabase();
    return bRes;
}

void DataManager::loadObject(CrtObject *obj)
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
                loadObject(obj);
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
                item->setControllerType(query.value(4).toString());
                item->setSystemType(query.value(6).toString());
                item->setNetID(query.value(7).toInt());
                obj->addChild(item);
                loadObject(item);
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
                obj->addChild(item);
                loadObject(item);
            }
        }
    }
    else if(!obj->Type().compare("controller"))
    {
        QString sql = QString("select * from LoopTb where controller_id = %1 and project_id = %2").arg(obj->ID()).arg(obj->Parent()->ID());
        QSqlQuery query;
        if(engine->ExeQuery(sql,query))
        {
            while(query.next())
            {
                CrtLoop* item = new CrtLoop(obj);
                //item->setKey(query.value(0).toInt());
                item->setID(query.value(1).toInt());
                item->setName(query.value(2).toString());
                obj->addChild(item);
                loadObject(item);
            }
        }
    }
    else if(!obj->Type().compare("loop"))
    {
        QString sql = QString("select * from DeviceTb where loop_id = %1 and controller_id = %2 and project_id = %3").arg(obj->ID()).arg(obj->Parent()->ID()).arg(obj->Parent()->Parent()->ID());
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
                item->setDeviceType(query.value(4).toString());
                obj->addChild(item);
            }
        }
    }
    else if(!obj->Type().compare("building"))
    {
        QString sql = QString("select * from LayerTb where building_id = %1 and project_id = %2").arg(obj->ID()).arg(obj->Parent()->ID());
        QSqlQuery query;
        if(engine->ExeQuery(sql,query))
        {
            while(query.next())
            {
                CrtLayer* item = new CrtLayer(obj);
                //item->setKey(query.value(0).toInt());
                item->setID(query.value(1).toInt());
                item->setName(query.value(2).toString());
                QString filePath = query.value(3).toString();
                if(!filePath.isEmpty() && QFileInfo(filePath).exists())
                {
                    item->setBackground(filePath);
                }
                obj->addChild(item);
                loadObject(item);
            }
        }
    }
    else if(!obj->Type().compare("layer"))
    {
        QString sql = QString("select * from DeviceTb where layer_id = %1 and building_id = %2").arg(obj->ID()).arg(obj->Parent()->ID());
        QSqlQuery query;
        if(engine->ExeQuery(sql,query))
        {
            while(query.next())
            {
                int id = query.value(1).toInt();
                int loop = query.value(7).toInt();
                int controller = query.value(8).toInt();
                CrtObject* item = CrtMaster::GetInstance()->findProjectObject(0,controller,loop,id);
                if(item)
                {
                    obj->addChild(item);
                    dynamic_cast<CrtDevice*>(item)->createDeviceItem()->setPos(query.value(5).toReal(),query.value(6).toReal());
                }
            }
        }
    }
}

bool DataManager::saveObject(CrtObject *obj)
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

        foreach(CrtObject* item,dynamic_cast<CrtProject*>(obj)->m_lstController)
        {
            if(!saveObject(item))return false;
        }

        foreach(CrtObject* item,dynamic_cast<CrtProject*>(obj)->m_lstBuilding)
        {
            if(!saveObject(item))return false;
        }
    }
    else if(!obj->Type().compare("controller"))
    {
        QSqlQuery query;

        query.prepare("insert into ControllerTb(id,name,type_name,system_name,netid,project_id) values(:id,:name,:type_name,:system_name,:netid,:proj_id)");
        query.bindValue(":id",obj->ID());
        query.bindValue(":name",obj->Name());
        query.bindValue(":type_name",dynamic_cast<CrtController*>(obj)->ControllerType());
        query.bindValue(":system_name",dynamic_cast<CrtController*>(obj)->SystemType());
        query.bindValue(":netid",dynamic_cast<CrtController*>(obj)->NetID());
        query.bindValue(":proj_id",obj->Parent()->ID());

        if(!query.exec())return false;

        query.clear();

        foreach(CrtObject* item,dynamic_cast<CrtController*>(obj)->m_lstLoop)
        {
            if(!saveObject(item))return false;
        }
    }
    else if(!obj->Type().compare("loop"))
    {
        QSqlQuery query;

        query.prepare("insert into LoopTb(id,name,controller_id,project_id) values(:id,:name,:controller_id,:project_id)");
        query.bindValue(":id",obj->ID());
        query.bindValue(":name",obj->Name());
        query.bindValue(":controller_id",obj->Parent()->ID());
        query.bindValue(":project_id",obj->Parent()->Parent()->ID());

        if(!query.exec())return false;

        query.clear();

        foreach(CrtObject* item,dynamic_cast<CrtLoop*>(obj)->m_lstDevice)
        {
            if(!saveObject(item))return false;
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

        foreach(CrtObject* item,dynamic_cast<CrtBuilding*>(obj)->m_lstLayer)
        {
            if(!saveObject(item))return false;
        }
    }
    else if(!obj->Type().compare("layer"))
    {
        QSqlQuery query;

        query.prepare("insert into LayerTb(id,name,file,building_id,project_id) values(:id,:name,:file,:building_id,:project_id)");
        query.bindValue(":id",obj->ID());
        query.bindValue(":name",obj->Name());
        query.bindValue(":file",dynamic_cast<CrtLayer*>(obj)->FilePath());
        query.bindValue(":building_id",obj->Parent()->ID());
        query.bindValue(":project_id",obj->Parent()->Parent()->ID());

        if(!query.exec())return false;

        query.clear();
    }
    else if(!obj->Type().compare("device"))
    {
        QSqlQuery query;

        query.prepare("insert into DeviceTb(id,name,type,type_name,x,y,loop_id,controller_id,layer_id,building_id,project_id) values(:id,:name,:type,:type_name,:x,:y,:loop_id,:controller_id,:layer_id,:building_id,:project_id)");
        query.bindValue(":id",obj->ID());
        query.bindValue(":name",obj->Name());
        query.bindValue(":type_name",dynamic_cast<CrtDevice*>(obj)->DeviceType());
        //query.bindValue(":type",//string type to int type);
        if(dynamic_cast<CrtDevice*>(obj)->LayerID()!=-1 && dynamic_cast<CrtDevice*>(obj)->BuildingID() != -1)
        {
            CrtDeviceItem* item = dynamic_cast<CrtDevice*>(obj)->createDeviceItem();
            query.bindValue(":x",item->pos().x());
            query.bindValue(":y",item->pos().y());
        }else
        {
            query.bindValue(":x",0);
            query.bindValue(":y",0);
        }

        query.bindValue(":loop_id",obj->Parent()->ID());
        query.bindValue(":controller_id",obj->Parent()->Parent()->ID());
        query.bindValue(":layer_id",dynamic_cast<CrtDevice*>(obj)->LayerID());
        query.bindValue(":building_id",dynamic_cast<CrtDevice*>(obj)->BuildingID());
        query.bindValue(":project_id",obj->Parent()->Parent()->Parent()->ID());

        if(!query.exec())return false;

        query.clear();
    }

    return true;
}


bool DataManager::save(CrtProject *proj)
{
    if(!engine->IsConnAlive())engine->OpenDatabase();
    if(engine->beginTransaction()){
        if(!engine->ExeNoQuery("delete from DeviceTb"))goto err;
        if(!engine->ExeNoQuery("delete from LayerTb"))goto err;
        if(!engine->ExeNoQuery("delete from BuildingTb"))goto err;
        if(!engine->ExeNoQuery("delete from LoopTb"))goto err;
        if(!engine->ExeNoQuery("delete from ControllerTb"))goto err;
        if(!engine->ExeNoQuery("delete from ProjectTb"))goto err;

        if(!saveObject(proj))goto err;

        return engine->endTransaction();
        err:
        engine->rollback();
    }
    return false;
}
