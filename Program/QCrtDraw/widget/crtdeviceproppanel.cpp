#include "crtdeviceproppanel.h"
#include <QLayout>
#include <QLabel>
#include <QTableWidget>
#include <QDir>
#include <QFileInfo>
#include <QValidator>
#include "crtmaster.h"

CrtDevicePropPanel::CrtDevicePropPanel(QWidget *parent) : QWidget(parent)
{
    QLabel* labID = new QLabel(tr("Device ID:"),this);
    editDeviceID = new QLineEdit(this);
    editDeviceID->setReadOnly(true);
    //editDeviceID->setValidator(new QIntValidator(1,999,this));
    QLabel* labName = new QLabel(tr("Device Name:"),this);
    editDeviceName = new QLineEdit(this);
    editDeviceName->setMaxLength(256);
    QLabel* labType = new QLabel(tr("Device Type:"),this);
    cmbDevTypeList = new QComboBox(this);
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
    btnSet = new QPushButton(tr("set"),this);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(labID);
    layout->addWidget(editDeviceID);
    layout->addWidget(labName);
    layout->addWidget(editDeviceName);
    layout->addWidget(labType);
    layout->addWidget(cmbDevTypeList);
    layout->addWidget(btnSet);

    layout->setStretchFactor(labID,1);
    layout->setStretchFactor(editDeviceID,3);
    layout->setStretchFactor(labName,1);
    layout->setStretchFactor(editDeviceName,3);
    layout->setStretchFactor(labType,1);
    layout->setStretchFactor(cmbDevTypeList,3);
    layout->setStretchFactor(btnSet,1);

    QWidget* container = new QWidget(this);
    container->setLayout(layout);

    QVBoxLayout* layoutMain = new QVBoxLayout(this);
    layoutMain->addWidget(container);
    QTableWidget* frame = new QTableWidget(this);
    layoutMain->addWidget(frame);

    setLayout(layoutMain);

    source = NULL;

    connect(btnSet,SIGNAL(clicked(bool)),this,SLOT(onSet()));
}

void CrtDevicePropPanel::initPanel(CrtObject *obj)
{
    if(obj->Type().compare("device"))return;

    source = dynamic_cast<CrtDevice*>(obj);

    editDeviceID->setText(QString("%1").arg(source->ID()));
    editDeviceName->setText(source->Name());

    int nIndex = cmbDevTypeList->findText(source->DeviceType());
    nIndex == -1 ? cmbDevTypeList->setCurrentText(source->DeviceType()) :
                   cmbDevTypeList->setCurrentIndex(nIndex);
}

void CrtDevicePropPanel::onSet()
{
    if(!source)return;

    /*if(!editDeviceID->text().trimmed().isEmpty())
        source->setID(editDeviceID->text().trimmed().toInt());*/
    if(!editDeviceName->text().trimmed().isEmpty())
        source->setName(editDeviceName->text().trimmed());
    else
        source->setName(QString(tr("NT-Device%1")).arg(source->ID()));

    source->setDeviceType(cmbDevTypeList->currentText());

    CrtMaster::GetInstance()->ProjectTreeView()->updateItem(source);
}

