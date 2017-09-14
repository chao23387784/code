#include "crtobject.h"

CrtObject::CrtObject(CrtObject *parent)
{
    this->parent = parent;
    setType("object");
}

CrtObject::~CrtObject()
{

}
