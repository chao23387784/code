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
    m_editDeviceID = new QLineEdit(this);
    m_editDeviceID->setReadOnly(true);
    //editDeviceID->setValidator(new QIntValidator(1,999,this));
    QLabel* labName = new QLabel(tr("Device Name:"),this);
    m_editDeviceName = new QLineEdit(this);
    m_editDeviceName->setMaxLength(256);
    QLabel* labType = new QLabel(tr("Device Type:"),this);
    m_cmbDevTypeList = new QComboBox(this);
    QLabel* labZone = new QLabel(tr("Device Zone:"),this);
    m_editDeviceZone = new QLineEdit(this);
    m_editDeviceZone->setValidator(new QIntValidator(0,999,this));
    QLabel* labAddress = new QLabel(tr("Device Address:"),this);
    m_editDeviceAddress = new QLineEdit(this);
    m_editDeviceAddress->setMaxLength(256);
    QDir dir(":/device");//change to local device dir
    dir.setFilter(QDir::Files | QDir::NoSymLinks);

    QFileInfoList lst = dir.entryInfoList();

    for(int i=0;i<lst.size();i++)
    {
        QFileInfo fi = lst.at(i);
        if(fi.suffix() == "bmp")
        {
            m_cmbDevTypeList->addItem(QIcon(fi.filePath()),fi.baseName(),fi.filePath());
        }
    }
    m_btnSet = new QPushButton(tr("set"),this);

    QHBoxLayout* layout1 = new QHBoxLayout(this);
    layout1->addWidget(labID);
    layout1->addWidget(m_editDeviceID);
    layout1->addWidget(labName);
    layout1->addWidget(m_editDeviceName);
    layout1->addWidget(labType);
    layout1->addWidget(m_cmbDevTypeList);


    layout1->setStretchFactor(labID,1);
    layout1->setStretchFactor(m_editDeviceID,3);
    layout1->setStretchFactor(labName,1);
    layout1->setStretchFactor(m_editDeviceName,3);
    layout1->setStretchFactor(labType,1);
    layout1->setStretchFactor(m_cmbDevTypeList,3);
    //layout1->setStretchFactor(btnSet,1);

    QWidget* container1 = new QWidget(this);
    container1->setLayout(layout1);

    QHBoxLayout* layout2 = new QHBoxLayout(this);
    layout2->addWidget(labZone);
    layout2->addWidget(m_editDeviceZone);
    layout2->addWidget(labAddress);
    layout2->addWidget(m_editDeviceAddress);
    layout2->addWidget(m_btnSet);

    layout2->setStretchFactor(labZone,1);
    layout2->setStretchFactor(m_editDeviceZone,3);
    layout2->setStretchFactor(labAddress,1);
    layout2->setStretchFactor(m_editDeviceAddress,6);
    layout2->setStretchFactor(m_btnSet,1);

    QWidget* container2 = new QWidget(this);
    container2->setLayout(layout2);

    QVBoxLayout* layoutMain = new QVBoxLayout(this);
    layoutMain->addWidget(container1);
    layoutMain->addWidget(container2);
    QTableWidget* frame = new QTableWidget(this);
    layoutMain->addWidget(frame);

    setLayout(layoutMain);

    m_source = NULL;

    connect(m_btnSet,SIGNAL(clicked(bool)),this,SLOT(slotSet()));
}

void CrtDevicePropPanel::initPanel(CrtObject *obj)
{
    if(obj->getType().compare("device"))return;

    m_source = dynamic_cast<CrtDevice*>(obj);

    m_editDeviceID->setText(QString("%1").arg(m_source->getID()));
    m_editDeviceName->setText(m_source->getName());

    int nIndex = m_cmbDevTypeList->findText(m_source->getDeviceType());
    nIndex == -1 ? m_cmbDevTypeList->setCurrentText(m_source->getDeviceType()) :
                   m_cmbDevTypeList->setCurrentIndex(nIndex);

    m_editDeviceZone->setText(QString("%1").arg(m_source->getDeviceZone()));
    m_editDeviceAddress->setText(m_source->getDeviceAddress());
}

void CrtDevicePropPanel::slotSet()
{
    if(!m_source)return;

    /*if(!editDeviceID->text().trimmed().isEmpty())
        source->setID(editDeviceID->text().trimmed().toInt());*/
    if(!m_editDeviceName->text().trimmed().isEmpty())
        m_source->setName(m_editDeviceName->text().trimmed());
    else
        m_source->setName(QString(tr("NT-Device%1")).arg(m_source->getID()));

    if(!m_editDeviceAddress->text().trimmed().isEmpty())
        m_source->setDeviceAddress(m_editDeviceAddress->text().trimmed());

    if(!m_editDeviceZone->text().trimmed().isEmpty())
    m_source->setDeviceZone(m_editDeviceZone->text().trimmed().toInt());

    m_source->setDeviceType(m_cmbDevTypeList->currentText());

    CrtMaster::getInstance()->getProjectTreeView()->slotUpdateItem(m_source);
}

