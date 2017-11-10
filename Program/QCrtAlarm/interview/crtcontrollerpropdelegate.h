#ifndef CRTCONTROLLERPROPDELEGATE_H
#define CRTCONTROLLERPROPDELEGATE_H
#include <QStyledItemDelegate>

class CrtControllerPropDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CrtControllerPropDelegate(QObject *parent = 0);
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const;
signals:
    void sigValueChanged(QString value) const;
};

#endif // CRTCONTROLLERPROPDELEGATE_H
