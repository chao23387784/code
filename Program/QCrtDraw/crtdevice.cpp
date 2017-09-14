#include "crtdevice.h"
#include "crtmaster.h"

CrtDevice::CrtDevice(CrtObject *parent) : CrtObject(parent)
{
    setType("device");
}

CrtDevice::~CrtDevice()
{

}

/*void CrtDevice::setDeviceType(int t)
{
    nType = t;
    //strType =
}*/

void CrtDevice::setDeviceType(QString t)
{
    strType = t;
    //nType =
}
