#include "crtcontroller.h"
#include "common.h"

CrtController::CrtController(CrtObject *parent) : CrtObject(parent)
{
    setType("controller");
    m_nMaxLoopID = 64;
}

CrtController::~CrtController()
{
    foreach(CrtObject* item,m_lstLoop)
    {
        SAFE_DELETE(item);
    }
    m_lstLoop.clear();
}

void CrtController::addChild(CrtObject *child)
{
    if(m_lstLoop.contains(child))return;
    m_lstLoop.append(child);
}

CrtObject *CrtController::childAt(int nIndex, int type)
{
    Q_UNUSED(type);
    if(m_lstLoop.count()<=0 || nIndex >= m_lstLoop.count() || nIndex < 0)
        return NULL;
    return m_lstLoop[nIndex];
}

void CrtController::removeChild(int nIndex, int type)
{
    Q_UNUSED(type);
    if(m_lstLoop.count()<=0 || nIndex >= m_lstLoop.count() || nIndex < 0)
        return;
    CrtObject* item = m_lstLoop[nIndex];
    m_lstLoop.removeAt(nIndex);
    SAFE_DELETE(item)
}

int CrtController::indexOf(CrtObject *child)
{
    if(child != NULL)
    {
        return m_lstLoop.indexOf(const_cast<CrtObject*>(child));
    }
    return -1;
}

int CrtController::childCount(int type)
{
    Q_UNUSED(type);
    return m_lstLoop.count();
}

int CrtController::getAvaliableChildID(int type)
{
    Q_UNUSED(type);
    int id = -1;
    QList<int> lstID;
    foreach(CrtObject* obj,m_lstLoop)
    {
        lstID<<obj->getID();
    }

    for(int i=1;i<=m_nMaxLoopID;i++)
    {
        if(!lstID.contains(i))
        {
            id = i;
            break;
        }
    }

    return id;
}

QList<int> CrtController::getAvaliableChildsID(int type)
{
    Q_UNUSED(type);
    QList<int> lstResult;
    QList<int> lstID;
    foreach(CrtObject* obj,m_lstLoop)
    {
        lstID<<obj->getID();
    }

    for(int i=1;i<=m_nMaxLoopID;i++)
    {
        if(!lstID.contains(i))
        {
            lstResult.append(i);
        }
    }

    return lstResult;
}

bool CrtController::isChildIDAvaliable(int id, int type)
{
    Q_UNUSED(type);
    bool bRes = true;

    if(id > m_nMaxLoopID)return false;

    foreach(CrtObject* obj,m_lstLoop)
    {
        if(obj->getID() == id)
        {
            bRes = false;
            break;
        }
    }

    return bRes;
}

void CrtController::setControllerType(QString t)
{
    m_strType = t;
}

void CrtController::setSystemType(QString t)
{
    m_strSystem = t;
}
