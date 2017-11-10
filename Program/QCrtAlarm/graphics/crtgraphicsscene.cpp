#include "crtgraphicsscene.h"
#include "common.h"
#include "crtmaster.h"
#include <QMimeData>
#include "crtobject.h"
#include "crtproject.h"
#include "crtcontroller.h"
#include "crtloop.h"
#include "crtdevice.h"
#include "crtdeviceitem.h"
#include "crtmaster.h"
#include <QMessageBox>
#include "crtgraphicsview.h"
#include "crtsetdevicedlg.h"

CrtGraphicsScene::CrtGraphicsScene(QObject *parent)
    :QGraphicsScene(parent)
{
    m_backgroundItem = new CrtBackground();
    m_layer = NULL;
    addItem(m_backgroundItem);
}

CrtGraphicsScene::CrtGraphicsScene(CrtLayer *layer)
{
    m_backgroundItem = new CrtBackground();
    this->m_layer = layer;
    addItem(m_backgroundItem);
}

CrtGraphicsScene::~CrtGraphicsScene()
{
    SAFE_DELETE(m_backgroundItem);
}

CrtBackground *CrtGraphicsScene::getBackground()
{
    if(m_backgroundItem!=NULL)
        return m_backgroundItem;
    return NULL;
}

void CrtGraphicsScene::setBackground(QString strPath)
{
    SAFE_DELETE(m_backgroundItem);
    m_backgroundItem = new CrtBackground();
    m_backgroundItem->setWmfFile(strPath);
}

void CrtGraphicsScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if(event->mimeData()->hasFormat("project/items"))
    {
        event->setAccepted(true);
    }
    else
    {
        event->setAccepted(false);
    }
}

void CrtGraphicsScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    event->accept();
}

void CrtGraphicsScene::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
}

void CrtGraphicsScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    if(event->mimeData()->hasFormat("project/items"))
    {
        QByteArray itemData = event->mimeData()->data("project/items");
        QDataStream dataStream(&itemData,QIODevice::ReadOnly);
        qlonglong ptr;
        dataStream >> ptr;
        CrtObject* obj = reinterpret_cast<CrtObject*>(ptr);

        if(obj)
        {
            CrtDevice* device = dynamic_cast<CrtDevice*>(obj);
            if(device->getBuildingID() != -1 && device->getLayerID() != -1)
            {
                CrtObject* ly = CrtMaster::getInstance()->findMapObject(0,device->getBuildingID(),device->getLayerID());
                ly->removeChild(ly->indexOf(obj));
            }
            device->createDeviceItem()->setPos(event->scenePos());
            m_layer->addChild(obj);
            clearSelection();
            device->createDeviceItem()->setSelected(true);
            emit CrtMaster::getInstance()->getCrtGraphicsView()->sigDropDevice();
        }
    }
}

void CrtGraphicsScene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete && !selectedItems().isEmpty()) {
        if( QMessageBox::Yes == QMessageBox::information(NULL,tr("warning"),tr("delete selected items?"),QMessageBox::Yes|QMessageBox::No))
        {
            while (!selectedItems().isEmpty()) {
                CrtDeviceItem* item = static_cast<CrtDeviceItem*>(selectedItems().front());
                removeItem(item);
                if(m_layer)
                {
                    CrtDevice* device = item->getDevice();
                    Q_ASSERT(device);
                    m_layer->removeChild(m_layer->indexOf(device));
                }
            }
        }
    } else {
        QGraphicsScene::keyPressEvent(event);
    }
}

void CrtGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    CrtSetDeviceDlg* dlg = CrtMaster::getInstance()->getCrtSetDeviceDlg();
    if(dlg->isVisible())
    {
        CrtObject* obj = dlg->getCurrentObject();
        if(obj)
        {
            CrtDevice* device = dynamic_cast<CrtDevice*>(obj);
            if(device->getBuildingID() != -1 && device->getLayerID() != -1)
            {
                CrtObject* ly = CrtMaster::getInstance()->findMapObject(0,device->getBuildingID(),device->getLayerID());
                ly->removeChild(ly->indexOf(obj));
            }
            device->createDeviceItem()->setPos(event->scenePos());
            m_layer->addChild(obj);
            clearSelection();
            device->createDeviceItem()->setSelected(true);
            emit CrtMaster::getInstance()->getCrtGraphicsView()->sigDropDevice();
        }
    }
    else
    {
        QGraphicsScene::mousePressEvent(event);
    }
}
