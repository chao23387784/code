#ifndef CRTTREEMODEL_H
#define CRTTREEMODEL_H
#include <QAbstractItemModel>
#include "crtproject.h"

class CrtTreeModel : public QAbstractItemModel
{
public:
    CrtTreeModel(QObject *parent = 0,int type = 0);//0 project,1 map;
    QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                                    int role = Qt::DisplayRole) const;
    //QMimeData* mimeData(const QModelIndexList &indexes) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool load(CrtProject* proj);
    CrtProject* save(int m_nType = 0);
    void insertItem(CrtObject* data,const QModelIndex &parent);
    void deleteItem(const QModelIndex &index);
    QModelIndex indexFromItem(CrtObject* item) const;
    void unload();
private:
    CrtObject* m_root;
    int m_nType;
};

#endif // CRTTREEMODEL_H
