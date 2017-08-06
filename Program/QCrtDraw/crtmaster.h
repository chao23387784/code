#ifndef CRTMASTER_H
#define CRTMASTER_H

#include <QHash>
#include "crtproject.h"

class CrtMaster
{
public:
    static CrtMaster* GetInstance();
    static void Destroy();
    void setProject(CrtProject* proj){project = proj;}
    CrtProject* Project(){return project;}
private:
    explicit CrtMaster();
    ~CrtMaster();
    static CrtMaster* m_inst;
    QHash<int,QString> m_lstDevType;
    CrtProject* project;
};

#endif // CRTMASTER_H
