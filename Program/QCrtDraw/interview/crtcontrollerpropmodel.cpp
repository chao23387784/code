#include "crtcontrollerpropmodel.h"
#include "crtcontroller.h"

CrtControllerPropModel::CrtControllerPropModel(QObject *parent):QAbstractItemModel(parent)
{
    source = NULL;
}

QModelIndex CrtControllerPropModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row,column,parent) || !source)
        return QModelIndex();

    return createIndex(row,column,source->childAt(row));
}

QModelIndex CrtControllerPropModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child);
    return QModelIndex();
}

Qt::ItemFlags CrtControllerPropModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return 0;

    return Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsEditable;
}

QVariant CrtControllerPropModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        QString value = "";
        switch(section)
        {
        case 0:
        {
            value = tr("Controller ID");
        }
            break;
        case 1:
        {
            value = tr("Controller Name");
        }
            break;
        case 2:
        {
            value = tr("NetID");
        }
            break;
        case 3:
        {
            value = tr("Controller Type");
        }
            break;
        case 4:
        {
            value = tr("System Type");
        }
            break;
        }
        return value;
    }

    return QVariant();
}

QVariant CrtControllerPropModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || role != Qt::DisplayRole)
        return QVariant();
    CrtController* item = static_cast<CrtController*>(index.internalPointer());
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
        value = item->NetID();
    }
        break;
    case 3:
    {
        value = item->ControllerType();
    }
        break;
    case 4:
    {
        value = item->SystemType();
    }
        break;
    }
    return value;
}

bool CrtControllerPropModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role);
    if(!index.isValid())return false;

    CrtController* item = static_cast<CrtController*>(index.internalPointer());
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
            item->setName(QString(tr("NT-Controller%1")).arg(item->ID()));
    }
        break;
    case 2:
    {
        if(value.toInt() > 0)
            item->setNetID(value.toInt());
        else
            item->setNetID(0);
    }
        break;
    case 3:
    {
        item->setControllerType(value.toString());
    }
        break;
    case 4:
    {
        item->setSystemType(value.toString());
    }
        break;
    }

    return true;
}

int CrtControllerPropModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if(!source)return 0;
    return source->childCount();
}

int CrtControllerPropModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 5;
}

bool CrtControllerPropModel::load(CrtObject *obj)
{
    if(obj != NULL)
    {
        beginResetModel();
        source = dynamic_cast<CrtProject*>(obj);
        endResetModel();
        return true;
    }
    return false;
}

void CrtControllerPropModel::unload()
{
    if(source)
    {
        beginResetModel();
        source = NULL;
        endResetModel();
    }
}
