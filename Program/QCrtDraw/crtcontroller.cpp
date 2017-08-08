#include "crtcontroller.h"
#include "common.h"

CrtController::CrtController(CrtObject *parent) : CrtObject(parent)
{
    setType("controller");
}

CrtController::~CrtController()
{
    foreach(CrtObject* item,m_lstLoop)
    {
        SAFE_DELETE(item);
    }
    m_lstLoop.clear();
}
