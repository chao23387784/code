#include "crtloop.h"
#include "common.h"

CrtLoop::CrtLoop(CrtObject *parent) : CrtObject(parent)
{
    setType(OT_LOOP);
    m_nMaxDeviceID = 252;
}

CrtLoop::~CrtLoop()
{
    foreach(CrtObject* item,m_lstDevice)
    {
        SAFE_DELETE(item);
    }
    m_lstDevice.clear();
}

void CrtLoop::addChild(CrtObject *child)
{
    if(m_lstDevice.contains(child))return;
    m_lstDevice.append(child);
}

CrtObject *CrtLoop::childAt(int nIndex, int type)
{
    Q_UNUSED(type);
    if(m_lstDevice.count()<=0 || nIndex >= m_lstDevice.count() || nIndex < 0)
        return NULL;
    return m_lstDevice[nIndex];
}

void CrtLoop::removeChild(int nIndex, int type)
{
    Q_UNUSED(type);
    if(m_lstDevice.count()<=0 || nIndex >= m_lstDevice.count() || nIndex < 0)
        return;
    CrtObject* item = m_lstDevice[nIndex];
    m_lstDevice.removeAt(nIndex);
    SAFE_DELETE(item)
}

int CrtLoop::indexOf(CrtObject *child)
{
    if(child != NULL)
    {
        return m_lstDevice.indexOf(const_cast<CrtObject*>(child));
    }
    return -1;
}

int CrtLoop::childCount(int type)
{
    Q_UNUSED(type);
    return m_lstDevice.count();
}

int CrtLoop::getAvaliableChildID(int type)
{
    Q_UNUSED(type);
    int id = -1;
    QList<int> lstID;
    foreach(CrtObject* obj,m_lstDevice)
    {
        lstID<<obj->getID();
    }

    for(int i=1;i<=m_nMaxDeviceID;i++)
    {
        if(!lstID.contains(i))
        {
            id = i;
            break;
        }
    }

    return id;
}

QList<int> CrtLoop::getAvaliableChildsID(int type)
{
    Q_UNUSED(type);
    QList<int> lstResult;
    QList<int> lstID;
    foreach(CrtObject* obj,m_lstDevice)
    {
        lstID<<obj->getID();
    }

    for(int i=1;i<=m_nMaxDeviceID;i++)
    {
        if(!lstID.contains(i))
        {
            lstResult.append(i);
        }
    }

    return lstResult;
}

bool CrtLoop::isChildIDAvaliable(int id, int type)
{
    Q_UNUSED(type);
    bool bRes = true;

    if(id > m_nMaxDeviceID)return false;

    foreach(CrtObject* obj,m_lstDevice)
    {
        if(obj->getID() == id)
        {
            bRes = false;
            break;
        }
    }

    return bRes;
}
