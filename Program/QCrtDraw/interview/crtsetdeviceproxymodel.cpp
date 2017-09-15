#include "crtsetdeviceproxymodel.h"
#include "crtdevice.h"

CrtSetDeviceProxyModel::CrtSetDeviceProxyModel(QObject *parent):QSortFilterProxyModel(parent)
{
    project_id = -1;
    controller_id = -1;
    loop_id = -1;
    device_type = "";
}

void CrtSetDeviceProxyModel::setFilter(QVariant filter, int type)
{
    if(type == 0)
    {
        project_id = filter.toInt();
        controller_id = -1;
        loop_id = -1;

    }else if(type == 1)
    {
        controller_id = filter.toInt();
        loop_id = -1;
    }else if(type == 2)
    {
       loop_id = filter.toInt();
    }else if(type == 3)
    {
        device_type = filter.toString();
    }
    invalidateFilter();
}

void CrtSetDeviceProxyModel::clearFilter()
{
    project_id = -1;
    controller_id = -1;
    loop_id = -1;
    device_type = "";
    invalidateFilter();
}

void CrtSetDeviceProxyModel::update()
{
    invalidateFilter();
}

bool CrtSetDeviceProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex index = sourceModel()->index(source_row, 0,
                                             source_parent);
    if(!index.isValid()) return false;

    CrtDevice* device = static_cast<CrtDevice*>(index.internalPointer());

    if((project_id == -1 || device->Parent()->Parent()->Parent()->ID() == project_id) &&
            (controller_id == -1 || device->Parent()->Parent()->ID() == controller_id) &&
            (loop_id == -1 || device->Parent()->ID() == loop_id) &&
            (device_type.isEmpty() || !device->DeviceType().compare(device_type)))
    {
        if(!device->isOnMap())
            return true;
    }

    return false;
}
