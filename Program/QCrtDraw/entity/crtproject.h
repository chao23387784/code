#ifndef CRTPROJECT_H
#define CRTPROJECT_H

#include <QList>
#include "crtcontroller.h"
#include "crtbuilding.h"
#include "crtobject.h"


class CrtProject : public CrtObject
{
public:
    explicit CrtProject(CrtObject *parent = 0);
    ~CrtProject();

    virtual void addChild(CrtObject* child);
    virtual CrtObject* childAt(int nIndex,int type = 0);
    virtual void removeChild(int nIndex,int type = 0);
    virtual int indexOf(CrtObject* child);
    virtual int childCount(int type = 0);
    virtual int getAvaliableChildID(int type = 0);
    virtual QList<int> getAvaliableChildsID(int type = 0);
    virtual bool isChildIDAvaliable(int id,int type = 0);

public:
    int maxControllerID;
    int maxBuildingID;
    QList<CrtObject*> m_lstController;
    QList<CrtObject*> m_lstBuilding;
};

#endif // CRTPROJECT_H
