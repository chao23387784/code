#ifndef CRTDEVICEPROPDELEGATE_H
#define CRTDEVICEPROPDELEGATE_H
#include <QStyledItemDelegate>

class CrtDevicePropDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CrtDevicePropDelegate(QObject *parent = 0);
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
signals:
    void valueChanged(QString value) const;
};

#endif // CRTDEVICEPROPDELEGATE_H
