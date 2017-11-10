#ifndef CRTOBJECT_H
#define CRTOBJECT_H

#include <QList>

enum ObjectType
{
    OT_OBJECT,
    OT_PROJECT,
    OT_CONTROLLER,
    OT_LOOP,
    OT_DEVICE,
    OT_BUILDING,
    OT_LAYER,
    OT_TEMP
};

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
    
    void setID(int nID){m_nID = nID;}
    int getID(){return m_nID;}
    void setName(const QString strName){m_strName = strName;}
    QString getName(){return m_strName;}
    void setParent(CrtObject* p){m_parent = p;}
    CrtObject* getParent(){return m_parent;}
    void setType(ObjectType type){m_type = type;}
    ObjectType getType(){return m_type;}
private:
    int m_nID;
    QString m_strName;
    ObjectType m_type;
    CrtObject* m_parent;
};

#endif // CRTOBJECT_H
