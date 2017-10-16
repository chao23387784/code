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
    QString getDeviceType() {return m_strDevType;}
    void setLayerID(int id){m_nLayerID = id;}
    int getLayerID(){return m_nLayerID;}
    void setBuildingID(int id){m_nBuildingID = id;}
    int getBuildingID(){return m_nBuildingID;}
    CrtDeviceItem* createDeviceItem();
    void destroyDeviceItem();
    bool isOnMap(){return m_item != NULL;}
    void setDeviceAddress(QString a);
    QString getDeviceAddress(){return m_strAddress;}
    void setDeviceZone(int z);
    int getDeviceZone(){return m_nZoneID;}
private:
    int m_nType;
    QString m_strDevType;
    QString m_strAddress;
    int m_nZoneID;
    int m_nLayerID;
    int m_nBuildingID;
    CrtDeviceItem* m_item;
};

#endif // CRTDEVICE_H
