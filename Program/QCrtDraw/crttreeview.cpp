#include "crttreeview.h"
#include "crttreemodel.h"
#include "crttreeitem.h"

CrtTreeView::CrtTreeView(QWidget *parent) : QTreeView(parent)
{

}

void CrtTreeView::expandItem(const QModelIndex &index)
{
    if(!index.isValid())return;
    CrtTreeModel* md = (CrtTreeModel*)model();
    CrtTreeItem* item = (CrtTreeItem*)index.internalPointer();
    while(item)
    {
        expand(md->indexFromItem(item));
        item = item->Parent();
    }
}

void CrtTreeView::deleteItem(const QModelIndex &index)
{
    CrtTreeItem* item = (CrtTreeItem*)index.internalPointer();
    CrtTreeItem* parent = (CrtTreeItem*)item->Parent();
    CrtTreeModel* md = (CrtTreeModel*)model();

    Q_ASSERT(parent);

    int row = item->Row();
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
    emit clicked(idx);
}

void CrtTreeView::insertItem(CrtTreeItem *item, const QModelIndex &parent)
{
    CrtTreeModel* md = (CrtTreeModel*)model();
    md->insertItem(item,parent);

    expandItem(parent);
    setCurrentIndex(parent);
    emit clicked(parent);
}
