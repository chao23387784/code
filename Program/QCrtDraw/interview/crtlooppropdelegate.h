#ifndef CRTLOOPPROPDELEGATE_H
#define CRTLOOPPROPDELEGATE_H
#include <QStyledItemDelegate>

class CrtLoopPropDelegate : public QStyledItemDelegate
{
public:
    explicit CrtLoopPropDelegate(QObject *parent = 0);
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const;
signals:
    void sigValueChanged(QString value) const;
};

#endif // CRTLOOPPROPDELEGATE_H
