#include "crtobject.h"

CrtObject::CrtObject(CrtObject *parent)
{
    this->m_parent = parent;
    setType(OT_OBJECT);
}

CrtObject::~CrtObject()
{

}
