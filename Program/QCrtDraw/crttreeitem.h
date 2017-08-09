#ifndef CRTTREEITEM_H
#define CRTTREEITEM_H
#include <QList>
#include "crtobject.h"

class CrtTreeItem
{
public:
    CrtTreeItem();
    ~CrtTreeItem();
    int Column(){return 0;}
    int Row();
    void setParent(CrtTreeItem* parent){this->parent = parent;}
    CrtTreeItem* Parent(){return parent;}
    void addChild(CrtTreeItem* child);
    CrtTreeItem* childAt(int nIndex);
    void removeChild(int nIndex);
    int indexOf(const CrtTreeItem* child);
    int childCount(){return children.count();}
    void setData(CrtObject* data){this->data = data;}
    CrtObject* Data(){return data;}
    void load(CrtObject* obj,int type = 0);
private:
    CrtTreeItem* parent;
    QList<CrtTreeItem*> children;
    CrtObject* data;
};

#endif // CRTTREEITEM_H
