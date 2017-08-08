#include "crtloop.h"
#include "common.h"

CrtLoop::CrtLoop(CrtObject *parent) : CrtObject(parent)
{
    setType("loop");
}

CrtLoop::~CrtLoop()
{
    foreach(CrtObject* item,m_lstDevice)
    {
        SAFE_DELETE(item);
    }
    m_lstDevice.clear();
}
