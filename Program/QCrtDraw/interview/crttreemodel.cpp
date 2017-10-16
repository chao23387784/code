#include "crttreemodel.h"
#include "common.h"
#include <QDebug>
#include <QIcon>
#include <QMimeData>
#include "crtmaster.h"
#include <QColor>

CrtTreeModel::CrtTreeModel(QObject *parent, int type):QAbstractItemModel(parent)
{
    m_root = NULL;
    this->m_nType = type;
}

QModelIndex CrtTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row,column,parent))
        return QModelIndex();

    CrtObject *parentItem;
    if(!parent.isValid())
    {
        return createIndex(0,0,m_root);
    }else
    {
        parentItem=static_cast<CrtObject*>(parent.internalPointer());
    }

    if(!parentItem->getType().compare("layer"))
        return QModelIndex();

    CrtObject *childItem=parentItem->childAt(row,m_nType);
    if(childItem)
    {
        return createIndex(row,column,childItem);
    }
    else
    {
        return QModelIndex();
    }
}

QModelIndex CrtTreeModel::parent(const QModelIndex &child) const
{
    if(!child.isValid())
    {
        return QModelIndex();
    }

    CrtObject *childItem=static_cast<CrtObject*>(child.internalPointer());
    CrtObject *parentItem=childItem->getParent();

    if(parentItem==NULL)
        return QModelIndex();

    return indexFromItem(parentItem);
}

Qt::ItemFlags CrtTreeModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return 0;

    if(m_nType)
        return Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsEditable;
    return Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsDragEnabled;
}

QVariant CrtTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section);
    Q_UNUSED(orientation);
    Q_UNUSED(role);
    return QVariant();
}

//QMimeData *CrtTreeModel::mimeData(const QModelIndexList &indexes) const
//{
//    if (indexes.count() > 0)
//     {
//        QByteArray itemData;
//        QDataStream dataStream(&itemData, QIODevice::WriteOnly);

//        CrtObject* node = (CrtObject*)indexes.at(0).internalPointer();
//        if (node && !node->getType().compare("device") && !dynamic_cast<CrtDevice*>(node)->isOnMap())
//        {
//            dataStream << reinterpret_cast<qlonglong>(node);
//            QMimeData *data = new QMimeData;
//            data->setData("project/items",itemData);
//            return data;
//        }
//     }
//    return NULL;
//}

int CrtTreeModel::rowCount(const QModelIndex &parent) const
{
    if(m_root == NULL)return 0;

    CrtObject *parentItem;

    if(!parent.isValid())
        return 1;
    else
        parentItem=static_cast<CrtObject*>(parent.internalPointer());

    if(!parentItem->getType().compare("layer"))return 0;

    return parentItem->childCount(m_nType);
}

int CrtTreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant CrtTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (role == Qt::DecorationRole && index.column() == 0)
    {
        CrtObject* item = (CrtObject*)index.internalPointer();
        QString strIcon;
        if(!item->getType().compare("device"))
        {
            strIcon = dynamic_cast<CrtDevice*>(item)->getDeviceType();
            return *(CrtMaster::getInstance()->getDeviceIcon(strIcon));
        }
        else
        {
            strIcon = item->getType();
            return *(CrtMaster::getInstance()->getTreeIcon(strIcon));
        }
        return QVariant();
    }

    if(role == Qt::EditRole && index.column() == 0)
    {
        CrtObject* item = (CrtObject*)index.internalPointer();
        return item->getName();
    }

    if(role == Qt::ForegroundRole && index.column() == 0)
    {
        CrtObject* item = (CrtObject*)index.internalPointer();
        if(!item->getType().compare("device"))
        {
            if(dynamic_cast<CrtDevice*>(item)->isOnMap())
                return QColor(Qt::red);
            else
                return QColor(Qt::blue);
        }
        return QVariant();
    }

    if(role == Qt::DisplayRole)
    {
        CrtObject *item=static_cast<CrtObject*>(index.internalPointer());
        return item->getName();
    }
    return QVariant();
}

bool CrtTreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role);
    if(!index.isValid())return false;
    CrtObject* item = (CrtObject*)index.internalPointer();
    item->setName(value.toString());  
    if(this == CrtMaster::getInstance()->getMapTreeView()->model())
    {
            CrtMaster::getInstance()->getProjectTreeView()->slotUpdateItem(item);
    }
    return true;
}

bool CrtTreeModel::load(CrtProject *proj)
{
    if(proj != NULL)
    {
        beginResetModel();
        SAFE_DELETE(m_root);
        //root->setParent(NULL);
        m_root = proj;
        endResetModel();
        return true;
    }
    return false;
}

CrtProject *CrtTreeModel::save(int type)
{
    Q_UNUSED(type);
    return NULL;
}

void CrtTreeModel::insertItem(CrtObject *data, const QModelIndex &parent)
{
    if(parent.isValid())
    {
        beginResetModel();
        CrtObject* parentItem = (CrtObject*)parent.internalPointer();
        parentItem->addChild(data);
        data->setParent(parentItem);
        endResetModel();
    }
    else//add project
    {

    }
}

void CrtTreeModel::deleteItem(const QModelIndex &index)
{
    if(index.isValid())
    {
        beginResetModel();
        CrtObject *item = (CrtObject*)index.internalPointer();
        CrtObject *parent = item->getParent();
        if(parent)
        {
            parent->removeChild(parent->indexOf(item),m_nType);
        }
        else//delete project
        {
            //SAFE_DELETE(root);
        }
        endResetModel();
    }
}

QModelIndex CrtTreeModel::indexFromItem(CrtObject *item) const
{
    CrtObject* parent = item->getParent();
    if(!parent)
    {
        return item == m_root ? createIndex(0,0,m_root) : QModelIndex();
    }
    else
    {
        return createIndex(parent->indexOf(item),0,item);
    }

    return QModelIndex();
}

void CrtTreeModel::unload()
{
    if(m_root)
    {
        beginResetModel();
        //SAFE_DELETE(root);
        m_root = NULL;
        endResetModel();
    }
}
