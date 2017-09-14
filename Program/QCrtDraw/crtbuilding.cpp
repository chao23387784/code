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

int CrtBuilding::getAvaliableLayerID()
{
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
