#include "crtsetdevicedlg.h"
#include <QLayout>
#include <QGridLayout>
#include <QLabel>
#include <QDir>
#include <QHeaderView>
#include "crtmaster.h"
#include "crtgraphicsview.h"

CrtSetDeviceDlg::CrtSetDeviceDlg(QWidget *parent, Qt::WindowFlags f):QWidget(parent,f)
{
    setWindowTitle(tr("Devices"));
    setAttribute(Qt::WA_DeleteOnClose);

    QLabel* lbProject = new QLabel(tr("Project"),this);
    QLabel* lbController = new QLabel(tr("Controller"),this);
    QLabel* lbLoop = new QLabel(tr("Loop"),this);
    QLabel* lbDeviceType = new QLabel(tr("Device Type"),this);

    m_cmbProject = new QComboBox(this);  
    //cmbProject->addItem(tr("All"));
    m_cmbController = new QComboBox(this);
    //cmbController->addItem(tr("All"));
    m_cmbLoop = new QComboBox(this);
    //cmbLoop->addItem(tr("All"));
    m_cmbDeviceType = new QComboBox(this);
    m_cmbDeviceType->addItem(tr("All"));


    QDir dir(":/device");//change to local device dir
    dir.setFilter(QDir::Files | QDir::NoSymLinks);

    QFileInfoList lst = dir.entryInfoList();

    for(int i=0;i<lst.size();i++)
    {
        QFileInfo fi = lst.at(i);
        if(fi.suffix() == "bmp")
        {
            m_cmbDeviceType->addItem(QIcon(fi.filePath()),fi.baseName(),fi.filePath());
        }
    }


    m_DeviceTable = new CrtSetDeviceView(this);
    //m_DeviceTable->setDragDropMode(QAbstractItemView::DragOnly);
    m_model = new CrtSetDeviceModel(this);
    m_proxymodel = new CrtSetDeviceProxyModel(this);
    m_proxymodel->setSourceModel(m_model);
    m_DeviceTable->setModel(m_proxymodel);
    m_DeviceTable->verticalHeader()->setVisible(false);
    m_DeviceTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    m_DeviceTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    m_DeviceTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    m_DeviceTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    m_DeviceTable->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);

    QGridLayout* layoutTop = new QGridLayout(this);
    layoutTop->addWidget(lbProject,0,0);
    layoutTop->addWidget(m_cmbProject,0,1);
    layoutTop->addWidget(lbController,0,2);
    layoutTop->addWidget(m_cmbController,0,3);

    layoutTop->addWidget(lbLoop,1,0);
    layoutTop->addWidget(m_cmbLoop,1,1);
    layoutTop->addWidget(lbDeviceType,1,2);
    layoutTop->addWidget(m_cmbDeviceType,1,3);

    QWidget* widget = new QWidget(this);
    widget->setLayout(layoutTop);

    QVBoxLayout* layoutMain = new QVBoxLayout(this);
    layoutMain->addWidget(widget);
    layoutMain->addWidget(m_DeviceTable);

    setLayout(layoutMain);
    //setFixedSize(600,600);
    //setFixedWidth(600);
}

CrtSetDeviceDlg::~CrtSetDeviceDlg()
{
    //disconnect(CrtMaster::GetInstance()->getCrtGraphicsView(),SIGNAL(dragDone()),this,SLOT(OnDragDone()));
}

void CrtSetDeviceDlg::loadData()
{
    m_cmbProject->clear();
    m_cmbProject->addItem(tr("All"));
    m_cmbController->clear();
    m_cmbController->addItem(tr("All"));
    m_cmbLoop->clear();
    m_cmbLoop->addItem(tr("All"));
    m_cmbProject->addItem(QString::number(CrtMaster::getInstance()->getProject()->getID()));
    m_model->load(CrtMaster::getInstance()->getProject());
    connect(CrtMaster::getInstance()->getCrtGraphicsView(),SIGNAL(sigDragDone()),this,SLOT(slotDragDone()));
    connect(m_cmbProject,SIGNAL(currentIndexChanged(int)),this,SLOT(slotComboItemSelected()));
    connect(m_cmbController,SIGNAL(currentIndexChanged(int)),this,SLOT(slotComboItemSelected()));
    connect(m_cmbLoop,SIGNAL(currentIndexChanged(int)),this,SLOT(slotComboItemSelected()));
    connect(m_cmbDeviceType,SIGNAL(currentIndexChanged(int)),this,SLOT(slotComboItemSelected()));
}

void CrtSetDeviceDlg::releaseData()
{
    disconnect(CrtMaster::getInstance()->getCrtGraphicsView(),SIGNAL(sigDragDone()),this,SLOT(slotDragDone()));
    disconnect(m_cmbProject,SIGNAL(currentIndexChanged(int)),this,SLOT(slotComboItemSelected()));
    disconnect(m_cmbController,SIGNAL(currentIndexChanged(int)),this,SLOT(slotComboItemSelected()));
    disconnect(m_cmbLoop,SIGNAL(currentIndexChanged(int)),this,SLOT(slotComboItemSelected()));
    disconnect(m_cmbDeviceType,SIGNAL(currentIndexChanged(int)),this,SLOT(slotComboItemSelected()));
    m_cmbProject->clear();
    m_cmbController->clear();
    m_cmbLoop->clear();
}

CrtObject *CrtSetDeviceDlg::getCurrentObject()
{
    QModelIndex index = m_DeviceTable->currentIndex();
    if(index.isValid())
    {
        int proj_id = m_proxymodel->data(m_proxymodel->index(index.row(),0)).toInt();
        int controller_id = m_proxymodel->data(m_proxymodel->index(index.row(),1)).toInt();
        int loop_id = m_proxymodel->data(m_proxymodel->index(index.row(),2)).toInt();
        int device_id = m_proxymodel->data(m_proxymodel->index(index.row(),3)).toInt();
        return CrtMaster::getInstance()->findProjectObject(proj_id,controller_id,loop_id,device_id);

    }
    return NULL;
}

void CrtSetDeviceDlg::slotComboItemSelected()
{
    if(sender() == m_cmbProject)
    {
        m_cmbController->clear();
        m_cmbLoop->clear();

        m_cmbController->addItem(tr("All"));
        m_cmbLoop->addItem(tr("All"));
        if(m_cmbProject->currentText().compare(tr("All")))
        {
            foreach(CrtObject* obj,CrtMaster::getInstance()->getProject()->m_lstController)
            {
                m_cmbController->addItem(QString::number(obj->getID()));
            }
        }
        m_proxymodel->setFilter(-1,0);
    }else if(sender() == m_cmbController)
    {
        m_cmbLoop->clear();
        m_cmbLoop->addItem(tr("All"));
        if(m_cmbController->currentText().compare(tr("All")))
        {
            CrtObject* controller = CrtMaster::getInstance()->findProjectObject(CrtMaster::getInstance()->getProject()->getID(),m_cmbController->currentText().toInt());
            if(controller)
            {
                foreach(CrtObject* obj,dynamic_cast<CrtController*>(controller)->m_lstLoop)
                {
                    m_cmbLoop->addItem(QString::number(obj->getID()));
                }
            }

            m_proxymodel->setFilter(m_cmbController->currentText().toInt(),1);
        }else
        {
            m_proxymodel->setFilter(-1,0);
        }

    }else if(sender() == m_cmbLoop)
    {
        if(m_cmbLoop->currentText().compare(tr("All")))
        {
            m_proxymodel->setFilter(m_cmbLoop->currentText().toInt(),2);
        }else
        {
            if(m_cmbController->currentText().compare(tr("All")))
            {
                m_proxymodel->setFilter(m_cmbController->currentText().toInt(),1);
            }else
                m_proxymodel->setFilter(-1,0);
        }
    }else if(sender() == m_cmbDeviceType)
    {
        if(m_cmbDeviceType->currentText().compare(tr("All")))
            m_proxymodel->setFilter(m_cmbDeviceType->currentText(),3);
        else
            m_proxymodel->setFilter("",3);
    }
}

void CrtSetDeviceDlg::slotDragDone()
{
    QModelIndex index = m_DeviceTable->currentIndex();
    m_proxymodel->update();
    if(m_DeviceTable->model()->rowCount() <= index.row())
    {
        if(m_DeviceTable->model()->rowCount() > 0)
            m_DeviceTable->selectRow(m_DeviceTable->model()->rowCount()-1);
    }else
    {
        m_DeviceTable->selectRow(index.row());
    }
}
