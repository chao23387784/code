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
    backgroundItem = NULL;
    layer = NULL;
}

CrtGraphicsScene::CrtGraphicsScene(CrtLayer *layer)
{
    backgroundItem = NULL;
    this->layer = layer;
}

CrtGraphicsScene::~CrtGraphicsScene()
{
    SAFE_DELETE(backgroundItem);
}

CrtBackground *CrtGraphicsScene::Background()
{
    if(backgroundItem!=NULL)
        return backgroundItem;
    return NULL;
}

void CrtGraphicsScene::setBackground(QString strPath)
{
    SAFE_DELETE(backgroundItem);
    backgroundItem = new CrtBackground();
    backgroundItem->setWmfFile(strPath);
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
            if(device->BuildingID() != -1 && device->LayerID() != -1)
            {
                CrtObject* ly = CrtMaster::GetInstance()->findMapObject(0,device->BuildingID(),device->LayerID());
                ly->removeChild(ly->indexOf(obj));
            }
            device->createDeviceItem()->setPos(event->scenePos());
            layer->addChild(obj);
            clearSelection();
            device->createDeviceItem()->setSelected(true);
            emit CrtMaster::GetInstance()->getCrtGraphicsView()->dragDone();
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
                if(layer)
                {
                    CrtDevice* device = item->Device();
                    Q_ASSERT(device);
                    layer->removeChild(layer->indexOf(device));
                }
            }
        }
    } else {
        QGraphicsScene::keyPressEvent(event);
    }
}

void CrtGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    CrtSetDeviceDlg* dlg = CrtMaster::GetInstance()->getCrtSetDeviceDlg();
    if(dlg->isVisible())
    {
        CrtObject* obj = dlg->getCurrentObject();
        if(obj)
        {
            CrtDevice* device = dynamic_cast<CrtDevice*>(obj);
            if(device->BuildingID() != -1 && device->LayerID() != -1)
            {
                CrtObject* ly = CrtMaster::GetInstance()->findMapObject(0,device->BuildingID(),device->LayerID());
                ly->removeChild(ly->indexOf(obj));
            }
            device->createDeviceItem()->setPos(event->scenePos());
            layer->addChild(obj);
            clearSelection();
            device->createDeviceItem()->setSelected(true);
            emit CrtMaster::GetInstance()->getCrtGraphicsView()->dragDone();
        }
    }
    else
    {
        QGraphicsScene::mousePressEvent(event);
    }
}
