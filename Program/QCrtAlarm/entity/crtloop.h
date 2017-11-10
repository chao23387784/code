#ifndef CRTLOOP_H
#define CRTLOOP_H

#include <QList>
#include "crtdevice.h"
#include "crtobject.h"

class CrtLoop : public CrtObject
{
public:
    explicit CrtLoop(CrtObject *parent = 0);
    ~CrtLoop();

    virtual void addChild(CrtObject* child);
    virtual CrtObject* childAt(int nIndex,int type = 0);
    virtual void removeChild(int nIndex,int type = 0);
    virtual int indexOf(CrtObject* child);
    virtual int childCount(int type = 0);
    virtual int getAvaliableChildID(int type = 0);
    virtual QList<int> getAvaliableChildsID(int type = 0);
    virtual bool isChildIDAvaliable(int id,int type = 0);
public:
    int m_nMaxDeviceID;
    QList<CrtObject*> m_lstDevice;
};

#endif // CRTLOOP_H
