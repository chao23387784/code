#include "crtproject.h"
#include "common.h"

CrtProject::CrtProject(CrtObject *parent) : CrtObject(parent)
{
    setType("project");
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
