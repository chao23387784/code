#ifndef CRTMASTER_H
#define CRTMASTER_H

#include <QHash>
#include "crtproject.h"
#include "entitymanager.h"

class CrtMaster
{
public:
    static CrtMaster* GetInstance();
    static void Destroy();
    void setProject(CrtProject* proj);
    CrtProject* Project(){return project;}
    void setManager(EntityManager* manager);
    EntityManager* Manager(){return manager;}
private:
    explicit CrtMaster();
    ~CrtMaster();
    static CrtMaster* m_inst;
    QHash<int,QString> m_lstDevType;
    CrtProject* project;
    EntityManager* manager;
};

#endif // CRTMASTER_H
