#ifndef CRTDEVICE_H
#define CRTDEVICE_H

#include "crtobject.h"

class CrtDeviceItem;

class CrtDevice : public CrtObject
{
public:
    explicit CrtDevice(CrtObject *parent = 0);
    ~CrtDevice();

    virtual void addChild(CrtObject* child){Q_UNUSED(child);}
    virtual CrtObject* childAt(int nIndex,int type = 0){Q_UNUSED(nIndex);Q_UNUSED(type);return NULL;}
    virtual void removeChild(int nIndex,int type = 0){Q_UNUSED(nIndex);Q_UNUSED(type);}
    virtual int indexOf(CrtObject* child){Q_UNUSED(child);return -1;}
    virtual int childCount(int type = 0){Q_UNUSED(type);return 0;}
    virtual int getAvaliableChildID(int type = 0){Q_UNUSED(type);return 0;}
    virtual QList<int> getAvaliableChildsID(int type = 0){Q_UNUSED(type);return QList<int>();}
    virtual bool isChildIDAvaliable(int id,int type = 0){Q_UNUSED(id);Q_UNUSED(type);return false;}

    void setDeviceType(int t);
    void setDeviceType(QString t);
    //int DeviceType(){return nType;}
    QString DeviceType() {return strType;}
    void setLayerID(int id){nLayerID = id;}
    int LayerID(){return nLayerID;}
    void setBuildingID(int id){nBuildingID = id;}
    int BuildingID(){return nBuildingID;}
    CrtDeviceItem* createDeviceItem();
    void destroyDeviceItem();
    bool isOnMap(){return item != NULL;}
private:
    int nType;
    QString strType;
    int nLayerID;
    int nBuildingID;
    CrtDeviceItem* item;
};

#endif // CRTDEVICE_H
