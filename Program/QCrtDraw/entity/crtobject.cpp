#include "crtobject.h"

CrtObject::CrtObject(CrtObject *parent)
{
    this->m_parent = parent;
    setType("object");
}

CrtObject::~CrtObject()
{

}
