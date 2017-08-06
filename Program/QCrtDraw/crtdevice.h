#ifndef CRTDEVICE_H
#define CRTDEVICE_H

#include "crtdeviceitem.h"
#include "crtobject.h"

class CrtDevice : public CrtObject
{
public:
    explicit CrtDevice(CrtObject *parent = 0);
    void setDeviceType(int t);
    void setDeviceType(QString t);
    //int DeviceType(){return nType;}
    QString DeviceType() {return strType;}
private:
    int nType;
    QString strType;
    CrtDeviceItem* item;
};

#endif // CRTDEVICE_H
