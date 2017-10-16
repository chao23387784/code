#include "crtdevice.h"
#include "crtmaster.h"
#include "common.h"
#include "crtdeviceitem.h"

CrtDevice::CrtDevice(CrtObject *parent) : CrtObject(parent)
{
    m_item = NULL;
    setType("device");
    m_nLayerID = -1;
    m_nBuildingID = -1;
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
    m_strDevType = t;
    if(m_item)
        m_item->setImage(QString(":/device/%1.bmp").arg(m_strDevType));
    //nType =
}

CrtDeviceItem *CrtDevice::createDeviceItem()
{
    if(!m_item)
    {
        QString strImgPath = QString(":/device/%1.bmp").arg(m_strDevType);
        m_item = new CrtDeviceItem(strImgPath,this);
        if(m_item->isPanel())
        {
            return NULL;
        }
    }
    return m_item;
}

void CrtDevice::destroyDeviceItem()
{
    SAFE_DELETE(m_item);
}

void CrtDevice::setDeviceAddress(QString a)
{
    m_strAddress = a;
}

void CrtDevice::setDeviceZone(int z)
{
    m_nZoneID = z;
}
