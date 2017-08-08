#ifndef CRTDEVICE_H
#define CRTDEVICE_H

#include "crtdeviceitem.h"
#include "crtobject.h"

class CrtDevice : public CrtObject
{
public:
    explicit CrtDevice(CrtObject *parent = 0);
    ~CrtDevice();
    void setDeviceType(int t);
    void setDeviceType(QString t);
    //int DeviceType(){return nType;}
    QString DeviceType() {return strType;}
    void setLayerID(int id){nLayerID = id;}
    int LayerID(){return nLayerID;}
private:
    int nType;
    QString strType;
    int nLayerID;
    CrtDeviceItem* item;
};

#endif // CRTDEVICE_H
