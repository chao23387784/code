#ifndef CRTOBJECT_H
#define CRTOBJECT_H

#include <QList>

class CrtObject
{
public:
    explicit CrtObject(CrtObject *parent = 0);
    ~CrtObject();
    void setID(int nID){id = nID;}
    int ID(){return id;}
    void setName(const QString strName){name = strName;}
    QString Name(){return name;}
    void setParent(CrtObject*& p){parent = p;}
    CrtObject* Parent(){return parent;}
    void setType(const QString strType){type = strType;}
    QString Type(){return type;}
    void setKey(int k){key = k;}
    int Key(){return key;}
private:
    int id;
    QString name;
    QString type;
    CrtObject* parent;
    int key;
};

#endif // CRTOBJECT_H
