#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include "crtobject.h"
#include "crtproject.h"
#include "crtcontroller.h"
#include "crtbuilding.h"
#include "crtloop.h"
#include "crtlayer.h"
#include "crtdevice.h"
#include "sqliteengine.h"
#include <QList>

enum DataStatus{
    New,
    Modify,
    Delete,
    Invalid
};

class EntityManager
{
public:
    EntityManager();
    ~EntityManager();
    void InitEngine(QString dbPath = "NtCrt.db",QString userName = "neat",QString password = "123");
    bool load(CrtProject* proj);
    bool save(CrtProject* proj);
    int getAvaliableNumber(const QString& tableName);
    int getAvaliableControllerNumber(int proj_id);
    int getAvaliableLoopNumber(int controller_id,int proj_id);
    int getAvaliableBuildingNumber(int proj_id);
    int getAvaliableLayerNumber(int building_id,int proj_id);
    int getAvaliableDeviceNumber(int loop_id,int controller_id,int proj_id);
    void addModifyEntity(CrtObject* obj,int type);
private:
    void loadEntity(CrtObject* obj);
    bool saveEntity(CrtObject* obj);
    QList<CrtObject*> m_lstModifyObjects;
private:
    SqliteEngine* engine;
};

#endif // ENTITYMANAGER_H
