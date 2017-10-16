#include "crtproject.h"
#include "common.h"

CrtProject::CrtProject(CrtObject *parent) : CrtObject(parent)
{
    setType("project");
    m_nMaxControllerID = 128;
    m_nMaxBuildingID = 80;
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

void CrtProject::addChild(CrtObject *child)
{
    if(!child->getType().compare("controller"))
    {
        if(m_lstController.contains(child))return;
        m_lstController.append(child);
    }
    else if(!child->getType().compare("building"))
    {
        if(m_lstBuilding.contains(child))return;
        m_lstBuilding.append(child);
    }
}

CrtObject *CrtProject::childAt(int nIndex, int type)
{
    if(type == 0)
    {
        if(m_lstController.count()<=0 || nIndex >= m_lstController.count() || nIndex < 0)
            return NULL;
        return m_lstController[nIndex];
    }
    else if(type == 1)
    {
        if(m_lstBuilding.count()<=0 || nIndex >= m_lstBuilding.count() || nIndex < 0)
            return NULL;
        return m_lstBuilding[nIndex];
    }

    return NULL;
}

void CrtProject::removeChild(int nIndex, int type)
{
    if(type == 0)
    {
        if(m_lstController.count()<=0 || nIndex >= m_lstController.count() || nIndex < 0)
            return;
        CrtObject* item = m_lstController[nIndex];
        m_lstController.removeAt(nIndex);
        SAFE_DELETE(item)
    }
    else if(type == 1)
    {
        if(m_lstBuilding.count()<=0 || nIndex >= m_lstBuilding.count() || nIndex < 0)
            return;
        CrtObject* item = m_lstBuilding[nIndex];
        m_lstBuilding.removeAt(nIndex);
        SAFE_DELETE(item)
    }
}

int CrtProject::indexOf(CrtObject *child)
{
    if(!child)return -1;
    if(!child->getType().compare("controller"))
    {
        return m_lstController.indexOf(child);
    }
    else if(!child->getType().compare("building"))
    {
        return m_lstBuilding.indexOf(child);
    }

    return -1;
}

int CrtProject::childCount(int type)
{
    if(type == 0)
    {
        return m_lstController.count();
    }
    else if(type == 1)
    {
        return m_lstBuilding.count();
    }

    return 0;
}

int CrtProject::getAvaliableChildID(int type)
{
    int id = -1;
    QList<int> lstID;
    if(type == 0)
    {
        foreach(CrtObject* obj,m_lstController)
        {
            lstID<<obj->getID();
        }

        for(int i=1;i<=m_nMaxControllerID;i++)
        {
            if(!lstID.contains(i))
            {
                id = i;
                break;
            }
        }
    }
    else if(type == 1)
    {
        foreach(CrtObject* obj,m_lstBuilding)
        {
            lstID<<obj->getID();
        }

        for(int i=1;i<=m_nMaxBuildingID;i++)
        {
            if(!lstID.contains(i))
            {
                id = i;
                break;
            }
        }
    }
    return id;
}

QList<int> CrtProject::getAvaliableChildsID(int type)
{
    QList<int> lstResult;
    QList<int> lstID;
    if(type == 0)
    {
        foreach(CrtObject* obj,m_lstController)
        {
            lstID<<obj->getID();
        }

        for(int i=1;i<=m_nMaxControllerID;i++)
        {
            if(!lstID.contains(i))
            {
                lstResult.append(i);
            }
        }
    }
    else if(type == 1)
    {
        foreach(CrtObject* obj,m_lstBuilding)
        {
            lstID<<obj->getID();
        }

        for(int i=1;i<=m_nMaxBuildingID;i++)
        {
            if(!lstID.contains(i))
            {
                lstResult.append(i);
            }
        }
    }
    return lstResult;
}

bool CrtProject::isChildIDAvaliable(int id, int type)
{
    bool bRes = true;
    if(type == 0)
    {
        if(id > m_nMaxControllerID)return false;

        foreach(CrtObject* obj,m_lstController)
        {
            if(obj->getID() == id)
            {
                bRes = false;
                break;
            }
        }
    }
    else if(type == 1)
    {
        if(id > m_nMaxBuildingID)return false;

        foreach(CrtObject* obj,m_lstBuilding)
        {
            if(obj->getID() == id)
            {
                bRes = false;
                break;
            }
        }
    }
    else
        bRes = false;

    return bRes;
}
