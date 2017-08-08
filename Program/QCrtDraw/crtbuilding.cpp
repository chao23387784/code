#include "crtbuilding.h"
#include "common.h"

CrtBuilding::CrtBuilding(CrtObject *parent) : CrtObject(parent)
{
    setType("building");
}

CrtBuilding::~CrtBuilding()
{
    foreach(CrtObject* item,m_lstLayer)
    {
        SAFE_DELETE(item);
    }
    m_lstLayer.clear();
}
