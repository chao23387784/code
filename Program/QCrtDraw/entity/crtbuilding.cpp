#include "crtbuilding.h"
#include "common.h"

CrtBuilding::CrtBuilding(CrtObject *parent) : CrtObject(parent)
{
    setType("building");
    maxLayerID = 80;
}

CrtBuilding::~CrtBuilding()
{
    foreach(CrtObject* item,m_lstLayer)
    {
        SAFE_DELETE(item);
    }
    m_lstLayer.clear();
}

void CrtBuilding::addChild(CrtObject *child)
{
    if(m_lstLayer.contains(child))return;
    m_lstLayer.append(child);
}

CrtObject *CrtBuilding::childAt(int nIndex, int type)
{
    Q_UNUSED(type);
    if(m_lstLayer.count()<=0 || nIndex >= m_lstLayer.count() || nIndex < 0)
        return NULL;
    return m_lstLayer[nIndex];
}

void CrtBuilding::removeChild(int nIndex, int type)
{
    Q_UNUSED(type);
    if(m_lstLayer.count()<=0 || nIndex >= m_lstLayer.count() || nIndex < 0)
        return;
    CrtObject* item = m_lstLayer[nIndex];
    m_lstLayer.removeAt(nIndex);
    SAFE_DELETE(item)
}

int CrtBuilding::indexOf(CrtObject *child)
{
    if(child != NULL)
    {
        return m_lstLayer.indexOf(const_cast<CrtObject*>(child));
    }
    return -1;
}

int CrtBuilding::childCount(int type)
{
    Q_UNUSED(type);
    return m_lstLayer.count();
}

int CrtBuilding::getAvaliableChildID(int type)
{
    Q_UNUSED(type);
    int id = -1;
    QList<int> lstID;
    foreach(CrtObject* obj,m_lstLayer)
    {
        lstID<<obj->ID();
    }

    for(int i=1;i<=maxLayerID;i++)
    {
        if(!lstID.contains(i))
        {
            id = i;
            break;
        }
    }

    return id;
}

QList<int> CrtBuilding::getAvaliableChildsID(int type)
{
    Q_UNUSED(type);
    QList<int> lstResult;
    QList<int> lstID;
    foreach(CrtObject* obj,m_lstLayer)
    {
        lstID<<obj->ID();
    }

    for(int i=1;i<=maxLayerID;i++)
    {
        if(!lstID.contains(i))
        {
            lstResult.append(i);
        }
    }

    return lstResult;
}

bool CrtBuilding::isChildIDAvaliable(int id, int type)
{
    Q_UNUSED(type);
    bool bRes = true;

    if(id > maxLayerID)return false;

    foreach(CrtObject* obj,m_lstLayer)
    {
        if(obj->ID() == id)
        {
            bRes = false;
            break;
        }
    }

    return bRes;
}
