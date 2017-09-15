#include "crtlooppropmodel.h"
#include "crtloop.h"

CrtLoopPropModel::CrtLoopPropModel(QObject *parent):QAbstractItemModel(parent)
{
    source = NULL;
}

QModelIndex CrtLoopPropModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row,column,parent) || !source)
        return QModelIndex();

    return createIndex(row,column,source->childAt(row));
}

QModelIndex CrtLoopPropModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child);
    return QModelIndex();
}

Qt::ItemFlags CrtLoopPropModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return 0;

    return Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsEditable;
}

QVariant CrtLoopPropModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        if(section == 0)
            return QString(tr("Loop ID"));
        else if(section == 1)
            return QString(tr("Loop Name"));
    }

    return QVariant();
}

QVariant CrtLoopPropModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || role != Qt::DisplayRole)
        return QVariant();
    CrtLoop* item = static_cast<CrtLoop*>(index.internalPointer());
    if(index.column() == 0)
        return item->ID();
    else if(index.column() == 1)
        return item->Name();

    return QVariant();
}

bool CrtLoopPropModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role);
    if(!index.isValid())return false;

    CrtLoop* item = static_cast<CrtLoop*>(index.internalPointer());
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
            item->setName(QString(tr("NT-Loop%1")).arg(item->ID()));
    }
        break;
    }

    return true;
}

int CrtLoopPropModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if(!source)return 0;
    return source->childCount();
}

int CrtLoopPropModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

bool CrtLoopPropModel::load(CrtObject *obj)
{
    if(obj != NULL)
    {
        beginResetModel();
        source = dynamic_cast<CrtController*>(obj);
        endResetModel();
        return true;
    }
    return false;
}

void CrtLoopPropModel::unload()
{
    if(source)
    {
        beginResetModel();
        source = NULL;
        endResetModel();
    }
}
