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
