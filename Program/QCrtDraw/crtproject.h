#ifndef CRTPROJECT_H
#define CRTPROJECT_H

#include <QList>
#include "crtcontroller.h"
#include "crtbuilding.h"
#include "crtobject.h"

enum DataStatus{
    New,
    Modify,
    Delete
};

class CrtProject : public CrtObject
{
public:
    explicit CrtProject(CrtObject *parent = 0);
    ~CrtProject();
public:
    QList<CrtController*> m_lstController;
    QList<CrtBuilding*> m_lstBuilding;
    QList<CrtObject*> m_lstModifyObjects;
};

#endif // CRTPROJECT_H
