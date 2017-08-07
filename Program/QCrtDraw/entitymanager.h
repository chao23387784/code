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
    void InitEngine(QString dbPath = "NtCrt.db",QString userName = "neat",QString password = "123");
    bool load(CrtProject* proj);
    bool save(CrtProject* proj);
    void loadEntity(CrtObject* obj);
    int getAvaliableNumber(const QString& tableName);
private:
    SqliteEngine* engine;
};

#endif // ENTITYMANAGER_H
