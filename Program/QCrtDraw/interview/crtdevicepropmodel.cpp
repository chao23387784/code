#include "crtdevicepropmodel.h"
#include "crtdevice.h"
#include "crtmaster.h"

CrtDevicePropModel::CrtDevicePropModel(QObject *parent):QAbstractItemModel(parent)
{
    source = NULL;
}

QModelIndex CrtDevicePropModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row,column,parent) || !source)
        return QModelIndex();

    return createIndex(row,column,source->childAt(row));
}

QModelIndex CrtDevicePropModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child);
    return QModelIndex();
}

Qt::ItemFlags CrtDevicePropModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return 0;

    return Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsEditable;
}

QVariant CrtDevicePropModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        QString value = "";
        switch(section)
        {
        case 0:
        {
            value = tr("Device ID");
        }
            break;
        case 1:
        {
            value = tr("Device Name");
        }
            break;
        case 2:
        {
            value = tr("Device Type");
        }
            break;
        }
        return value;
    }

    return QVariant();
}

QVariant CrtDevicePropModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    CrtDevice* item = static_cast<CrtDevice*>(index.internalPointer());
    if (role == Qt::DecorationRole && index.column() == 2)
    {
        QString strIcon;
        if(!item->Type().compare("device"))
        {
            strIcon = dynamic_cast<CrtDevice*>(item)->DeviceType();
            return *(CrtMaster::GetInstance()->DeviceIcon(strIcon));
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
            value = item->ID();
        }
            break;
        case 1:
        {
            value = item->Name();
        }
            break;
        case 2:
        {
            value = item->DeviceType();
        }
            break;
        }
        return value;
    }
    return QVariant();
}

bool CrtDevicePropModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role);
    if(!index.isValid())return false;

    CrtDevice* item = static_cast<CrtDevice*>(index.internalPointer());
    switch(index.column())
    {
    /*case 0:
    {
        if(value.toInt() > 0)
            item->setID(value.toInt());
    }
        break;*/
    case 1:
    {
        if(!value.toString().trimmed().isEmpty())
            item->setName(value.toString());
        else
            item->setName(QString(tr("NT-Device%1")).arg(item->ID()));
    }
        break;
    case 2:
    {
        item->setDeviceType(value.toString());
    }
        break;
    }

    return true;
}

int CrtDevicePropModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if(!source)return 0;
    return source->childCount();
}

int CrtDevicePropModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 3;
}

bool CrtDevicePropModel::load(CrtObject *obj)
{
    if(obj != NULL)
    {
        beginResetModel();
        source = dynamic_cast<CrtLoop*>(obj);
        endResetModel();
        return true;
    }
    return false;
}

void CrtDevicePropModel::unload()
{
    if(source)
    {
        beginResetModel();
        source = NULL;
        endResetModel();
    }
}
