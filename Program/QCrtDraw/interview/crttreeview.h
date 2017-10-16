#ifndef CRTTREEVIEW_H
#define CRTTREEVIEW_H

#include <QTreeView>
#include "crtobject.h"

class CrtTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit CrtTreeView(QWidget *parent = 0);
    void expandItem(const QModelIndex& index);
    void deleteItem(const QModelIndex& index);
    void insertItem(CrtObject* data,const QModelIndex &parent);
    void insertItems(QList<CrtObject*>& lstData,const QModelIndex &parent);
signals:
    void sigUpdateMainWindowTab(int index);
protected:
    void mouseMoveEvent(QMouseEvent *event);
public slots:
    void slotUpdateItem(CrtObject* obj);
private slots:
    void slotItemDoubleClicked(QModelIndex index);
};

#endif // CRTTREEVIEW_H
