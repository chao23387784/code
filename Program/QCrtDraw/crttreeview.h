#ifndef CRTTREEVIEW_H
#define CRTTREEVIEW_H

#include <QTreeView>
#include "crttreeitem.h"

class CrtTreeView : public QTreeView
{
public:
    explicit CrtTreeView(QWidget *parent = 0);
    void expandItem(const QModelIndex& index);
    void deleteItem(const QModelIndex& index);
    void insertItem(CrtTreeItem* item,const QModelIndex &parent);
};

#endif // CRTTREEVIEW_H
