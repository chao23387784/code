#include "datamanager.h"
#include "qdebug.h"
#include "common.h"
#include <QMessageBox>
#include <QFileInfo>
#include "crtmaster.h"

DataManager::DataManager()
{
    m_engine = new SqliteEngine();
}

DataManager::~DataManager()
{  
    if(m_engine->isConnAlive())
        m_engine->closeDatabase();
    SAFE_DELETE(m_engine);
}

void DataManager::initEngine(QString dbPath, QString userName, QString password)
{
    m_engine->closeDatabase();
    m_engine->initDatabase(dbPath,userName,password);
    m_engine->openDatabase();
    m_engine->createDefaultCrtTables();
    m_engine->closeDatabase();
}

bool DataManager::load(CrtProject *proj)
{
    bool bRes = true;
    if(m_engine->openDatabase())
    {
        proj->setType(OT_TEMP);
        loadObject(proj);
    }
    else
    {
        bRes = false;
    }

    //if(bRes == false)
    //    qDebug("%s",engine->GetSqlError());
    m_engine->closeDatabase();
    return bRes;
}

void DataManager::loadObject(CrtObject *obj)
{
    if(!m_engine->isConnAlive())return;
    if(!obj)return;
    if(obj->getType() == OT_TEMP)
    {
        obj->setType(OT_PROJECT);
        QString sql = "select * from ProjectTb";
        QSqlQuery query;
        if(m_engine->exeQuery(sql,query))
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
    else if(obj->getType() == OT_PROJECT)
    {
        QString sql = "select * from ControllerTb";
        QSqlQuery query;
        if(m_engine->exeQuery(sql,query))
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
        if(m_engine->exeQuery(sql,query))
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
    else if(obj->getType() == OT_CONTROLLER)
    {
        QString sql = QString("select * from LoopTb where controller_id = %1 and project_id = %2").arg(obj->getID()).arg(obj->getParent()->getID());
        QSqlQuery query;
        if(m_engine->exeQuery(sql,query))
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
    else if(obj->getType() == OT_LOOP)
    {
        QString sql = QString("select * from DeviceTb where loop_id = %1 and controller_id = %2 and project_id = %3").arg(obj->getID()).arg(obj->getParent()->getID()).arg(obj->getParent()->getParent()->getID());
        QSqlQuery query;
        if(m_engine->exeQuery(sql,query))
        {
            while(query.next())
            {
                CrtDevice* item = new CrtDevice(obj);
                //item->setKey(query.value(0).toInt());
                item->setID(query.value(1).toInt());
                item->setName(query.value(2).toString());
                //item->setType(query.value(5).toInt());
                item->setDeviceType(query.value(4).toString());
                item->setDeviceZone(query.value(13).toInt());
                item->setDeviceAddress(query.value(14).toString());
                obj->addChild(item);
            }
        }
    }
    else if(obj->getType() == OT_BUILDING)
    {
        QString sql = QString("select * from LayerTb where building_id = %1 and project_id = %2").arg(obj->getID()).arg(obj->getParent()->getID());
        QSqlQuery query;
        if(m_engine->exeQuery(sql,query))
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
    else if(obj->getType() == OT_LAYER)
    {
        QString sql = QString("select * from DeviceTb where layer_id = %1 and building_id = %2").arg(obj->getID()).arg(obj->getParent()->getID());
        QSqlQuery query;
        if(m_engine->exeQuery(sql,query))
        {
            while(query.next())
            {
                int id = query.value(1).toInt();
                int loop = query.value(8).toInt();
                int controller = query.value(9).toInt();
                CrtObject* item = CrtMaster::getInstance()->findProjectObject(0,controller,loop,id);
                if(item)
                {
                    obj->addChild(item);
                    dynamic_cast<CrtDevice*>(item)->createDeviceItem()->setPos(query.value(5).toReal(),query.value(6).toReal());
                    dynamic_cast<CrtDevice*>(item)->createDeviceItem()->setScale(query.value(7).toReal());
                }
            }
        }
    }
}

bool DataManager::saveObject(CrtObject *obj)
{
    if(!m_engine->isConnAlive())return false;
    if(!obj)return true;

    if(obj->getType() == OT_PROJECT)
    {
        QSqlQuery query;

        query.prepare("insert into ProjectTb(id,name) values(:id,:name)");
        query.bindValue(":id",obj->getID());
        query.bindValue(":name",obj->getName());

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
    else if(obj->getType() == OT_CONTROLLER)
    {
        QSqlQuery query;

        query.prepare("insert into ControllerTb(id,name,type_name,system_name,netid,project_id) values(:id,:name,:type_name,:system_name,:netid,:proj_id)");
        query.bindValue(":id",obj->getID());
        query.bindValue(":name",obj->getName());
        query.bindValue(":type_name",dynamic_cast<CrtController*>(obj)->getControllerType());
        query.bindValue(":system_name",dynamic_cast<CrtController*>(obj)->getSystemType());
        query.bindValue(":netid",dynamic_cast<CrtController*>(obj)->getNetID());
        query.bindValue(":proj_id",obj->getParent()->getID());

        if(!query.exec())return false;

        query.clear();

        foreach(CrtObject* item,dynamic_cast<CrtController*>(obj)->m_lstLoop)
        {
            if(!saveObject(item))return false;
        }
    }
    else if(obj->getType() == OT_LOOP)
    {
        QSqlQuery query;

        query.prepare("insert into LoopTb(id,name,controller_id,project_id) values(:id,:name,:controller_id,:project_id)");
        query.bindValue(":id",obj->getID());
        query.bindValue(":name",obj->getName());
        query.bindValue(":controller_id",obj->getParent()->getID());
        query.bindValue(":project_id",obj->getParent()->getParent()->getID());

        if(!query.exec())return false;

        query.clear();

        foreach(CrtObject* item,dynamic_cast<CrtLoop*>(obj)->m_lstDevice)
        {
            if(!saveObject(item))return false;
        }
    }
    else if(obj->getType() == OT_BUILDING)
    {
        QSqlQuery query;

        query.prepare("insert into BuildingTb(id,name,project_id) values(:id,:name,:proj_id)");
        query.bindValue(":id",obj->getID());
        query.bindValue(":name",obj->getName());
        query.bindValue(":proj_id",obj->getParent()->getID());

        if(!query.exec())return false;

        query.clear();

        foreach(CrtObject* item,dynamic_cast<CrtBuilding*>(obj)->m_lstLayer)
        {
            if(!saveObject(item))return false;
        }
    }
    else if(obj->getType() == OT_LAYER)
    {
        QSqlQuery query;

        query.prepare("insert into LayerTb(id,name,file,building_id,project_id) values(:id,:name,:file,:building_id,:project_id)");
        query.bindValue(":id",obj->getID());
        query.bindValue(":name",obj->getName());
        query.bindValue(":file",dynamic_cast<CrtLayer*>(obj)->getFilePath());
        query.bindValue(":building_id",obj->getParent()->getID());
        query.bindValue(":project_id",obj->getParent()->getParent()->getID());

        if(!query.exec())return false;

        query.clear();
    }
    else if(obj->getType() == OT_DEVICE)
    {
        QSqlQuery query;

        query.prepare("insert into DeviceTb(id,name,type,type_name,x,y,scale,loop_id,controller_id,layer_id,building_id,project_id,zone,address) values(:id,:name,:type,:type_name,:x,:y,:scale,:loop_id,:controller_id,:layer_id,:building_id,:project_id,:zone,:address)");
        query.bindValue(":id",obj->getID());
        query.bindValue(":name",obj->getName());
        query.bindValue(":type_name",dynamic_cast<CrtDevice*>(obj)->getDeviceType());
        query.bindValue(":zone",dynamic_cast<CrtDevice*>(obj)->getDeviceZone());
        query.bindValue(":address",dynamic_cast<CrtDevice*>(obj)->getDeviceAddress());
        //query.bindValue(":type",//string type to int type);
        if(dynamic_cast<CrtDevice*>(obj)->getLayerID()!=-1 && dynamic_cast<CrtDevice*>(obj)->getBuildingID() != -1)
        {
            CrtDeviceItem* item = dynamic_cast<CrtDevice*>(obj)->createDeviceItem();
            query.bindValue(":x",item->pos().x());
            query.bindValue(":y",item->pos().y());
            query.bindValue(":scale",item->scale());
        }else
        {
            query.bindValue(":x",0);
            query.bindValue(":y",0);
            query.bindValue(":scale",1.0);
        }

        query.bindValue(":loop_id",obj->getParent()->getID());
        query.bindValue(":controller_id",obj->getParent()->getParent()->getID());
        query.bindValue(":layer_id",dynamic_cast<CrtDevice*>(obj)->getLayerID());
        query.bindValue(":building_id",dynamic_cast<CrtDevice*>(obj)->getBuildingID());
        query.bindValue(":project_id",obj->getParent()->getParent()->getParent()->getID());

        if(!query.exec())return false;

        query.clear();
    }

    return true;
}


bool DataManager::save(CrtProject *proj)
{
    if(!m_engine->isConnAlive())m_engine->openDatabase();
    if(m_engine->beginTransaction()){
        if(!m_engine->exeNoQuery("delete from DeviceTb"))goto err;
        if(!m_engine->exeNoQuery("delete from LayerTb"))goto err;
        if(!m_engine->exeNoQuery("delete from BuildingTb"))goto err;
        if(!m_engine->exeNoQuery("delete from LoopTb"))goto err;
        if(!m_engine->exeNoQuery("delete from ControllerTb"))goto err;
        if(!m_engine->exeNoQuery("delete from ProjectTb"))goto err;

        if(!saveObject(proj))goto err;

        return m_engine->endTransaction();
        err:
        m_engine->rollback();
    }
    return false;
}
