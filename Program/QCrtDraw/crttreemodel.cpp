#include "crttreemodel.h"

CrtTreeModel::CrtTreeModel(QObject *parent):QAbstractItemModel(parent)
{

}

QModelIndex CrtTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row,column,parent))
        return QModelIndex();

    CrtTreeItem *parentItem;
    if(!parent.isValid())
    {
        return createIndex(0,0,root);
    }else
    {
        parentItem=static_cast<CrtTreeItem*>(parent.internalPointer());
    }

    CrtTreeItem *childItem=parentItem->childAt(row);
    if(childItem)
        return createIndex(row,column,childItem);
    else
        return QModelIndex();
}

QModelIndex CrtTreeModel::parent(const QModelIndex &child) const
{
    if(!child.isValid())
        return QModelIndex();

    CrtTreeItem *childItem=static_cast<CrtTreeItem*>(child.internalPointer());
    CrtTreeItem *parentItem=childItem->Parent();

    if(parentItem==NULL)
        return QModelIndex();

    return createIndex(parentItem->Row(),0,parentItem);
}

Qt::ItemFlags CrtTreeModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return 0;

    return Qt::ItemIsEnabled|Qt::ItemIsSelectable;
}

int CrtTreeModel::rowCount(const QModelIndex &parent) const
{
    CrtTreeItem *parentItem;

    if(!parent.isValid())
        return 1;
    else
        parentItem=static_cast<CrtTreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int CrtTreeModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant CrtTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole)
    {
        CrtTreeItem *item=static_cast<CrtTreeItem*>(index.internalPointer());
        return item->Data()->Name();
    }
    return QVariant();
}

bool CrtTreeModel::load(CrtProject *proj, int type)
{
    if(proj != NULL)
    {
        root = new CrtTreeItem();
        root->setParent(NULL);
        root->setColumn(0);
        root->setRow(1);
        root->setData(proj);
        root->load(proj,type);
        //beginResetModel();
        //endResetModel();
        return true;
    }
    return false;
}

CrtProject *CrtTreeModel::save(int type)
{
    return NULL;
}
