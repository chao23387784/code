#ifndef CRTLAYER_H
#define CRTLAYER_H

#include "crtgraphicsscene.h"
#include "crtdevice.h"
#include "crtobject.h"
#include <QList>
#include "crtbackground.h"

class CrtLayer : public CrtObject
{
public:
    explicit CrtLayer(CrtObject *parent = 0);
    ~CrtLayer();

    virtual void addChild(CrtObject* child);
    virtual CrtObject* childAt(int nIndex,int type = 0);
    virtual void removeChild(int nIndex,int type = 0);
    virtual int indexOf(CrtObject* child);
    virtual int childCount(int type = 0);
    virtual int getAvaliableChildID(int type = 0){Q_UNUSED(type);return 0;}
    virtual QList<int> getAvaliableChildsID(int type = 0){Q_UNUSED(type);return QList<int>();}
    virtual bool isChildIDAvaliable(int id,int type = 0){Q_UNUSED(id);Q_UNUSED(type);return false;}

    //void setScene(CrtScene* s);
    CrtGraphicsScene* Scene();
    void setBackground(QString strPath);
    QString FilePath(){return filePath;}
private:
    CrtGraphicsScene* scene;
    QString filePath;
public:
    int maxDeviceCount;
    QList<CrtObject*> m_lstDevice;
};

#endif // CRTLAYER_H
