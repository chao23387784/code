#include "crtsetdevicemodel.h"
#include "crtloop.h"
#include "crtcontroller.h"
#include "crtmaster.h"
#include <QMimeData>

CrtSetDeviceModel::CrtSetDeviceModel(QObject *parent):QAbstractItemModel(parent)
{

}

QModelIndex CrtSetDeviceModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row,column,parent) || m_source.isEmpty())
        return QModelIndex();

    return createIndex(row,column,m_source.at(row));
}

QModelIndex CrtSetDeviceModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child);
    return QModelIndex();
}

Qt::ItemFlags CrtSetDeviceModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return 0;

    return Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsDragEnabled;
}

QVariant CrtSetDeviceModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        QString value = "";
        switch(section)
        {
        case 0:
        {
            value = tr("Project ID");
        }
            break;
        case 1:
        {
            value = tr("Controller ID");
        }
            break;
        case 2:
        {
            value = tr("Loop ID");
        }
            break;
        case 3:
        {
            value = tr("Device ID");
        }
            break;
        case 4:
        {
            value = tr("Device Type");
        }
            break;
        }
        return value;
    }

    return QVariant();
}

QVariant CrtSetDeviceModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    CrtDevice* item = static_cast<CrtDevice*>(index.internalPointer());
    if (role == Qt::DecorationRole && index.column() == 4)
    {
        QString strIcon;
        if(item->getType() == OT_DEVICE)
        {
            strIcon = dynamic_cast<CrtDevice*>(item)->getDeviceType();
            return *(CrtMaster::getInstance()->getDeviceIcon(strIcon));
        }
        return QVariant();
    }
    if(role == Qt::DisplayRole)
    {
        QVariant value;
        switch(index.column())
        {
        case 0:
        {
            value = item->getParent()->getParent()->getParent()->getID();
        }
            break;
        case 1:
        {
            value = item->getParent()->getParent()->getID();
        }
            break;
        case 2:
        {
            value = item->getParent()->getID();
        }
            break;
        case 3:
        {
            value = item->getID();
        }
            break;
        case 4:
        {
            value = item->getDeviceType();
        }
            break;
        }
        return value;
    }
    return QVariant();
}

//QMimeData *CrtSetDeviceModel::mimeData(const QModelIndexList &indexes) const
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

int CrtSetDeviceModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if(m_source.isEmpty())return 0;
    return m_source.count();
}

int CrtSetDeviceModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 5;
}

bool CrtSetDeviceModel::load(CrtProject *obj)
{
    m_source.clear();
    beginResetModel();
    foreach(CrtObject* controller,obj->m_lstController)
    {
        foreach(CrtObject* loop,dynamic_cast<CrtController*>(controller)->m_lstLoop)
        {
            m_source.append(dynamic_cast<CrtLoop*>(loop)->m_lstDevice);
        }
    }

    endResetModel();

    return true;
}
