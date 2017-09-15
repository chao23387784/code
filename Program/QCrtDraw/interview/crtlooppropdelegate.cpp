#include "crtlooppropdelegate.h"
#include <QLineEdit>
#include <QComboBox>

CrtLoopPropDelegate::CrtLoopPropDelegate(QObject *parent):QStyledItemDelegate(parent)
{

}

QWidget *CrtLoopPropDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);

    switch(index.column())
    {
    /*case 0://loop id
    {
        QLineEdit* editLoopID = new QLineEdit(parent);
        editLoopID->setValidator(new QIntValidator(1,999,parent));
        return editLoopID;
    }
        break;*/
    case 1://loop name
    {
        QLineEdit* editLoopName = new QLineEdit(parent);
        editLoopName->setMaxLength(256);
        connect(editLoopName,SIGNAL(textEdited(QString)),this,SIGNAL(valueChanged(QString)));
        return editLoopName;
    }
        break;
    }

    return NULL;
}

void CrtLoopPropDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    switch(index.column())
    {
    //case 0:
    case 1:
    {
        QString value = index.data().toString();
        QLineEdit* ctrl = qobject_cast<QLineEdit*>(editor);
        Q_ASSERT(ctrl);
        ctrl->setText(value);
    }
        break;
    default:
        QStyledItemDelegate::setEditorData(editor,index);
    }
}

void CrtLoopPropDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    switch(index.column())
    {
    /*case 0:
    {
        QLineEdit* ctrl = qobject_cast<QLineEdit*>(editor);
        Q_ASSERT(ctrl);
        model->setData(index,ctrl->text().trimmed().toInt());
    }
        break;*/
    case 1:
    {
        QLineEdit* ctrl = qobject_cast<QLineEdit*>(editor);
        Q_ASSERT(ctrl);
        model->setData(index,ctrl->text().trimmed());
    }
        break;
    default:
        QStyledItemDelegate::setModelData(editor,model,index);
    }
}
