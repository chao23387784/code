#ifndef CRTBUILDING_H
#define CRTBUILDING_H

#include "crtlayer.h"
#include "crtobject.h"
#include <QList>

class CrtBuilding : public CrtObject
{
public:
    explicit CrtBuilding(CrtObject *parent = 0);
    ~CrtBuilding();

    virtual void addChild(CrtObject* child);
    virtual CrtObject* childAt(int nIndex,int type = 0);
    virtual void removeChild(int nIndex,int type = 0);
    virtual int indexOf(CrtObject* child);
    virtual int childCount(int type = 0);
    virtual int getAvaliableChildID(int type = 0);
    virtual QList<int> getAvaliableChildsID(int type = 0);
    virtual bool isChildIDAvaliable(int id,int type = 0);
public:
    int maxLayerID;
    QList<CrtObject*> m_lstLayer;
};

#endif // CRTBUILDING_H
