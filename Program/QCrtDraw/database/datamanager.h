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

class DataManager
{
public:
    DataManager();
    ~DataManager();
    void InitEngine(QString dbPath = "NtCrt.db",QString userName = "neat",QString password = "123");
    bool load(CrtProject* proj);
    bool save(CrtProject* proj);
private:
    void loadObject(CrtObject* obj);
    bool saveObject(CrtObject* obj);
private:
    SqliteEngine* engine;
};

#endif // ENTITYMANAGER_H
