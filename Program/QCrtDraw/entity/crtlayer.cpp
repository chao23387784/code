#include "crtlayer.h"
#include "common.h"

CrtLayer::CrtLayer(CrtObject *parent) : CrtObject(parent)
{
    m_strFilePath = "";
    m_scene = new CrtGraphicsScene(this);
    setType("layer");
}

CrtLayer::~CrtLayer()
{
    foreach(CrtObject* item,m_lstDevice)
    {
        dynamic_cast<CrtDevice*>(item)->destroyDeviceItem();
    }
    SAFE_DELETE(m_scene);
    m_lstDevice.clear();
}

void CrtLayer::addChild(CrtObject *child)
{
    if(m_lstDevice.contains(child))return;
    m_lstDevice.append(child);
    dynamic_cast<CrtDevice*>(child)->setLayerID(getID());
    dynamic_cast<CrtDevice*>(child)->setBuildingID(getParent()->getID());
    m_scene->addItem(dynamic_cast<CrtDevice*>(child)->createDeviceItem());
}

CrtObject *CrtLayer::childAt(int nIndex, int type)
{
    Q_UNUSED(type);
    if(m_lstDevice.count()<=0 || nIndex >= m_lstDevice.count() || nIndex < 0)
        return NULL;
    return m_lstDevice[nIndex];
}

void CrtLayer::removeChild(int nIndex, int type)
{
    Q_UNUSED(type);
    Q_ASSERT(m_scene);

    if(m_lstDevice.count()<=0 || nIndex >= m_lstDevice.count() || nIndex < 0)
        return;

    CrtDevice* item = dynamic_cast<CrtDevice*>(m_lstDevice[nIndex]);
    m_scene->removeItem(item->createDeviceItem());
    item->destroyDeviceItem();
    item->setLayerID(-1);
    item->setBuildingID(-1);
    m_lstDevice.removeAt(nIndex);
}

int CrtLayer::indexOf(CrtObject *child)
{
    if(child != NULL)
    {
        return m_lstDevice.indexOf(const_cast<CrtObject*>(child));
    }
    return -1;
}

int CrtLayer::childCount(int type)
{
    Q_UNUSED(type);
    return m_lstDevice.count();
}


/*void CrtLayer::setScene(CrtScene *s)
{
    if(scene)
    {
        delete scene;
        scene = NULL;
    }

    scene = s;
}*/

CrtGraphicsScene *CrtLayer::getScene()
{
    return m_scene;
}

void CrtLayer::setBackground(QString strPath)
{
    Q_ASSERT(m_scene);
    m_scene->setBackground(strPath);
    m_scene->addItem(m_scene->getBackground());
    m_strFilePath = strPath;
}

/*CrtBackground *CrtLayer::BackGround()
{
    return bg;
}*/

