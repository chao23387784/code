#include "crttreeview.h"
#include "crttreemodel.h"
#include "crtmaster.h"
#include <QDrag>
#include <QMimeData>
#include <QPixmap>

CrtTreeView::CrtTreeView(QWidget *parent) : QTreeView(parent)
{
    //setDragDropMode(QAbstractItemView::DragOnly);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setUniformRowHeights(true);
    setExpandsOnDoubleClick(false);
    setEditTriggers(QAbstractItemView::SelectedClicked);
    connect(this,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(slotItemDoubleClicked(QModelIndex)));
}

void CrtTreeView::expandItem(const QModelIndex &index)
{
    if(!index.isValid())return;
    CrtTreeModel* md = (CrtTreeModel*)model();
    CrtObject* item = (CrtObject*)index.internalPointer();

    while(item)
    {
        expand(md->indexFromItem(item));
        item = item->getParent();
    }
}

void CrtTreeView::deleteItem(const QModelIndex &index)
{
    CrtObject* item = (CrtObject*)index.internalPointer();
    CrtObject* parent = (CrtObject*)item->getParent();
    CrtTreeModel* md = (CrtTreeModel*)model();

    Q_ASSERT(parent);

    int row = parent->indexOf(item);
    md->deleteItem(index);

    QModelIndex idx = md->index(row,0,md->indexFromItem(parent));
    if(!idx.isValid())
    {
        if(row)
            idx = md->index(row-1,0,md->indexFromItem(parent));
        else
            idx = md->indexFromItem(parent);
    }

    expandItem(idx);
    setCurrentIndex(idx);
    //emit clicked(idx);
}

void CrtTreeView::insertItem(CrtObject *data, const QModelIndex &parent)
{   
    CrtTreeModel* md = (CrtTreeModel*)model();
    md->insertItem(data,parent);

    expandItem(parent);
    setCurrentIndex(parent);
    //emit clicked(parent);
}

void CrtTreeView::insertItems(QList<CrtObject *> &lstData, const QModelIndex &parent)
{
    CrtTreeModel* md = (CrtTreeModel*)model();

    foreach(CrtObject* data,lstData)
    {
        md->insertItem(data,parent);
    }

    expandItem(parent);
    setCurrentIndex(parent);
    //emit clicked(parent);
}

void CrtTreeView::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        QModelIndex index = currentIndex();
        if(index.isValid())
        {
            QByteArray itemData;
            QDataStream dataStream(&itemData, QIODevice::WriteOnly);

            CrtObject* node = (CrtObject*)index.internalPointer();
            if (node && !node->getType().compare("device") && !dynamic_cast<CrtDevice*>(node)->isOnMap())
            {
                dataStream << reinterpret_cast<qlonglong>(node);
                QMimeData *data = new QMimeData;
                data->setData("project/items",itemData);
                QDrag* drag = new QDrag(this);
                drag->setMimeData(data);
                drag->setPixmap(QPixmap(QString(":/device/%1.bmp").arg(dynamic_cast<CrtDevice*>(node)->getDeviceType())));
                drag->exec(Qt::MoveAction);
            }
        }
    }
}

void CrtTreeView::slotUpdateItem(CrtObject *obj)
{
    Q_ASSERT(obj);
    CrtTreeModel* md = (CrtTreeModel*)model();
    QModelIndex index = md->indexFromItem(obj);
    if(index.isValid())
        update(index);
}

void CrtTreeView::slotItemDoubleClicked(QModelIndex index)
{
    if(!index.isValid())return;
    CrtObject* item = (CrtObject*)index.internalPointer();

    if(!item->getType().compare("device"))
    {
        CrtDevice* device = dynamic_cast<CrtDevice*>(item);
        if(device->isOnMap())
        {
            CrtObject* layer = CrtMaster::getInstance()->findMapObject(device->getParent()->getParent()->getID(),
                                     device->getBuildingID(),device->getLayerID());
            QModelIndex index = static_cast<CrtTreeModel*>(CrtMaster::getInstance()->getMapTreeView()->model())->indexFromItem(layer);
            if(index.isValid())
            {
                CrtMaster::getInstance()->getMapTreeView()->setCurrentIndex(index);
                CrtDeviceItem* deviceItem = device->createDeviceItem();
                CrtMaster::getInstance()->getCrtGraphicsView()->scene()->clearSelection();
                deviceItem->setSelected(true);
                CrtMaster::getInstance()->getCrtGraphicsView()->centerOn(deviceItem);
                emit sigUpdateMainWindowTab(1);
            }
        }
    }
    else if(!item->getType().compare("layer") || !item->getType().compare("building"))
    {
        emit sigUpdateMainWindowTab(1);
    }
}

