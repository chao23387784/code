#include "crttreeview.h"
#include "crttreemodel.h"
#include "crtmaster.h"

CrtTreeView::CrtTreeView(QWidget *parent) : QTreeView(parent)
{
    setDragDropMode(QAbstractItemView::DragOnly);
    setUniformRowHeights(true);
    setExpandsOnDoubleClick(false);
    setEditTriggers(QAbstractItemView::SelectedClicked);
    connect(this,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(itemDoubleClicked(QModelIndex)));
}

void CrtTreeView::expandItem(const QModelIndex &index)
{
    if(!index.isValid())return;
    CrtTreeModel* md = (CrtTreeModel*)model();
    CrtObject* item = (CrtObject*)index.internalPointer();

    while(item)
    {
        expand(md->indexFromItem(item));
        item = item->Parent();
    }
}

void CrtTreeView::deleteItem(const QModelIndex &index)
{
    CrtObject* item = (CrtObject*)index.internalPointer();
    CrtObject* parent = (CrtObject*)item->Parent();
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

void CrtTreeView::updateItem(CrtObject *obj)
{
    Q_ASSERT(obj);
    CrtTreeModel* md = (CrtTreeModel*)model();
    QModelIndex index = md->indexFromItem(obj);
    if(index.isValid())
        update(index);
}

void CrtTreeView::itemDoubleClicked(QModelIndex index)
{
    if(!index.isValid())return;
    CrtObject* item = (CrtObject*)index.internalPointer();

    if(!item->Type().compare("device"))
    {
        CrtDevice* device = dynamic_cast<CrtDevice*>(item);
        if(device->isOnMap())
        {
            CrtObject* layer = CrtMaster::GetInstance()->findMapObject(device->Parent()->Parent()->ID(),
                                     device->BuildingID(),device->LayerID());
            QModelIndex index = static_cast<CrtTreeModel*>(CrtMaster::GetInstance()->MapTreeView()->model())->indexFromItem(layer);
            if(index.isValid())
            {
                CrtMaster::GetInstance()->MapTreeView()->setCurrentIndex(index);
                CrtDeviceItem* deviceItem = device->createDeviceItem();
                CrtMaster::GetInstance()->getCrtGraphicsView()->scene()->clearSelection();
                deviceItem->setSelected(true);
                CrtMaster::GetInstance()->getCrtGraphicsView()->centerOn(deviceItem);
                emit updateMainWindowTab(1);
            }
        }
    }
    else if(!item->Type().compare("layer") || !item->Type().compare("building"))
    {
        emit updateMainWindowTab(1);
    }
}

