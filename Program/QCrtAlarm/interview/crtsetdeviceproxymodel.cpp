#include "crtsetdeviceproxymodel.h"
#include "crtdevice.h"

CrtSetDeviceProxyModel::CrtSetDeviceProxyModel(QObject *parent):QSortFilterProxyModel(parent)
{
    m_nProject_ID = -1;
    m_nController_ID = -1;
    m_nLoop_ID = -1;
    m_strDevType = "";
}

void CrtSetDeviceProxyModel::setFilter(QVariant filter, int type)
{
    if(type == 0)
    {
        m_nProject_ID = filter.toInt();
        m_nController_ID = -1;
        m_nLoop_ID = -1;

    }else if(type == 1)
    {
        m_nController_ID = filter.toInt();
        m_nLoop_ID = -1;
    }else if(type == 2)
    {
       m_nLoop_ID = filter.toInt();
    }else if(type == 3)
    {
        m_strDevType = filter.toString();
    }
    invalidateFilter();
}

void CrtSetDeviceProxyModel::clearFilter()
{
    m_nProject_ID = -1;
    m_nController_ID = -1;
    m_nLoop_ID = -1;
    m_strDevType = "";
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

    if((m_nProject_ID == -1 || device->getParent()->getParent()->getParent()->getID() == m_nProject_ID) &&
            (m_nController_ID == -1 || device->getParent()->getParent()->getID() == m_nController_ID) &&
            (m_nLoop_ID == -1 || device->getParent()->getID() == m_nLoop_ID) &&
            (m_strDevType.isEmpty() || !device->getDeviceType().compare(m_strDevType)))
    {
        if(!device->isOnMap())
            return true;
    }

    return false;
}
