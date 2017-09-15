#include "crtcontrollerpropdelegate.h"
#include <QLineEdit>
#include <QComboBox>
#include <QValidator>
#include "crtmaster.h"

CrtControllerPropDelegate::CrtControllerPropDelegate(QObject *parent):QStyledItemDelegate(parent)
{

}

QWidget *CrtControllerPropDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);

    switch(index.column())
    {
    /*case 0://controller id
    {
        QLineEdit* editControllerID = new QLineEdit(parent);
        editControllerID->setValidator(new QIntValidator(1,999,parent));
        return editControllerID;
    }
        break;*/
    case 1://controller name
    {
        QLineEdit* editControllerName = new QLineEdit(parent);
        editControllerName->setMaxLength(256);
        connect(editControllerName,SIGNAL(textEdited(QString)),this,SIGNAL(valueChanged(QString)));
        return editControllerName;
    }
        break;
    case 2://controller netid
    {
        QLineEdit* editNetID = new QLineEdit(parent);
        editNetID->setValidator(new QIntValidator(0,999,parent));
        connect(editNetID,SIGNAL(textEdited(QString)),this,SIGNAL(valueChanged(QString)));
        return editNetID;
    }
        break;
    case 3://controller type
    {
        QComboBox* cmbControllerType = new QComboBox(parent);
        cmbControllerType->addItems(*(CrtMaster::GetInstance()->ControllerType()));
        connect(cmbControllerType,SIGNAL(activated(QString)),this,SIGNAL(valueChanged(QString)));
        return cmbControllerType;
    }
        break;
    case 4://system type
    {
        QComboBox* cmbControllerSystem = new QComboBox(parent);
        cmbControllerSystem->addItems(*(CrtMaster::GetInstance()->SystemType()));
        connect(cmbControllerSystem,SIGNAL(activated(QString)),this,SIGNAL(valueChanged(QString)));
        return cmbControllerSystem;
    }
        break;
    }

    return NULL;
}

void CrtControllerPropDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    switch(index.column())
    {
    //case 0:
    case 1:
    case 2:
    {
        QString value = index.data().toString();
        QLineEdit* ctrl = qobject_cast<QLineEdit*>(editor);
        Q_ASSERT(ctrl);
        ctrl->setText(value);
    }
        break;
    case 3:
    case 4:
    {
        QString value = index.data().toString();
        QComboBox* ctrl = qobject_cast<QComboBox*>(editor);
        Q_ASSERT(ctrl);
        int nIndex = ctrl->findText(value);
        if(nIndex == -1)
            ctrl->setCurrentText(value);
        else
            ctrl->setCurrentIndex(nIndex);
    }
        break;
    default:
        QStyledItemDelegate::setEditorData(editor,index);
    }
}

void CrtControllerPropDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    switch(index.column())
    {
    //case 0:
    case 2:
    {
        QLineEdit* ctrl = qobject_cast<QLineEdit*>(editor);
        Q_ASSERT(ctrl);
        model->setData(index,ctrl->text().trimmed().toInt());
    }
        break;
    case 1:
    {
        QLineEdit* ctrl = qobject_cast<QLineEdit*>(editor);
        Q_ASSERT(ctrl);
        model->setData(index,ctrl->text().trimmed());
    }
        break;
    case 3:
    case 4:
    {
        QComboBox* ctrl = qobject_cast<QComboBox*>(editor);
        Q_ASSERT(ctrl);
        model->setData(index,ctrl->currentText());

    }
        break;
    default:
        QStyledItemDelegate::setModelData(editor,model,index);
    }
}
