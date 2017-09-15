#ifndef CRTOBJECT_H
#define CRTOBJECT_H

#include <QList>

class CrtObject
{
public:
    explicit CrtObject(CrtObject *parent = 0);
    ~CrtObject();
    
    virtual void addChild(CrtObject* child){Q_UNUSED(child);}
    virtual CrtObject* childAt(int nIndex,int type = 0){Q_UNUSED(nIndex);Q_UNUSED(type);return NULL;}
    virtual void removeChild(int nIndex,int type = 0){Q_UNUSED(nIndex);Q_UNUSED(type);}
    virtual int indexOf(CrtObject* child){Q_UNUSED(child);return -1;}
    virtual int childCount(int type = 0){Q_UNUSED(type);return 0;}
    virtual int getAvaliableChildID(int type = 0){Q_UNUSED(type);return 0;}
    virtual QList<int> getAvaliableChildsID(int type = 0){Q_UNUSED(type);return QList<int>();}
    virtual bool isChildIDAvaliable(int id,int type = 0){Q_UNUSED(id);Q_UNUSED(type);return false;}
    
    void setID(int nID){id = nID;}
    int ID(){return id;}
    void setName(const QString strName){name = strName;}
    QString Name(){return name;}
    void setParent(CrtObject* p){parent = p;}
    CrtObject* Parent(){return parent;}
    void setType(const QString strType){type = strType;}
    QString Type(){return type;}
private:
    int id;
    QString name;
    QString type;
    CrtObject* parent;
};

#endif // CRTOBJECT_H
