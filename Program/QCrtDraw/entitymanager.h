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

class EntityManager
{
public:
    EntityManager();
    ~EntityManager();
    void InitEngine(QString dbPath = "NtCrt.db",QString userName = "neat",QString password = "123");
    bool load(CrtProject* proj);
    bool save(CrtProject* proj);
private:
    void loadEntity(CrtObject* obj);
    bool saveEntity(CrtObject* obj);
private:
    SqliteEngine* engine;
};

#endif // ENTITYMANAGER_H
