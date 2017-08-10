#include "crtloop.h"
#include "common.h"

CrtLoop::CrtLoop(CrtObject *parent) : CrtObject(parent)
{
    setType("loop");
    maxDeviceID = 252;
}

CrtLoop::~CrtLoop()
{
    foreach(CrtObject* item,m_lstDevice)
    {
        SAFE_DELETE(item);
    }
    m_lstDevice.clear();
}

int CrtLoop::getAvaliableDeviceID()
{
    int id = -1;
    QList<int> lstID;
    foreach(CrtObject* obj,m_lstDevice)
    {
        lstID<<obj->ID();
    }

    for(int i=1;i<=maxDeviceID;i++)
    {
        if(!lstID.contains(i))
        {
            id = i;
            break;
        }
    }

    return id;
}
