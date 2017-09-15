#include "crtsetdevicedlg.h"
#include <QLayout>
#include <QGridLayout>
#include <QLabel>
#include <QDir>
#include "crtmaster.h"
#include "crtgraphicsview.h"

CrtSetDeviceDlg::CrtSetDeviceDlg(QWidget *parent, Qt::WindowFlags f):QDialog(parent,f)
{
    setWindowTitle(tr("Devices"));
    setAttribute(Qt::WA_DeleteOnClose);

    QLabel* lbProject = new QLabel(tr("Project"),this);
    QLabel* lbController = new QLabel(tr("Controller"),this);
    QLabel* lbLoop = new QLabel(tr("Loop"),this);
    QLabel* lbDeviceType = new QLabel(tr("Device Type"),this);

    cmbProject = new QComboBox(this);  
    cmbProject->addItem(tr("All"));
    cmbProject->addItem(QString::number(CrtMaster::GetInstance()->Project()->ID()));
    cmbController = new QComboBox(this);
    cmbController->addItem(tr("All"));
    cmbLoop = new QComboBox(this);
    cmbLoop->addItem(tr("All"));
    cmbDeviceType = new QComboBox(this);
    cmbDeviceType->addItem(tr("All"));


    QDir dir(":/device");//change to local device dir
    dir.setFilter(QDir::Files | QDir::NoSymLinks);

    QFileInfoList lst = dir.entryInfoList();

    for(int i=0;i<lst.size();i++)
    {
        QFileInfo fi = lst.at(i);
        if(fi.suffix() == "bmp")
        {
            cmbDeviceType->addItem(QIcon(fi.filePath()),fi.baseName(),fi.filePath());
        }
    }


    DeviceTable = new QTableView(this);
    DeviceTable->setDragDropMode(QAbstractItemView::DragOnly);
    DeviceTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    model = new CrtSetDeviceModel(this);
    model->load(CrtMaster::GetInstance()->Project());
    proxymodel = new CrtSetDeviceProxyModel(this);
    proxymodel->setSourceModel(model);
    DeviceTable->setModel(proxymodel);

    QGridLayout* layoutTop = new QGridLayout(this);
    layoutTop->addWidget(lbProject,0,0);
    layoutTop->addWidget(cmbProject,0,1);
    layoutTop->addWidget(lbController,0,2);
    layoutTop->addWidget(cmbController,0,3);

    layoutTop->addWidget(lbLoop,1,0);
    layoutTop->addWidget(cmbLoop,1,1);
    layoutTop->addWidget(lbDeviceType,1,2);
    layoutTop->addWidget(cmbDeviceType,1,3);

    QWidget* widget = new QWidget(this);
    widget->setLayout(layoutTop);

    QVBoxLayout* layoutMain = new QVBoxLayout(this);
    layoutMain->addWidget(widget);
    layoutMain->addWidget(DeviceTable);

    setLayout(layoutMain);
    setFixedSize(600,600);

    connect(cmbProject,SIGNAL(currentIndexChanged(int)),this,SLOT(OnComboItemSelected()));
    connect(cmbController,SIGNAL(currentIndexChanged(int)),this,SLOT(OnComboItemSelected()));
    connect(cmbLoop,SIGNAL(currentIndexChanged(int)),this,SLOT(OnComboItemSelected()));
    connect(cmbDeviceType,SIGNAL(currentIndexChanged(int)),this,SLOT(OnComboItemSelected()));
    connect(CrtMaster::GetInstance()->getCrtGraphicsView(),SIGNAL(dragDone()),this,SLOT(OnDragDone()));
}

CrtSetDeviceDlg::~CrtSetDeviceDlg()
{
    disconnect(CrtMaster::GetInstance()->getCrtGraphicsView(),SIGNAL(dragDone()),this,SLOT(OnDragDone()));
}

void CrtSetDeviceDlg::OnComboItemSelected()
{
    if(sender() == cmbProject)
    {
        cmbController->clear();
        cmbLoop->clear();

        cmbController->addItem(tr("All"));
        cmbLoop->addItem(tr("All"));
        if(cmbProject->currentText().compare(tr("All")))
        {
            foreach(CrtObject* obj,CrtMaster::GetInstance()->Project()->m_lstController)
            {
                cmbController->addItem(QString::number(obj->ID()));
            }
        }
        proxymodel->setFilter(-1,0);
    }else if(sender() == cmbController)
    {
        cmbLoop->clear();
        cmbLoop->addItem(tr("All"));
        if(cmbController->currentText().compare(tr("All")))
        {
            CrtObject* controller = CrtMaster::GetInstance()->findProjectObject(CrtMaster::GetInstance()->Project()->ID(),cmbController->currentText().toInt());
            if(controller)
            {
                foreach(CrtObject* obj,dynamic_cast<CrtController*>(controller)->m_lstLoop)
                {
                    cmbLoop->addItem(QString::number(obj->ID()));
                }
            }

            proxymodel->setFilter(cmbController->currentText().toInt(),1);
        }else
        {
            proxymodel->setFilter(-1,0);
        }

    }else if(sender() == cmbLoop)
    {
        if(cmbLoop->currentText().compare(tr("All")))
        {
            proxymodel->setFilter(cmbLoop->currentText().toInt(),2);
        }else
        {
            if(cmbController->currentText().compare(tr("All")))
            {
                proxymodel->setFilter(cmbController->currentText().toInt(),1);
            }else
                proxymodel->setFilter(-1,0);
        }
    }else if(sender() == cmbDeviceType)
    {
        if(cmbDeviceType->currentText().compare(tr("All")))
            proxymodel->setFilter(cmbDeviceType->currentText(),3);
        else
            proxymodel->setFilter("",3);
    }
}

void CrtSetDeviceDlg::OnDragDone()
{
    proxymodel->update();
}
