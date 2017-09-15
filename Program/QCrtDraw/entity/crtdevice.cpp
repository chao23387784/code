#include "crtdevice.h"
#include "crtmaster.h"
#include "common.h"
#include "crtdeviceitem.h"

CrtDevice::CrtDevice(CrtObject *parent) : CrtObject(parent)
{
    item = NULL;
    setType("device");
    nLayerID = -1;
    nBuildingID = -1;
}

CrtDevice::~CrtDevice()
{
    destroyDeviceItem();
}

/*void CrtDevice::setDeviceType(int t)
{
    nType = t;
    //strType =
}*/

void CrtDevice::setDeviceType(QString t)
{
    strType = t;
    if(item)
        item->setImage(QString(":/device/%1.bmp").arg(strType));
    //nType =
}

CrtDeviceItem *CrtDevice::createDeviceItem()
{
    if(!item)
    {
        QString strImgPath = QString(":/device/%1.bmp").arg(strType);
        item = new CrtDeviceItem(strImgPath,this);
        if(item->isPanel())
        {
            return NULL;
        }
    }
    return item;
}

void CrtDevice::destroyDeviceItem()
{
    SAFE_DELETE(item);
}
