#include "crtproject.h"
#include "common.h"

CrtProject::CrtProject(CrtObject *parent) : CrtObject(parent)
{
    setType("project");
    maxControllerID = 128;
    maxBuildingID = 80;
}

CrtProject::~CrtProject()
{
    foreach(CrtObject* item,m_lstBuilding)
    {
        SAFE_DELETE(item);
    }
    m_lstBuilding.clear();

    foreach(CrtObject* item,m_lstController)
    {
        SAFE_DELETE(item);
    }
    m_lstController.clear();
}

int CrtProject::getAvaliableControllerID()
{
    int id = -1;
    QList<int> lstID;
    foreach(CrtObject* obj,m_lstController)
    {
        lstID<<obj->ID();
    }

    for(int i=1;i<=maxControllerID;i++)
    {
        if(!lstID.contains(i))
        {
            id = i;
            break;
        }
    }

    return id;
}

int CrtProject::getAvaliableBuildingID()
{
    int id = -1;
    QList<int> lstID;
    foreach(CrtObject* obj,m_lstBuilding)
    {
        lstID<<obj->ID();
    }

    for(int i=1;i<=maxBuildingID;i++)
    {
        if(!lstID.contains(i))
        {
            id = i;
            break;
        }
    }

    return id;
}
