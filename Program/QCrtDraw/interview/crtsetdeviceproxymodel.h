#ifndef CRTSETDEVICEPROXYMODEL_H
#define CRTSETDEVICEPROXYMODEL_H
#include <QSortFilterProxyModel>

class CrtSetDeviceProxyModel : public QSortFilterProxyModel
{
public:
    explicit CrtSetDeviceProxyModel(QObject *parent = 0);
    void setFilter(QVariant filter,int type);
    void clearFilter();
    void update();
protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
private:
    int project_id;
    int controller_id;
    int loop_id;
    QString device_type;
};

#endif // CRTSETDEVICEPROXYMODEL_H
