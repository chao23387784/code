#include "crtcontroller.h"
#include "common.h"

CrtController::CrtController(CrtObject *parent) : CrtObject(parent)
{
    setType("controller");
    maxLoopID = 64;
}

CrtController::~CrtController()
{
    foreach(CrtObject* item,m_lstLoop)
    {
        SAFE_DELETE(item);
    }
    m_lstLoop.clear();
}

int CrtController::getAvaliableLoopID()
{
    int id = -1;
    QList<int> lstID;
    foreach(CrtObject* obj,m_lstLoop)
    {
        lstID<<obj->ID();
    }

    for(int i=1;i<=maxLoopID;i++)
    {
        if(!lstID.contains(i))
        {
            id = i;
            break;
        }
    }

    return id;
}
