#ifndef CRTSETDEVICEMODEL_H
#define CRTSETDEVICEMODEL_H
#include <QAbstractItemModel>
#include <QList>
#include "crtdevice.h"
#include "crtproject.h"

class CrtSetDeviceModel : public QAbstractItemModel
{
public:
    explicit CrtSetDeviceModel(QObject *parent = 0);
    QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                                    int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    //bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    QMimeData* mimeData(const QModelIndexList &indexes) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    bool load(CrtProject* obj);
    //void unload();
private:
    QList<CrtObject*> source;
};

#endif // CRTSETDEVICEMODEL_H
