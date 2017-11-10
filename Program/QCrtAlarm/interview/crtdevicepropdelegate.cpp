#include "crtdevicepropdelegate.h"
#include <QComboBox>
#include <QDir>
#include <QFileInfo>
#include <QLineEdit>

CrtDevicePropDelegate::CrtDevicePropDelegate(QObject *parent):QStyledItemDelegate(parent)
{

}

QWidget *CrtDevicePropDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);

    switch(index.column())
    {
    /*case 0://device id
    {
        QLineEdit* editDeviceID = new QLineEdit(parent);
        editDeviceID->setValidator(new QIntValidator(1,999,parent));
        return editDeviceID;
    }
        break;*/
    case 1://device name
    {
        QLineEdit* editDeviceName = new QLineEdit(parent);
        editDeviceName->setMaxLength(256);
        connect(editDeviceName,SIGNAL(textEdited(QString)),this,SIGNAL(sigValueChanged(QString)));
        return editDeviceName;
    }
        break;
    case 2:
    {
        QLineEdit* editDeviceZone = new QLineEdit(parent);
        editDeviceZone->setValidator(new QIntValidator(0,999,parent));
        connect(editDeviceZone,SIGNAL(textEdited(QString)),this,SIGNAL(sigValueChanged(QString)));
        return editDeviceZone;
    }
        break;
    case 3://device type
    {
        QComboBox* cmbDevTypeList = new QComboBox(parent);
        QDir dir(":/device");//change to local device dir
        dir.setFilter(QDir::Files | QDir::NoSymLinks);

        QFileInfoList lst = dir.entryInfoList();

        for(int i=0;i<lst.size();i++)
        {
            QFileInfo fi = lst.at(i);
            if(fi.suffix() == "bmp")
            {
                cmbDevTypeList->addItem(QIcon(fi.filePath()),fi.baseName(),fi.filePath());
            }
        }
        connect(cmbDevTypeList,SIGNAL(activated(QString)),this,SIGNAL(sigValueChanged(QString)));
        return cmbDevTypeList;
    }
        break;
    case 4:
    {
        QLineEdit* editDeviceAddress = new QLineEdit(parent);
        editDeviceAddress->setMaxLength(256);
        connect(editDeviceAddress,SIGNAL(textEdited(QString)),this,SIGNAL(sigValueChanged(QString)));
        return editDeviceAddress;
    }
        break;
    }

    return NULL;
}

void CrtDevicePropDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    switch(index.column())
    {
    //case 0:
    case 1:
    case 2:
    case 4:
    {
        QString value = index.data().toString();
        QLineEdit* ctrl = qobject_cast<QLineEdit*>(editor);
        Q_ASSERT(ctrl);
        ctrl->setText(value);
    }
        break;
    case 3:
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

void CrtDevicePropDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
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
    case 4:
    {
        QLineEdit* ctrl = qobject_cast<QLineEdit*>(editor);
        Q_ASSERT(ctrl);
        model->setData(index,ctrl->text().trimmed());
    }
        break;
    case 2:
    {
        QLineEdit* ctrl = qobject_cast<QLineEdit*>(editor);
        Q_ASSERT(ctrl);
        model->setData(index,ctrl->text().trimmed().toInt());
    }
        break;
    case 3:
    {
        QComboBox* ctrl = qobject_cast<QComboBox*>(editor);
        Q_ASSERT(ctrl);
        model->setData(index,ctrl->currentText());
        //emit valueChanged(ctrl->currentText());
    }
        break;
    default:
        QStyledItemDelegate::setModelData(editor,model,index);
    }
}

void CrtDevicePropDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column() == 2)
    {
        QComboBox* combobox = static_cast<QComboBox*>(editor);
        combobox->setGeometry(option.rect);
    }
    else
        QStyledItemDelegate::updateEditorGeometry(editor,option,index);
}
