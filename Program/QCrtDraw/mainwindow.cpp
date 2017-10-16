#include "mainwindow.h"
#include <QToolBar>
#include <QIcon>
#include <QPixmap>
#include <QDockWidget>
#include <QFileDialog>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QButtonGroup>
#include <QTabWidget>
#include "crtmaster.h"
#include "datamanager.h"
#include "common.h"
#include <QStyledItemDelegate>
#include <QItemSelectionModel>
#include <QInputDialog>
#include <QLayout>
#include <QStackedLayout>
#include "crtcontrollerproppanel.h"
#include "crtsetdevicedlg.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initUi();
    initConnect();
    //resize(1250, 850);
    //setMinimumSize(1250,850);
    setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow()
{

}

void MainWindow::initUi()
{
    //CrtWelcomWidget* welcom = new CrtWelcomWidget(this);
    //CrtMaster::GetInstance()->setWelcomeWidget(welcom);

    QToolBar* toolBar = new QToolBar(this);
    QToolBar* toolBarProject = new QToolBar(this);
    toolBarProject->setMinimumHeight(40);
    QToolBar* toolBarMap = new QToolBar(this);
    toolBarMap->setMinimumHeight(40);
    QToolBar* toolBarGraphics = new QToolBar(this);
    toolBarGraphics->setMinimumHeight(40);

    m_btnCreateProj = new QAction(QIcon(":/img/new.png"),tr("Create Project"),this);
    toolBar->addAction(m_btnCreateProj);
    m_btnOpenProj = new QAction(QIcon(":/img/open.png"),tr("Open Project"),this);
    toolBar->addAction(m_btnOpenProj);
    m_btnSaveProj = new QAction(QIcon(":/img/save.png"),tr("Save Project"),this);
    toolBar->addAction(m_btnSaveProj);
    m_btnCloseProj = new QAction(QIcon(":/img/close.png"),tr("Close Project"),this);
    toolBar->addAction(m_btnCloseProj);
    //toolBar->addSeparator();

    m_crtBtnAddController = new CrtTwoWayToolButton(this);
    m_crtBtnAddController->setIcon(QIcon(":/img/controlleradd.png"));
    m_crtBtnAddController->setToolTip(tr("Add Controller"));
    m_btnAddController = toolBarProject->addWidget(m_crtBtnAddController);
    m_btnDeleteController = new QAction(QIcon(":/img/controllersub.png"),tr("Delete Controller"),this);
    toolBarProject->addAction(m_btnDeleteController);

    m_crtBtnAddLoop = new CrtTwoWayToolButton(this);
    m_crtBtnAddLoop->setIcon(QIcon(":/img/addloop.png"));
    m_crtBtnAddLoop->setToolTip(tr("Add Loop"));
    m_btnAddLoop = toolBarProject->addWidget(m_crtBtnAddLoop);
    m_btnDeleteLoop = new QAction(QIcon(":/img/delloop.png"),tr("Delete Loop"),this);
    toolBarProject->addAction(m_btnDeleteLoop);

    m_crtBtnAddDevice = new CrtTwoWayToolButton(this);
    m_crtBtnAddDevice->setIcon(QIcon(":/img/adddev.png"));
    m_crtBtnAddDevice->setToolTip(tr("Add Device"));
    m_btnAddDevice = toolBarProject->addWidget(m_crtBtnAddDevice);
    m_btnDeleteDevice = new QAction(QIcon(":/img/deldev.png"),tr("Delete Device"),this);
    toolBarProject->addAction(m_btnDeleteDevice);

    m_crtBtnAddBuilding = new CrtTwoWayToolButton(this);
    m_crtBtnAddBuilding->setIcon(QIcon(":/img/addcatigory.png"));
    m_crtBtnAddBuilding->setToolTip(tr("Add Building"));
    m_btnAddBuilding = toolBarMap->addWidget(m_crtBtnAddBuilding);
    m_btnDeleteBuilding = new QAction(QIcon(":/img/delcatigory.png"),tr("Delete Building"),this);
    toolBarMap->addAction(m_btnDeleteBuilding);

    m_crtBtnAddLayer = new CrtTwoWayToolButton(this);
    m_crtBtnAddLayer->setIcon(QIcon(":/img/addlayer.png"));
    m_crtBtnAddLayer->setToolTip(tr("Add Layer"));
    m_btnAddLayer = toolBarMap->addWidget(m_crtBtnAddLayer);
    m_btnDeleteLayer = new QAction(QIcon(":/img/dellayer.png"),tr("Delete Layer"),this);
    toolBarMap->addAction(m_btnDeleteLayer);

    m_btnSetBackImage = new QAction(QIcon(":/img/map.png"),tr("Set BackImage"),this);
    m_tbPan = new QToolButton(this);
    m_tbPan->setIcon(QIcon(":/img/drag.png"));
    m_tbPan->setToolTip(tr("Drag Map"));
    m_tbPan->setCheckable(true);

    m_btnZoomin = new QAction(QIcon(":/img/zoomin.png"),tr("Zoom In"),this);
    m_btnZoomout = new QAction(QIcon(":/img/zoomout.png"),tr("Zoom Out"),this);
    toolBarGraphics->addAction(m_btnSetBackImage);
    m_btnPan = toolBarGraphics->addWidget(m_tbPan);
    toolBarGraphics->addAction(m_btnZoomin);
    toolBarGraphics->addAction(m_btnZoomout);

    m_tbSetDevice = new QToolButton(this);
    m_tbSetDevice->setIcon(QIcon(":/img/marknormalpoint.png"));
    m_tbSetDevice->setToolTip(tr("Set Device"));
    m_tbSetDevice->setCheckable(true);
    m_btnSetDevice = toolBarGraphics->addWidget(m_tbSetDevice);
    //toolBarGraphics->addAction(btnSetDevice);

    m_tbCustomSize = new QToolButton();
    m_tbCustomSize->setIcon(QIcon(":/img/customsize.png"));
    m_tbCustomSize->setToolTip(tr("Custom Size"));
    toolBarGraphics->addWidget(m_tbCustomSize);

    m_customSizeMenu = new QMenu();
    m_customSizeMenu->addAction(tr("8px"))->setData(0.25);
    m_customSizeMenu->addAction(tr("16px"))->setData(0.5);
    m_customSizeMenu->addAction(tr("32px"))->setData(1.0);
    m_customSizeMenu->addAction(tr("48px"))->setData(1.5);
    m_customSizeMenu->addAction(tr("64px"))->setData(2.0);
    m_customSizeMenu->addAction(tr("96px"))->setData(3.0);
    m_customSizeMenu->addAction(tr("128px"))->setData(4.0);

    m_tbCustomSize->setPopupMode(QToolButton::InstantPopup);
    m_tbCustomSize->setMenu(m_customSizeMenu);

    m_cmbDevList = new QComboBox();
    m_cmbDevList->setFixedWidth(180);

    QDir dir(":/device");//change to local device dir
    dir.setFilter(QDir::Files | QDir::NoSymLinks);

    QFileInfoList lst = dir.entryInfoList();

    for(int i=0;i<lst.size();i++)
    {
        QFileInfo fi = lst.at(i);
        if(fi.suffix() == "bmp")
        {
            m_cmbDevList->addItem(QIcon(fi.filePath()),fi.baseName(),fi.filePath());
        }
    }

    m_actDevList = toolBarProject->addWidget(m_cmbDevList);

    m_cmbCtrlList = new QComboBox(this);

    m_cmbCtrlList->addItems(*(CrtMaster::getInstance()->getControllerType()));

    m_actCtrlList = toolBarProject->addWidget(m_cmbCtrlList);

    addToolBar(toolBar);

    slotUpdateToolbarProjectState(0);
    slotUpdateToolbarMapState(0);

    m_panelProject = new QDockWidget(this);
    m_panelProject->setFeatures(QDockWidget::DockWidgetMovable);
    m_panelProject->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    QWidget* windProject = new QWidget(this);
    m_panelProject->setWidget(windProject);

    m_treeProject = new CrtTreeView(this);
    m_treeProject->setHeaderHidden(true);
    CrtMaster::getInstance()->setPtojectTreeView(m_treeProject);
    
    m_treeMap = new CrtTreeView(this);
    m_treeMap->setHeaderHidden(true);
    CrtMaster::getInstance()->setMapTreeView(m_treeMap);

    m_treeProjectModel = new CrtTreeModel(this);
    m_treeProject->setModel(m_treeProjectModel);
    m_treeProject->setSelectionModel(new QItemSelectionModel());
    m_treeMapModel = new CrtTreeModel(this,1);
    m_treeMap->setModel(m_treeMapModel);
    m_treeMap->setSelectionModel(new QItemSelectionModel());

    QVBoxLayout* layoutProject = new QVBoxLayout(this);
    layoutProject->addWidget(toolBarProject);
    layoutProject->addWidget(m_treeProject);

    windProject->setLayout(layoutProject);
    m_panelProject->setWindowTitle(tr("Project"));

    addDockWidget(Qt::LeftDockWidgetArea,m_panelProject);

    m_panelMap = new QDockWidget(this);
    m_panelMap->setFeatures(QDockWidget::DockWidgetMovable);
    m_panelMap->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    QWidget* windMap = new QWidget(this);
    m_panelMap->setWidget(windMap);

    QVBoxLayout* layoutMap = new QVBoxLayout(this);
    layoutMap->addWidget(toolBarMap);
    layoutMap->addWidget(m_treeMap);
    windMap->setLayout(layoutMap);

    m_panelMap->setWindowTitle(tr("Design"));

    addDockWidget(Qt::RightDockWidgetArea,m_panelMap);

    m_panelDevice = new QDockWidget(this);
    m_panelDevice->setFeatures(QDockWidget::DockWidgetFloatable);
    m_panelDevice->setAllowedAreas(Qt::BottomDockWidgetArea);
    CrtSetDeviceDlg* dlg = new CrtSetDeviceDlg(this);
    CrtMaster::getInstance()->setCrtSetDeviceDlg(dlg);
    m_panelDevice->setWidget(dlg);
    m_panelDevice->setWindowTitle(tr("Device"));
    addDockWidget(Qt::BottomDockWidgetArea,m_panelDevice);
    m_panelDevice->setFloating(true);
    m_panelDevice->resize(800,600);
    m_panelDevice->setVisible(false);
    //panelDevice->setVisible(false);

    m_tabMain = new QTabWidget(this);

    m_frmProperty = new CrtPropertyContianer(this);

    m_tabMain->addTab(m_frmProperty,tr("Property"));

    m_mapView = new CrtGraphicsView(this);
    m_mapView->setBackgroundBrush(Qt::black);
    CrtMaster::getInstance()->setCrtGraphicsView(m_mapView);

    m_frmView = new CrtGraphicsViewContainer(m_mapView,toolBarGraphics,this);
    m_tabMain->addTab(m_frmView,tr("Graphics"));

    //tabMain->setTabPosition(QTabWidget::South);
    setCentralWidget(m_tabMain);
}

void MainWindow::initConnect()
{
    connect(m_btnCreateProj,SIGNAL(triggered(bool)),this,SLOT(slotCreateProject()));
    connect(m_btnOpenProj,SIGNAL(triggered(bool)),this,SLOT(slotOpenProject()));
    connect(m_btnSaveProj,SIGNAL(triggered(bool)),this,SLOT(slotSaveProject()));
    connect(m_btnCloseProj,SIGNAL(triggered(bool)),this,SLOT(slotCloseProject()));
    connect(m_tbPan,SIGNAL(clicked(bool)),this,SLOT(slotViewTransform()));
    connect(m_tbSetDevice,SIGNAL(clicked(bool)),this,SLOT(slotSetDevice()));
    connect(m_btnZoomin,SIGNAL(triggered(bool)),this,SLOT(slotViewTransform()));
    connect(m_btnZoomout,SIGNAL(triggered(bool)),this,SLOT(slotViewTransform()));
    connect(m_crtBtnAddController,SIGNAL(sigQuickPress()),this,SLOT(slotAddController()));
    connect(m_crtBtnAddController,SIGNAL(sigHoldPress()),this,SLOT(slotAddControllers()));
    connect(m_btnDeleteController,SIGNAL(triggered(bool)),this,SLOT(slotDeleteController()));
    connect(m_crtBtnAddLoop,SIGNAL(sigQuickPress()),this,SLOT(slotAddLoop()));
    connect(m_crtBtnAddLoop,SIGNAL(sigHoldPress()),this,SLOT(slotAddLoops()));
    connect(m_btnDeleteLoop,SIGNAL(triggered(bool)),this,SLOT(slotDeleteLoop()));
    connect(m_crtBtnAddDevice,SIGNAL(sigQuickPress()),this,SLOT(slotAddDevice()));
    connect(m_crtBtnAddDevice,SIGNAL(sigHoldPress()),this,SLOT(slotAddDevices()));
    connect(m_btnDeleteDevice,SIGNAL(triggered(bool)),this,SLOT(slotDeleteDevice()));
    connect(m_crtBtnAddBuilding,SIGNAL(sigQuickPress()),this,SLOT(slotAddBuilding()));
    connect(m_crtBtnAddBuilding,SIGNAL(sigHoldPress()),this,SLOT(slotAddBuildings()));
    connect(m_btnDeleteBuilding,SIGNAL(triggered(bool)),this,SLOT(slotDeleteBuilding()));
    connect(m_crtBtnAddLayer,SIGNAL(sigQuickPress()),this,SLOT(slotAddLayer()));
    connect(m_crtBtnAddLayer,SIGNAL(sigHoldPress()),this,SLOT(slotAddLayers()));
    connect(m_btnDeleteLayer,SIGNAL(triggered(bool)),this,SLOT(slotDeleteLayer()));
    connect(m_btnSetBackImage,SIGNAL(triggered(bool)),this,SLOT(slotSetBackImage()));
    connect(m_btnSetDevice,SIGNAL(triggered(bool)),this,SLOT(slotSetDevice()));
    connect(m_customSizeMenu, SIGNAL(triggered(QAction*)), this, SLOT(slotCustomSize(QAction*)));
    connect(static_cast<QItemSelectionModel*>(m_treeProject->selectionModel()),SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(slotProjectItemChanged()));
    connect(static_cast<QItemSelectionModel*>(m_treeMap->selectionModel()),SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(slotMapItemChanged()));
    connect(m_treeProject,SIGNAL(sigUpdateMainWindowTab(int)),this,SLOT(slotUpdateCurrentVisibleTab(int)));
    connect(m_treeMap,SIGNAL(sigUpdateMainWindowTab(int)),this,SLOT(slotUpdateCurrentVisibleTab(int)));
}

void MainWindow::initModel()
{
    if(!m_treeProjectModel)return;

    m_treeProjectModel->load(CrtMaster::getInstance()->getProject());
    m_treeMapModel->load(CrtMaster::getInstance()->getProject());
}

void MainWindow::loadProject(QString path)
{
    if(path.isEmpty())
    {
        CrtMaster::getInstance()->getManager()->initEngine();
    }
    else
    {
        if(!QFileInfo(path).exists())
        {
            QMessageBox::information(this,tr("warning"),tr("file not exists!"));
            return;
        }
        CrtMaster::getInstance()->getManager()->initEngine(path);
    }

    CrtMaster::getInstance()->setProject(new CrtProject());
    CrtMaster::getInstance()->getManager()->load(CrtMaster::getInstance()->getProject());
}

void MainWindow::slotOpenProject()
{
    QString path = QFileDialog::getOpenFileName(this,tr("Open Project File"),
                                                QDir::currentPath(),
                                                tr("SQLite Database Files (*.db)"));
    if(!QFileInfo(path).exists())
    {
        QMessageBox::information(this,tr("warning"),tr("file not exists!"));
        return;
    }

    if(CrtMaster::getInstance()->getProject())
    {
        QMessageBox::information(this,tr("warning"),tr("close current project first"));
        return;
    }
    CrtMaster::getInstance()->setManager(new DataManager());
    loadProject(path);
    initModel();
}

void MainWindow::slotCreateProject()
{
    if(CrtMaster::getInstance()->getProject())
    {
        QMessageBox::information(this,tr("warning"),tr("close current project first!"));
        return;
    }
    CrtMaster::getInstance()->setManager(new DataManager());
    CrtMaster::getInstance()->getManager()->initEngine();
    CrtProject* proj = new CrtProject();
    proj->setID(/*getid*/0);
    proj->setName("project1");
    CrtMaster::getInstance()->setProject(proj);
    initModel();
}

void MainWindow::slotSaveProject()
{
    if(!CrtMaster::getInstance()->getProject())
    {
        QMessageBox::information(this,tr("warning"),tr("no project!"));
        return;
    }

    /*QString path = QFileDialog::getSaveFileName(this, tr("Save Project File"),
                                                QDir::currentPath(),
                                                tr("SQLite Database File (*.db)"));
    if(QFileInfo(path).exists())
    {
        QMessageBox::information(this,tr("warning"),tr("file exists!"));
        return;
    }*/

    if(!CrtMaster::getInstance()->getManager()->save(CrtMaster::getInstance()->getProject()))
    {
        QMessageBox::information(this,tr("error"),tr("project save failed!"));
    }

    /*Libwmf::WmfWriter  wmf(path);
    wmf.begin();
    wmf.setWindow(0, 0, 200, 200);
    wmf.drawRect(10, 20, 50, 120);
    wmf.end();*/
}

void MainWindow::slotCloseProject()
{
    if(!CrtMaster::getInstance()->getProject())return;
    m_panelDevice->setVisible(false);
    m_panelProject->setVisible(true);
    CrtMaster::getInstance()->getCrtSetDeviceDlg()->releaseData();
    m_frmView->setCurrentPanel(NULL);
    m_mapView->setScene(NULL);
    m_treeMapModel->unload();
    m_treeProjectModel->unload();
    CrtMaster::getInstance()->setProject(NULL);
    CrtMaster::getInstance()->setManager(NULL);
    slotUpdateToolbarProjectState(0);
    slotUpdateToolbarMapState(0);
}

void MainWindow::slotViewTransform()
{
    if(sender() == m_btnZoomin)
    {
        m_mapView->zoomIn();
    }
    else if(sender() == m_btnZoomout)
    {
        m_mapView->zoomOut();
    }
    if(m_tbPan->isChecked())
    {
        m_mapView->setViewStatus(Pan);
    }
    else
    {
        m_mapView->setViewStatus(None);
    }
}

void MainWindow::slotAddController()
{
    QModelIndex index = m_treeProject->currentIndex();
    if(!index.isValid())return;

    int id = CrtMaster::getInstance()->getProject()->getAvaliableChildID();
    if(id == -1)
    {
        QMessageBox::information(this,tr("warning"),tr("Upper limit reached!"));
        return;
    }

    CrtController* controller = new CrtController();
    controller->setID(id);
    controller->setNetID(0);
    controller->setName(QString(tr("NT-Controller%1")).arg(id));
    controller->setControllerType(m_cmbCtrlList->currentText());
    controller->setSystemType(CrtMaster::getInstance()->getSystemType()->front());

    m_treeProject->insertItem(controller,index);
}

void MainWindow::slotAddControllers()
{
    QModelIndex index = m_treeProject->currentIndex();
    if(!index.isValid())return;
    bool ok = false;
    int nCount = QInputDialog::getInt(this,tr("Add Controller"),tr("Controller Count:"),1,1,128,1,&ok);
    if(!ok)return;

    QList<int> lst = CrtMaster::getInstance()->getProject()->getAvaliableChildsID();
    QList<CrtObject*> lstData;
    foreach(int id,lst)
    {
        if(nCount <= 0)
            break;
        CrtController* controller = new CrtController();
        controller->setID(id);
        controller->setName(QString(tr("NT-Controller%1")).arg(id));
        controller->setNetID(0);
        controller->setControllerType(m_cmbCtrlList->currentText());
        controller->setSystemType(CrtMaster::getInstance()->getSystemType()->front());
        lstData.append(controller);
        nCount--;
    }
    if(!lstData.isEmpty())
        m_treeProject->insertItems(lstData,index);
}

void MainWindow::slotDeleteController()
{
    QModelIndex index = m_treeProject->currentIndex();
    if(!index.isValid())return;

    m_treeProject->deleteItem(index);
}

void MainWindow::slotAddLoop()
{
    QModelIndex index = m_treeProject->currentIndex();
    if(!index.isValid())return;

    int id = static_cast<CrtObject*>(index.internalPointer())->getAvaliableChildID();
    if(id == -1)
    {
        QMessageBox::information(this,tr("warning"),tr("Upper limit reached!"));
        return;
    }

    CrtLoop* loop = new CrtLoop();
    loop->setID(id);
    loop->setName(QString(tr("NT-Loop%1")).arg(id));

    m_treeProject->insertItem(loop,index);
}

void MainWindow::slotAddLoops()
{
    QModelIndex index = m_treeProject->currentIndex();
    if(!index.isValid())return;
    bool ok = false;
    int nCount = QInputDialog::getInt(this,tr("Add Loop"),tr("Loop Count:"),1,1,64,1,&ok);
    if(!ok)return;

    QList<int> lst = static_cast<CrtObject*>(index.internalPointer())->getAvaliableChildsID();
    QList<CrtObject*> lstData;
    foreach(int id,lst)
    {
        if(nCount <= 0)
            break;
        CrtLoop* loop = new CrtLoop();
        loop->setID(id);
        loop->setName(QString(tr("NT-Loop%1")).arg(id));
        lstData.append(loop);
        nCount--;
    }
    if(!lstData.isEmpty())
        m_treeProject->insertItems(lstData,index);
}

void MainWindow::slotDeleteLoop()
{
    QModelIndex index = m_treeProject->currentIndex();
    if(!index.isValid())return;

    m_treeProject->deleteItem(index);
}

void MainWindow::slotAddDevice()
{
    QModelIndex index = m_treeProject->currentIndex();
    if(!index.isValid())return;

    int id = static_cast<CrtObject*>(index.internalPointer())->getAvaliableChildID();
    if(id == -1)
    {
        QMessageBox::information(this,tr("warning"),tr("Upper limit reached!"));
        return;
    }

    CrtDevice* device = new CrtDevice();
    device->setID(id);
    device->setName(QString(tr("NT-Device%1")).arg(id));
    device->setDeviceZone(0);
    device->setDeviceAddress("");
    device->setDeviceType(m_cmbDevList->currentText());

    m_treeProject->insertItem(device,index);
}

void MainWindow::slotAddDevices()
{
    QModelIndex index = m_treeProject->currentIndex();
    if(!index.isValid())return;
    bool ok = false;
    int nCount = QInputDialog::getInt(this,tr("Add Device"),tr("Device Count:"),1,1,252,1,&ok);
    if(!ok)return;

    QList<int> lst = static_cast<CrtObject*>(index.internalPointer())->getAvaliableChildsID();
    QList<CrtObject*> lstData;
    foreach(int id,lst)
    {
        if(nCount <= 0)
            break;
        CrtDevice* device = new CrtDevice();
        device->setID(id);
        device->setName(QString(tr("NT-Device%1")).arg(id));
        device->setDeviceZone(0);
        device->setDeviceAddress("");
        device->setDeviceType(m_cmbDevList->currentText());
        lstData.append(device);
        nCount--;
    }
    if(!lstData.isEmpty())
        m_treeProject->insertItems(lstData,index);
}

void MainWindow::slotDeleteDevice()
{
    QModelIndex index = m_treeProject->currentIndex();
    if(!index.isValid())return;

    m_treeProject->deleteItem(index);
}

void MainWindow::slotAddBuilding()
{
    QModelIndex index = m_treeMap->currentIndex();
    if(!index.isValid())return;

    int id = CrtMaster::getInstance()->getProject()->getAvaliableChildID(1);
    if(id == -1)
    {
        QMessageBox::information(this,tr("warning"),tr("Upper limit reached!"));
        return;
    }

    CrtBuilding* building = new CrtBuilding(CrtMaster::getInstance()->getProject());
    building->setID(id);
    building->setName(QString(tr("NT-Building%1")).arg(id));

    m_treeMap->insertItem(building,index);
}

void MainWindow::slotAddBuildings()
{
    QModelIndex index = m_treeMap->currentIndex();
    if(!index.isValid())return;
    bool ok = false;
    int nCount = QInputDialog::getInt(this,tr("Add Building"),tr("Building Count:"),1,1,80,1,&ok);
    if(!ok)return;

    QList<int> lst = CrtMaster::getInstance()->getProject()->getAvaliableChildsID(1);
    QList<CrtObject*> lstData;
    foreach(int id,lst)
    {
        if(nCount <= 0)
            break;
        CrtBuilding* building = new CrtBuilding(CrtMaster::getInstance()->getProject());
        building->setID(id);
        building->setName(QString(tr("NT-Building%1")).arg(id));
        lstData.append(building);
        nCount--;
    }
    if(!lstData.isEmpty())
        m_treeMap->insertItems(lstData,index);
}

void MainWindow::slotDeleteBuilding()
{
    QModelIndex index = m_treeMap->currentIndex();
    if(!index.isValid())return;

    m_treeMap->deleteItem(index);
}

void MainWindow::slotAddLayer()
{
    QModelIndex index = m_treeMap->currentIndex();
    if(!index.isValid())return;

    int id = static_cast<CrtObject*>(index.internalPointer())->getAvaliableChildID();
    if(id == -1)
    {
        QMessageBox::information(this,tr("warning"),tr("Upper limit reached!"));
        return;
    }

    CrtLayer* layer = new CrtLayer();
    //this id is not correct
    layer->setID(id);
    layer->setName(QString(tr("NT-Layer%1")).arg(id));

    m_treeMap->insertItem(layer,index);
}

void MainWindow::slotAddLayers()
{
    QModelIndex index = m_treeMap->currentIndex();
    if(!index.isValid())return;
    bool ok = false;
    int nCount = QInputDialog::getInt(this,tr("Add Layer"),tr("Layer Count:"),1,1,80,1,&ok);
    if(!ok)return;

    QList<int> lst = static_cast<CrtObject*>(index.internalPointer())->getAvaliableChildsID();
    QList<CrtObject*> lstData;
    foreach(int id,lst)
    {
        if(nCount <= 0)
            break;
        CrtLayer* layer = new CrtLayer();
        //this id is not correct
        layer->setID(id);
        layer->setName(QString(tr("NT-Layer%1")).arg(id));
        lstData.append(layer);
        nCount--;
    }
    if(!lstData.isEmpty())
        m_treeMap->insertItems(lstData,index);
}

void MainWindow::slotDeleteLayer()
{
    QModelIndex index = m_treeMap->currentIndex();
    if(!index.isValid())return;

    m_treeMap->deleteItem(index);
}

void MainWindow::slotSetBackImage()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open Map File"),
                                                QDir::currentPath(),
                                                tr("Images (*.jpg *.png *.wmf *.bmp)"));
    if(!QFileInfo(path).exists())
    {
        QMessageBox::information(this,tr("warning"),tr("file not exists!"));
        return;
    }

    QString currentPath = QDir::currentPath();
    QString newPath = QString("%1/image").arg(currentPath);
    QDir dir(newPath);
    if(!dir.exists())
    {
        dir.mkdir(newPath);
    }

    QString imageFile = QString("./image/%1").arg(QFileInfo(path).fileName());
    QFile::copy(path,imageFile);
    //load file
    QModelIndex index = m_treeMap->currentIndex();
    if(index.isValid())
    {
        CrtLayer* layer = static_cast<CrtLayer*>(index.internalPointer());
        layer->setBackground(imageFile);
        m_mapView->setSceneRect(layer->getScene()->getBackground()->boundingRect());
    }
}

void MainWindow::slotProjectItemChanged()
{
    QModelIndex index = m_treeProject->currentIndex();
    if(!index.isValid())return;
    CrtObject* item = (CrtObject*)index.internalPointer();
    if(item)
    {
        if(!item->getType().compare("project"))
           emit slotUpdateToolbarProjectState(1);
        else if(!item->getType().compare("controller"))
            emit slotUpdateToolbarProjectState(2);
        else if(!item->getType().compare("loop"))
            emit slotUpdateToolbarProjectState(6);
        else if(!item->getType().compare("device"))
            emit slotUpdateToolbarProjectState(7);
        else
            emit slotUpdateToolbarProjectState(0);
        m_frmProperty->setCurrentPanel(item);
    }
}

void MainWindow::slotMapItemChanged()
{
    QModelIndex index = m_treeMap->currentIndex();
    if(!index.isValid())return;
    m_mapView->setScene(NULL);
    CrtObject* item = (CrtObject*)index.internalPointer();
    if(item)
    {
        if(!item->getType().compare("project"))
           emit slotUpdateToolbarMapState(3);
        else if(!item->getType().compare("building"))
            emit slotUpdateToolbarMapState(4);
        else if(!item->getType().compare("layer"))
        {
            emit slotUpdateToolbarMapState(5);
            m_mapView->setScene(dynamic_cast<CrtLayer*>(item)->getScene());
        }
        else
            emit slotUpdateToolbarMapState(0);
        m_frmView->setCurrentPanel(item);
    }
}

void MainWindow::slotSetDevice()
{
    if(CrtMaster::getInstance()->getProject())
    {
        if(!m_tbSetDevice->isChecked())
        {
            m_panelDevice->setVisible(false);
            //panelProject->setVisible(true);
            CrtMaster::getInstance()->getCrtSetDeviceDlg()->releaseData();
        }else
        {
            CrtMaster::getInstance()->getCrtSetDeviceDlg()->loadData();
            m_panelDevice->setVisible(true);
            //panelProject->setVisible(false);
        }
    }
}

void MainWindow::slotCustomSize(QAction *action)
{
    foreach(QGraphicsItem* item,CrtMaster::getInstance()->getCrtGraphicsView()->scene()->selectedItems())
    {
        item->setScale(action->data().toFloat());
    }
}

void MainWindow::slotUpdateToolbarProjectState(int state)
{
    foreach(QAction* btn,QList<QAction*>()<<m_btnAddController<<m_btnDeleteController<<m_btnAddLoop
            <<m_btnDeleteLoop<<m_btnAddDevice<<m_btnDeleteDevice<<m_actCtrlList<<m_actDevList)
    {
        btn->setVisible(false);
    }

    switch(state)
    {
    case 0://project
    {
    }
        break;
    case 1://controller
    {
        m_btnAddController->setVisible(true);
        m_actCtrlList->setVisible(true);
    }
        break;
    case 2://loop
    {
        m_btnDeleteController->setVisible(true);
        m_btnAddLoop->setVisible(true);
    }
        break;
    case 3://building
    {
        m_btnAddBuilding->setVisible(true);
    }
        break;
    case 4://layer
    {
        m_btnDeleteBuilding->setVisible(true);
        m_btnAddLayer->setVisible(true);
    }
        break;
    case 5://map
    {
        m_btnDeleteLayer->setVisible(true);
    }
        break;
    case 6://device
    {
        m_btnAddDevice->setVisible(true);
        m_btnDeleteLoop->setVisible(true);
        m_actDevList->setVisible(true);
    }
        break;
    case 7:
    {
        m_btnDeleteDevice->setVisible(true);
    }
        break;
    }
}

void MainWindow::slotUpdateToolbarMapState(int state)
{
    foreach(QAction* btn,QList<QAction*>()<<m_btnAddBuilding<<m_btnDeleteBuilding<<m_btnAddLayer<<m_btnDeleteLayer)
    {
        btn->setVisible(false);
    }

    switch(state)
    {
    case 0://project
    {
    }
        break;
    case 1://controller
    {
        m_btnAddController->setVisible(true);
    }
        break;
    case 2://loop
    {
        m_btnDeleteController->setVisible(true);
        m_btnAddLoop->setVisible(true);
    }
        break;
    case 3://building
    {
        m_btnAddBuilding->setVisible(true);
    }
        break;
    case 4://layer
    {
        m_btnDeleteBuilding->setVisible(true);
        m_btnAddLayer->setVisible(true);
    }
        break;
    case 5://map
    {
        m_btnDeleteLayer->setVisible(true);
    }
        break;
    case 6://device
    {
        m_btnAddDevice->setVisible(true);
        m_btnDeleteLoop->setVisible(true);
        m_actDevList->setVisible(true);
    }
        break;
    case 7:
    {
        m_btnDeleteDevice->setVisible(true);
    }
        break;
    }
}

void MainWindow::slotUpdateCurrentVisibleTab(int index)
{
    m_tabMain->setCurrentIndex(index);
}

void MainWindow::closeEvent(QCloseEvent *)
{
    CrtMaster::getInstance()->destroy();
}
