#ifndef CRTCONTROLLER_H
#define CRTCONTROLLER_H

#include <QList>
#include "crtloop.h"
#include "crtobject.h"

class CrtController : public CrtObject
{
public:
    explicit CrtController(CrtObject *parent = 0);
    ~CrtController();

    virtual void addChild(CrtObject* child);
    virtual CrtObject* childAt(int nIndex,int type = 0);
    virtual void removeChild(int nIndex,int type = 0);
    virtual int indexOf(CrtObject* child);
    virtual int childCount(int type = 0);
    virtual int getAvaliableChildID(int type = 0);
    virtual QList<int> getAvaliableChildsID(int type = 0);
    virtual bool isChildIDAvaliable(int id,int type = 0);

    void setControllerType(int t);
    void setControllerType(QString t);
    //int DeviceType(){return nType;}
    QString ControllerType() {return strType;}
    void setSystemType(int t);
    void setSystemType(QString t);
    QString SystemType(){return strSystem;}
    void setNetID(int t){netid = t;}
    int NetID(){return netid;}
public:
    int netid;
    int nSystem;
    QString strSystem;
    int nType;
    QString strType;
    int maxLoopID;
    QList<CrtObject*> m_lstLoop;
};

#endif // CRTCONTROLLER_H
