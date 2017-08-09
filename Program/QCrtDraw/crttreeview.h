#ifndef CRTTREEVIEW_H
#define CRTTREEVIEW_H

#include <QTreeView>

class CrtTreeView : public QTreeView
{
public:
    explicit CrtTreeView(QWidget *parent = 0);
    void expandItem(const QModelIndex& index);
};

#endif // CRTTREEVIEW_H
