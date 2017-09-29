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
	InitUi();
	InitConnect();
    //resize(1250, 850);
    //setMinimumSize(1250,850);
    setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow()
{

}

void MainWindow::InitUi()
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

    btnCreateProj = new QAction(QIcon(":/img/new.png"),tr("Create Project"),this);
    toolBar->addAction(btnCreateProj);
    btnOpenProj = new QAction(QIcon(":/img/open.png"),tr("Open Project"),this);
    toolBar->addAction(btnOpenProj);
    btnSaveProj = new QAction(QIcon(":/img/save.png"),tr("Save Project"),this);
    toolBar->addAction(btnSaveProj);
    btnCloseProj = new QAction(QIcon(":/img/close.png"),tr("Close Project"),this);
    toolBar->addAction(btnCloseProj);
    //toolBar->addSeparator();

    crtBtnAddController = new CrtTwoWayToolButton(this);
    crtBtnAddController->setIcon(QIcon(":/img/controlleradd.png"));
    crtBtnAddController->setToolTip(tr("Add Controller"));
    btnAddController = toolBarProject->addWidget(crtBtnAddController);
    btnDeleteController = new QAction(QIcon(":/img/controllersub.png"),tr("Delete Controller"),this);
    toolBarProject->addAction(btnDeleteController);

    crtBtnAddLoop = new CrtTwoWayToolButton(this);
    crtBtnAddLoop->setIcon(QIcon(":/img/addloop.png"));
    crtBtnAddLoop->setToolTip(tr("Add Loop"));
    btnAddLoop = toolBarProject->addWidget(crtBtnAddLoop);
    btnDeleteLoop = new QAction(QIcon(":/img/delloop.png"),tr("Delete Loop"),this);
    toolBarProject->addAction(btnDeleteLoop);

    crtBtnAddDevice = new CrtTwoWayToolButton(this);
    crtBtnAddDevice->setIcon(QIcon(":/img/adddev.png"));
    crtBtnAddDevice->setToolTip(tr("Add Device"));
    btnAddDevice = toolBarProject->addWidget(crtBtnAddDevice);
    btnDeleteDevice = new QAction(QIcon(":/img/deldev.png"),tr("Delete Device"),this);
    toolBarProject->addAction(btnDeleteDevice);

    crtBtnAddBuilding = new CrtTwoWayToolButton(this);
    crtBtnAddBuilding->setIcon(QIcon(":/img/addcatigory.png"));
    crtBtnAddBuilding->setToolTip(tr("Add Building"));
    btnAddBuilding = toolBarMap->addWidget(crtBtnAddBuilding);
    btnDeleteBuilding = new QAction(QIcon(":/img/delcatigory.png"),tr("Delete Building"),this);
    toolBarMap->addAction(btnDeleteBuilding);

    crtBtnAddLayer = new CrtTwoWayToolButton(this);
    crtBtnAddLayer->setIcon(QIcon(":/img/addlayer.png"));
    crtBtnAddLayer->setToolTip(tr("Add Layer"));
    btnAddLayer = toolBarMap->addWidget(crtBtnAddLayer);
    btnDeleteLayer = new QAction(QIcon(":/img/dellayer.png"),tr("Delete Layer"),this);
    toolBarMap->addAction(btnDeleteLayer);

    btnSetBackImage = new QAction(QIcon(":/img/map.png"),tr("Set BackImage"),this);
    tbPan = new QToolButton(this);
    tbPan->setIcon(QIcon(":/img/drag.png"));
    tbPan->setToolTip(tr("Drag Map"));
    tbPan->setCheckable(true);

    btnZoomin = new QAction(QIcon(":/img/zoomin.png"),tr("Zoom In"),this);
    btnZoomout = new QAction(QIcon(":/img/zoomout.png"),tr("Zoom Out"),this);
    toolBarGraphics->addAction(btnSetBackImage);
    btnPan = toolBarGraphics->addWidget(tbPan);
    toolBarGraphics->addAction(btnZoomin);
    toolBarGraphics->addAction(btnZoomout);

    tbSetDevice = new QToolButton(this);
    tbSetDevice->setIcon(QIcon(":/img/marknormalpoint.png"));
    tbSetDevice->setToolTip(tr("Set Device"));
    tbSetDevice->setCheckable(true);
    btnSetDevice = toolBarGraphics->addWidget(tbSetDevice);
    //toolBarGraphics->addAction(btnSetDevice);

    cmbDevList = new QComboBox();
    cmbDevList->setFixedWidth(180);

    QDir dir(":/device");//change to local device dir
    dir.setFilter(QDir::Files | QDir::NoSymLinks);

    QFileInfoList lst = dir.entryInfoList();

    for(int i=0;i<lst.size();i++)
    {
        QFileInfo fi = lst.at(i);
        if(fi.suffix() == "bmp")
        {
            cmbDevList->addItem(QIcon(fi.filePath()),fi.baseName(),fi.filePath());
        }
    }

    actDevList = toolBarProject->addWidget(cmbDevList);

    cmbCtrlList = new QComboBox(this);

    cmbCtrlList->addItems(*(CrtMaster::GetInstance()->ControllerType()));

    actCtrlList = toolBarProject->addWidget(cmbCtrlList);

    addToolBar(toolBar);

    UpdateToolbarProjectState(0);
    UpdateToolbarMapState(0);

    panelProject = new QDockWidget(this);
    panelProject->setFeatures(QDockWidget::DockWidgetMovable);
    panelProject->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    QWidget* windProject = new QWidget(this);
    panelProject->setWidget(windProject);

    treeProject = new CrtTreeView(this);
    treeProject->setHeaderHidden(true);
    CrtMaster::GetInstance()->setPtojectTreeView(treeProject);
    
    treeMap = new CrtTreeView(this);
    treeMap->setHeaderHidden(true);
    CrtMaster::GetInstance()->setMapTreeView(treeMap);

    treeProjectModel = new CrtTreeModel(this);
    treeProject->setModel(treeProjectModel);
    treeProject->setSelectionModel(new QItemSelectionModel());
    treeMapModel = new CrtTreeModel(this,1);
    treeMap->setModel(treeMapModel);
    treeMap->setSelectionModel(new QItemSelectionModel());

    QVBoxLayout* layoutProject = new QVBoxLayout(this);
    layoutProject->addWidget(toolBarProject);
    layoutProject->addWidget(treeProject);

    windProject->setLayout(layoutProject);
    panelProject->setWindowTitle(tr("Project"));

    addDockWidget(Qt::LeftDockWidgetArea,panelProject);

    panelMap = new QDockWidget(this);
    panelMap->setFeatures(QDockWidget::DockWidgetMovable);
    panelMap->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    QWidget* windMap = new QWidget(this);
    panelMap->setWidget(windMap);

    QVBoxLayout* layoutMap = new QVBoxLayout(this);
    layoutMap->addWidget(toolBarMap);
    layoutMap->addWidget(treeMap);
    windMap->setLayout(layoutMap);

    panelMap->setWindowTitle(tr("Design"));

    addDockWidget(Qt::RightDockWidgetArea,panelMap);

    panelDevice = new QDockWidget(this);
    panelDevice->setFeatures(QDockWidget::NoDockWidgetFeatures);
    panelDevice->setAllowedAreas(Qt::LeftDockWidgetArea);
    CrtSetDeviceDlg* dlg = new CrtSetDeviceDlg(this);
    CrtMaster::GetInstance()->setCrtSetDeviceDlg(dlg);
    panelDevice->setWidget(dlg);
    panelDevice->setWindowTitle(tr("Device"));
    addDockWidget(Qt::LeftDockWidgetArea,panelDevice);
    panelDevice->setVisible(false);
    //panelDevice->setVisible(false);

    tabMain = new QTabWidget(this);

    frmProperty = new CrtPropertyContianer(this);

    tabMain->addTab(frmProperty,tr("Property"));

    mapView = new CrtGraphicsView(this);
    mapView->setBackgroundBrush(Qt::black);
    CrtMaster::GetInstance()->setCrtGraphicsView(mapView);

    frmView = new CrtGraphicsViewContainer(mapView,toolBarGraphics,this);
    tabMain->addTab(frmView,tr("Graphics"));

    //tabMain->setTabPosition(QTabWidget::South);
    setCentralWidget(tabMain);
}

void MainWindow::InitConnect()
{
    connect(btnCreateProj,SIGNAL(triggered(bool)),this,SLOT(OnCreateProject()));
    connect(btnOpenProj,SIGNAL(triggered(bool)),this,SLOT(OnOpenProject()));
    connect(btnSaveProj,SIGNAL(triggered(bool)),this,SLOT(OnSaveProject()));
    connect(btnCloseProj,SIGNAL(triggered(bool)),this,SLOT(OnCloseProject()));
    connect(tbPan,SIGNAL(clicked(bool)),this,SLOT(OnViewTransform()));
    connect(tbSetDevice,SIGNAL(clicked(bool)),this,SLOT(OnSetDevice()));
    connect(btnZoomin,SIGNAL(triggered(bool)),this,SLOT(OnViewTransform()));
    connect(btnZoomout,SIGNAL(triggered(bool)),this,SLOT(OnViewTransform()));
    connect(crtBtnAddController,SIGNAL(quickpress()),this,SLOT(OnAddController()));
    connect(crtBtnAddController,SIGNAL(holdpress()),this,SLOT(OnAddControllers()));
    connect(btnDeleteController,SIGNAL(triggered(bool)),this,SLOT(OnDeleteController()));
    connect(crtBtnAddLoop,SIGNAL(quickpress()),this,SLOT(OnAddLoop()));
    connect(crtBtnAddLoop,SIGNAL(holdpress()),this,SLOT(OnAddLoops()));
    connect(btnDeleteLoop,SIGNAL(triggered(bool)),this,SLOT(OnDeleteLoop()));
    connect(crtBtnAddDevice,SIGNAL(quickpress()),this,SLOT(OnAddDevice()));
    connect(crtBtnAddDevice,SIGNAL(holdpress()),this,SLOT(OnAddDevices()));
    connect(btnDeleteDevice,SIGNAL(triggered(bool)),this,SLOT(OnDeleteDevice()));
    connect(crtBtnAddBuilding,SIGNAL(quickpress()),this,SLOT(OnAddBuilding()));
    connect(crtBtnAddBuilding,SIGNAL(holdpress()),this,SLOT(OnAddBuildings()));
    connect(btnDeleteBuilding,SIGNAL(triggered(bool)),this,SLOT(OnDeleteBuilding()));
    connect(crtBtnAddLayer,SIGNAL(quickpress()),this,SLOT(OnAddLayer()));
    connect(crtBtnAddLayer,SIGNAL(holdpress()),this,SLOT(OnAddLayers()));
    connect(btnDeleteLayer,SIGNAL(triggered(bool)),this,SLOT(OnDeleteLayer()));
    connect(btnSetBackImage,SIGNAL(triggered(bool)),this,SLOT(OnSetBackImage()));
    connect(btnSetDevice,SIGNAL(triggered(bool)),this,SLOT(OnSetDevice()));
    connect(static_cast<QItemSelectionModel*>(treeProject->selectionModel()),SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(OnProjectItemChanged()));
    connect(static_cast<QItemSelectionModel*>(treeMap->selectionModel()),SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(OnMapItemChanged()));
    connect(treeProject,SIGNAL(updateMainWindowTab(int)),this,SLOT(UpdateCurrentVisibleTab(int)));
    connect(treeMap,SIGNAL(updateMainWindowTab(int)),this,SLOT(UpdateCurrentVisibleTab(int)));
}

void MainWindow::InitModel()
{
    if(!treeProjectModel)return;

    treeProjectModel->load(CrtMaster::GetInstance()->Project());
    treeMapModel->load(CrtMaster::GetInstance()->Project());
}

void MainWindow::loadProject(QString path)
{
    if(path.isEmpty())
    {
        CrtMaster::GetInstance()->Manager()->InitEngine();
    }
    else
    {
        if(!QFileInfo(path).exists())
        {
            QMessageBox::information(this,tr("warning"),tr("file not exists!"));
            return;
        }
        CrtMaster::GetInstance()->Manager()->InitEngine(path);
    }

    CrtMaster::GetInstance()->setProject(new CrtProject());
    CrtMaster::GetInstance()->Manager()->load(CrtMaster::GetInstance()->Project());
}

void MainWindow::OnOpenProject()
{
    QString path = QFileDialog::getOpenFileName(this,tr("Open Project File"),
                                                QDir::currentPath(),
                                                tr("SQLite Database Files (*.db)"));
    if(!QFileInfo(path).exists())
    {
        QMessageBox::information(this,tr("warning"),tr("file not exists!"));
        return;
    }

    if(CrtMaster::GetInstance()->Project())
    {
        QMessageBox::information(this,tr("warning"),tr("close current project first"));
        return;
    }
    CrtMaster::GetInstance()->setManager(new DataManager());
    loadProject(path);
    InitModel();
}

void MainWindow::OnCreateProject()
{
    if(CrtMaster::GetInstance()->Project())
    {
        QMessageBox::information(this,tr("warning"),tr("close current project first!"));
        return;
    }
    CrtMaster::GetInstance()->setManager(new DataManager());
    CrtMaster::GetInstance()->Manager()->InitEngine();
    CrtProject* proj = new CrtProject();
    proj->setID(/*getid*/0);
    proj->setName("project1");
    CrtMaster::GetInstance()->setProject(proj);
    InitModel();
}

void MainWindow::OnSaveProject()
{
    if(!CrtMaster::GetInstance()->Project())
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

    if(!CrtMaster::GetInstance()->Manager()->save(CrtMaster::GetInstance()->Project()))
    {
        QMessageBox::information(this,tr("error"),tr("project save failed!"));
    }

    /*Libwmf::WmfWriter  wmf(path);
    wmf.begin();
    wmf.setWindow(0, 0, 200, 200);
    wmf.drawRect(10, 20, 50, 120);
    wmf.end();*/
}

void MainWindow::OnCloseProject()
{
    if(!CrtMaster::GetInstance()->Project())return;
    panelDevice->setVisible(false);
    panelProject->setVisible(true);
    CrtMaster::GetInstance()->getCrtSetDeviceDlg()->releaseData();
    frmView->setCurrentPanel(NULL);
    mapView->setScene(NULL);
    treeMapModel->unload();
    treeProjectModel->unload();
    CrtMaster::GetInstance()->setProject(NULL);
    CrtMaster::GetInstance()->setManager(NULL);
    UpdateToolbarProjectState(0);
    UpdateToolbarMapState(0);
}

void MainWindow::OnViewTransform()
{
    if(sender() == btnZoomin)
    {
        mapView->zoomIn();
    }
    else if(sender() == btnZoomout)
    {
        mapView->zoomOut();
    }
    if(tbPan->isChecked())
    {
        mapView->setViewStatus(Pan);
    }
    else
    {
        mapView->setViewStatus(None);
    }
}

void MainWindow::OnAddController()
{
    QModelIndex index = treeProject->currentIndex();
    if(!index.isValid())return;

    int id = CrtMaster::GetInstance()->Project()->getAvaliableChildID();
    if(id == -1)
    {
        QMessageBox::information(this,tr("warning"),tr("Upper limit reached!"));
        return;
    }

    CrtController* controller = new CrtController();
    controller->setID(id);
    controller->setNetID(0);
    controller->setName(QString(tr("NT-Controller%1")).arg(id));
    controller->setControllerType(cmbCtrlList->currentText());
    controller->setSystemType(CrtMaster::GetInstance()->SystemType()->front());

    treeProject->insertItem(controller,index);
}

void MainWindow::OnAddControllers()
{
    QModelIndex index = treeProject->currentIndex();
    if(!index.isValid())return;
    bool ok = false;
    int nCount = QInputDialog::getInt(this,tr("Add Controller"),tr("Controller Count:"),1,1,128,1,&ok);
    if(!ok)return;

    QList<int> lst = CrtMaster::GetInstance()->Project()->getAvaliableChildsID();
    QList<CrtObject*> lstData;
    foreach(int id,lst)
    {
        if(nCount <= 0)
            break;
        CrtController* controller = new CrtController();
        controller->setID(id);
        controller->setName(QString(tr("NT-Controller%1")).arg(id));
        controller->setNetID(0);
        controller->setControllerType(cmbCtrlList->currentText());
        controller->setSystemType(CrtMaster::GetInstance()->SystemType()->front());
        lstData.append(controller);
        nCount--;
    }
    if(!lstData.isEmpty())
        treeProject->insertItems(lstData,index);
}

void MainWindow::OnDeleteController()
{
    QModelIndex index = treeProject->currentIndex();
    if(!index.isValid())return;

    treeProject->deleteItem(index);
}

void MainWindow::OnAddLoop()
{
    QModelIndex index = treeProject->currentIndex();
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

    treeProject->insertItem(loop,index);
}

void MainWindow::OnAddLoops()
{
    QModelIndex index = treeProject->currentIndex();
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
        treeProject->insertItems(lstData,index);
}

void MainWindow::OnDeleteLoop()
{
    QModelIndex index = treeProject->currentIndex();
    if(!index.isValid())return;

    treeProject->deleteItem(index);
}

void MainWindow::OnAddDevice()
{
    QModelIndex index = treeProject->currentIndex();
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
    device->setDeviceType(cmbDevList->currentText());

    treeProject->insertItem(device,index);
}

void MainWindow::OnAddDevices()
{
    QModelIndex index = treeProject->currentIndex();
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
        device->setDeviceType(cmbDevList->currentText());
        lstData.append(device);
        nCount--;
    }
    if(!lstData.isEmpty())
        treeProject->insertItems(lstData,index);
}

void MainWindow::OnDeleteDevice()
{
    QModelIndex index = treeProject->currentIndex();
    if(!index.isValid())return;

    treeProject->deleteItem(index);
}

void MainWindow::OnAddBuilding()
{
    QModelIndex index = treeMap->currentIndex();
    if(!index.isValid())return;

    int id = CrtMaster::GetInstance()->Project()->getAvaliableChildID(1);
    if(id == -1)
    {
        QMessageBox::information(this,tr("warning"),tr("Upper limit reached!"));
        return;
    }

    CrtBuilding* building = new CrtBuilding(CrtMaster::GetInstance()->Project());
    building->setID(id);
    building->setName(QString(tr("NT-Building%1")).arg(id));

    treeMap->insertItem(building,index);
}

void MainWindow::OnAddBuildings()
{
    QModelIndex index = treeMap->currentIndex();
    if(!index.isValid())return;
    bool ok = false;
    int nCount = QInputDialog::getInt(this,tr("Add Building"),tr("Building Count:"),1,1,80,1,&ok);
    if(!ok)return;

    QList<int> lst = CrtMaster::GetInstance()->Project()->getAvaliableChildsID(1);
    QList<CrtObject*> lstData;
    foreach(int id,lst)
    {
        if(nCount <= 0)
            break;
        CrtBuilding* building = new CrtBuilding(CrtMaster::GetInstance()->Project());
        building->setID(id);
        building->setName(QString(tr("NT-Building%1")).arg(id));
        lstData.append(building);
        nCount--;
    }
    if(!lstData.isEmpty())
        treeMap->insertItems(lstData,index);
}

void MainWindow::OnDeleteBuilding()
{
    QModelIndex index = treeMap->currentIndex();
    if(!index.isValid())return;

    treeMap->deleteItem(index);
}

void MainWindow::OnAddLayer()
{
    QModelIndex index = treeMap->currentIndex();
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

    treeMap->insertItem(layer,index);
}

void MainWindow::OnAddLayers()
{
    QModelIndex index = treeMap->currentIndex();
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
        treeMap->insertItems(lstData,index);
}

void MainWindow::OnDeleteLayer()
{
    QModelIndex index = treeMap->currentIndex();
    if(!index.isValid())return;

    treeMap->deleteItem(index);
}

void MainWindow::OnSetBackImage()
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
    QModelIndex index = treeMap->currentIndex();
    if(index.isValid())
    {
        CrtLayer* layer = static_cast<CrtLayer*>(index.internalPointer());
        layer->setBackground(imageFile);
        mapView->setSceneRect(layer->Scene()->Background()->boundingRect());
    }
}

void MainWindow::OnProjectItemChanged()
{
    QModelIndex index = treeProject->currentIndex();
    if(!index.isValid())return;
    CrtObject* item = (CrtObject*)index.internalPointer();
    if(item)
    {
        if(!item->Type().compare("project"))
           emit UpdateToolbarProjectState(1);
        else if(!item->Type().compare("controller"))
            emit UpdateToolbarProjectState(2);
        else if(!item->Type().compare("loop"))
            emit UpdateToolbarProjectState(6);
        else if(!item->Type().compare("device"))
            emit UpdateToolbarProjectState(7);
        else
            emit UpdateToolbarProjectState(0);
        frmProperty->setCurrentPanel(item);
    }
}

void MainWindow::OnMapItemChanged()
{
    QModelIndex index = treeMap->currentIndex();
    if(!index.isValid())return;
    mapView->setScene(NULL);
    CrtObject* item = (CrtObject*)index.internalPointer();
    if(item)
    {
        if(!item->Type().compare("project"))
           emit UpdateToolbarMapState(3);
        else if(!item->Type().compare("building"))
            emit UpdateToolbarMapState(4);
        else if(!item->Type().compare("layer"))
        {
            emit UpdateToolbarMapState(5);
            mapView->setScene(dynamic_cast<CrtLayer*>(item)->Scene());
        }
        else
            emit UpdateToolbarMapState(0);
        frmView->setCurrentPanel(item);
    }
}

void MainWindow::OnSetDevice()
{
    if(CrtMaster::GetInstance()->Project())
    {
        if(!tbSetDevice->isChecked())
        {
            panelDevice->setVisible(false);
            panelProject->setVisible(true);
            CrtMaster::GetInstance()->getCrtSetDeviceDlg()->releaseData();
        }else
        {
            CrtMaster::GetInstance()->getCrtSetDeviceDlg()->loadData();
            panelDevice->setVisible(true);
            panelProject->setVisible(false);
        }
    }
}

void MainWindow::UpdateToolbarProjectState(int state)
{
    foreach(QAction* btn,QList<QAction*>()<<btnAddController<<btnDeleteController<<btnAddLoop
            <<btnDeleteLoop<<btnAddDevice<<btnDeleteDevice<<actCtrlList<<actDevList)
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
        btnAddController->setVisible(true);
        actCtrlList->setVisible(true);
    }
        break;
    case 2://loop
    {
        btnDeleteController->setVisible(true);
        btnAddLoop->setVisible(true);
    }
        break;
    case 3://building
    {
        btnAddBuilding->setVisible(true);
    }
        break;
    case 4://layer
    {
        btnDeleteBuilding->setVisible(true);
        btnAddLayer->setVisible(true);
    }
        break;
    case 5://map
    {
        btnDeleteLayer->setVisible(true);
    }
        break;
    case 6://device
    {
        btnAddDevice->setVisible(true);
        btnDeleteLoop->setVisible(true);
        actDevList->setVisible(true);
    }
        break;
    case 7:
    {
        btnDeleteDevice->setVisible(true);
    }
        break;
    }
}

void MainWindow::UpdateToolbarMapState(int state)
{
    foreach(QAction* btn,QList<QAction*>()<<btnAddBuilding<<btnDeleteBuilding<<btnAddLayer<<btnDeleteLayer)
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
        btnAddController->setVisible(true);
    }
        break;
    case 2://loop
    {
        btnDeleteController->setVisible(true);
        btnAddLoop->setVisible(true);
    }
        break;
    case 3://building
    {
        btnAddBuilding->setVisible(true);
    }
        break;
    case 4://layer
    {
        btnDeleteBuilding->setVisible(true);
        btnAddLayer->setVisible(true);
    }
        break;
    case 5://map
    {
        btnDeleteLayer->setVisible(true);
    }
        break;
    case 6://device
    {
        btnAddDevice->setVisible(true);
        btnDeleteLoop->setVisible(true);
        actDevList->setVisible(true);
    }
        break;
    case 7:
    {
        btnDeleteDevice->setVisible(true);
    }
        break;
    }
}

void MainWindow::UpdateCurrentVisibleTab(int index)
{
    tabMain->setCurrentIndex(index);
}

void MainWindow::closeEvent(QCloseEvent *)
{
    CrtMaster::GetInstance()->Destroy();
}
