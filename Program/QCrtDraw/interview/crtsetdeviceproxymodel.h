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
    int m_nProject_ID;
    int m_nController_ID;
    int m_nLoop_ID;
    QString m_strDevType;
};

#endif // CRTSETDEVICEPROXYMODEL_H
