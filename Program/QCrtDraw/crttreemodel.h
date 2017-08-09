#ifndef CRTTREEMODEL_H
#define CRTTREEMODEL_H
#include <QAbstractItemModel>
#include "crttreeitem.h"
#include "crtproject.h"

class CrtTreeModel : public QAbstractItemModel
{
public:
    CrtTreeModel(QObject *parent = 0);
    QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool load(CrtProject* proj,int type = 0);//0 project,1 map;
    CrtProject* save(int type = 0);
    //void reset(){beginResetModel();endResetModel();}
    void InsertItem(CrtTreeItem* item,const QModelIndex &parent);
    void DeleteItem(const QModelIndex &index);
    QModelIndex indexFromItem(CrtTreeItem* item);
    void unload();
private:
    CrtTreeItem* root;
};

#endif // CRTTREEMODEL_H
