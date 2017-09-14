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
#include "entitymanager.h"
#include "common.h"
#include <QStyledItemDelegate>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
	InitUi();
	InitConnect();
    resize(1250, 850);
    setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow()
{

}

void MainWindow::InitUi()
{
    QToolBar* toolBar = new QToolBar(this);

    btnCreateProj = new QAction(QIcon(":/img/new.png"),tr("Create Project"),this);
    toolBar->addAction(btnCreateProj);
    btnOpenProj = new QAction(QIcon(":/img/open.png"),tr("Open Project"),this);
    toolBar->addAction(btnOpenProj);
    btnSaveProj = new QAction(QIcon(":/img/save.png"),tr("Save Project"),this);
    toolBar->addAction(btnSaveProj);
    btnCloseProj = new QAction(QIcon(":/img/close.png"),tr("Close Project"),this);
    toolBar->addAction(btnCloseProj);
    toolBar->addSeparator();
    btnAddController = new QAction(QIcon(":/img/controlleradd.png"),tr("Add Controller"),this);
    toolBar->addAction(btnAddController);
    btnDeleteController = new QAction(QIcon(":/img/controllersub.png"),tr("Delete Controller"),this);
    toolBar->addAction(btnDeleteController);

    btnAddLoop = new QAction(QIcon(":/img/addloop.png"),tr("Add Loop"),this);
    toolBar->addAction(btnAddLoop);
    btnDeleteLoop = new QAction(QIcon(":/img/delloop.png"),tr("Delete Loop"),this);
    toolBar->addAction(btnDeleteLoop);

    btnAddDevice = new QAction(QIcon(":/img/adddev.png"),tr("Add Device"),this);
    toolBar->addAction(btnAddDevice);
    btnDeleteDevice = new QAction(QIcon(":/img/deldev.png"),tr("Delete Device"),this);
    toolBar->addAction(btnDeleteDevice);

    btnAddBuilding = new QAction(QIcon(":/img/addcatigory.png"),tr("Add Building"),this);
    toolBar->addAction(btnAddBuilding);
    btnDeleteBuilding = new QAction(QIcon(":/img/delcatigory.png"),tr("Delete Building"),this);
    toolBar->addAction(btnDeleteBuilding);
    btnAddLayer = new QAction(QIcon(":/img/addlayer.png"),tr("Add Layer"),this);
    toolBar->addAction(btnAddLayer);
    btnDeleteLayer = new QAction(QIcon(":/img/dellayer.png"),tr("Delete Layer"),this);
    toolBar->addAction(btnDeleteLayer);

    btnSetBackImage = new QAction(QIcon(":/img/map.png"),tr("Set BackImage"),this);
    btnPan = new QAction(QIcon(":/img/drag.png"),tr("Drag Map"),this);
    btnPan->toggled(true);
    btnZoomin = new QAction(QIcon(":/img/zoomin.png"),tr("Zoom In"),this);
    btnZoomout = new QAction(QIcon(":/img/zoomout.png"),tr("Zoom Out"),this);
    toolBar->addAction(btnSetBackImage);
    toolBar->addAction(btnPan);
    toolBar->addAction(btnZoomin);
    toolBar->addAction(btnZoomout);

    cmbDevList = new QComboBox();
    cmbDevList->setFixedWidth(180);

    QDir dir(":/device");
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

    actDevList = toolBar->addWidget(cmbDevList);

    addToolBar(toolBar);

    UpdateToolbarState(0);

    QDockWidget* treePanel = new QDockWidget(this);
    treePanel->setFeatures(QDockWidget::DockWidgetMovable);
    treePanel->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    tabTree = new QTabWidget(this);

    treeProject = new CrtTreeView(this);
    //treeProject->setItemDelegate(new QStyledItemDelegate());
    //treeProject->setExpandsOnDoubleClick(false);
    //treeProject->setEditTriggers(QAbstractItemView::SelectedClicked);
    tabTree->addTab(treeProject,tr("Project"));
    treeMap = new CrtTreeView(this);
    tabTree->addTab(treeMap,tr("Map"));

    //CrtMaster::GetInstance()->setProject(new CrtProject());
    treeProjectModel = new CrtTreeModel(this);
    treeProject->setModel(treeProjectModel);
    treeMapModel = new CrtTreeModel(this);
    treeMap->setModel(treeMapModel);

    treePanel->setWidget(tabTree);
    treePanel->setWindowTitle(tr("Solution"));

    tabTree->setCurrentIndex(0);

    addDockWidget(Qt::LeftDockWidgetArea,treePanel);

    QDockWidget* tbPanel = new QDockWidget(this);
    tbPanel->setFeatures(QDockWidget::DockWidgetMovable);
    tbPanel->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    tbProp = new QTableWidget(this);
    tbPanel->setWidget(tbProp);
    tbPanel->setWindowTitle(tr("Property"));

    addDockWidget(Qt::RightDockWidgetArea,tbPanel);

    mapView = new CrtView(this);
    mapScene = new CrtScene(this);
    mapView->setBackgroundBrush(Qt::white);
    mapView->setScene(mapScene);
    map = new CrtBackground;
    mapScene->addItem(map);
    mapScene->setBackground(map);

    setCentralWidget(mapView);
}

void MainWindow::InitConnect()
{
    connect(tabTree,SIGNAL(currentChanged(int)),this,SLOT(OnTabChanged(int)));
    connect(btnCreateProj,SIGNAL(triggered(bool)),this,SLOT(OnCreateProject()));
    connect(btnOpenProj,SIGNAL(triggered(bool)),this,SLOT(OnOpenProject()));
    connect(btnSaveProj,SIGNAL(triggered(bool)),this,SLOT(OnSaveProject()));
    connect(btnCloseProj,SIGNAL(triggered(bool)),this,SLOT(OnCloseProject()));
    connect(btnPan,SIGNAL(triggered(bool)),this,SLOT(OnViewTransform()));
    connect(btnZoomin,SIGNAL(triggered(bool)),this,SLOT(OnViewTransform()));
    connect(btnZoomout,SIGNAL(triggered(bool)),this,SLOT(OnViewTransform()));
    //connect(cmbDevList,SIGNAL(currentIndexChanged(int)),this,SLOT(OnEditDeviceChanged(int)));
    connect(btnAddController,SIGNAL(triggered(bool)),this,SLOT(OnAddController()));
    connect(btnDeleteController,SIGNAL(triggered(bool)),this,SLOT(OnDeleteController()));
    connect(btnAddLoop,SIGNAL(triggered(bool)),this,SLOT(OnAddLoop()));
    connect(btnDeleteLoop,SIGNAL(triggered(bool)),this,SLOT(OnDeleteLoop()));
    connect(btnAddDevice,SIGNAL(triggered(bool)),this,SLOT(OnAddDevice()));
    connect(btnDeleteDevice,SIGNAL(triggered(bool)),this,SLOT(OnDeleteDevice()));
    connect(btnAddBuilding,SIGNAL(triggered(bool)),this,SLOT(OnAddBuilding()));
    connect(btnDeleteBuilding,SIGNAL(triggered(bool)),this,SLOT(OnDeleteBuilding()));
    connect(btnAddLayer,SIGNAL(triggered(bool)),this,SLOT(OnAddLayer()));
    connect(btnDeleteLayer,SIGNAL(triggered(bool)),this,SLOT(OnDeleteLayer()));
    connect(btnSetBackImage,SIGNAL(triggered(bool)),this,SLOT(OnSetBackImage()));
    connect(treeProject,SIGNAL(clicked(QModelIndex)),this,SLOT(OnProjectItemChanged()));
    connect(treeMap,SIGNAL(clicked(QModelIndex)),this,SLOT(OnMapItemChanged()));
}

void MainWindow::InitModel()
{
    if(!treeProjectModel)return;

    treeProjectModel->load(CrtMaster::GetInstance()->Project());
    treeMapModel->load(CrtMaster::GetInstance()->Project(),1);
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
    CrtMaster::GetInstance()->setManager(new EntityManager());
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
    CrtMaster::GetInstance()->setManager(new EntityManager());
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
    treeMapModel->unload();
    treeProjectModel->unload();
    CrtMaster::GetInstance()->setProject(NULL);
    CrtMaster::GetInstance()->setManager(NULL);
}

void MainWindow::OnViewTransform()
{
    if(btnPan->isChecked())
    {
        mapView->setViewMode(Pan);
    }
    else if(btnZoomin->isChecked() || btnZoomout->isChecked())
    {
        mapView->setViewMode(Zoomin);
    }
    else
    {
        mapView->setViewMode(None);
    }
}

void MainWindow::OnAddController()
{
    QModelIndex index = treeProject->currentIndex();
    if(!index.isValid())return;

    int id = CrtMaster::GetInstance()->Project()->getAvaliableControllerID();
    if(id == -1)
    {
        QMessageBox::information(this,tr("warning"),tr("Upper limit reached!"));
        return;
    }
    CrtController* controller = new CrtController(CrtMaster::GetInstance()->Project());
    //this id is not correct
    controller->setID(id);
    controller->setName(QString(tr("NT-Controller%1")).arg(id));
    CrtMaster::GetInstance()->Project()->m_lstController.append(controller);

    treeProject->insertItem(controller,index);
}

void MainWindow::OnDeleteController()
{
    QModelIndex index = treeProject->currentIndex();
    if(!index.isValid())return;
    CrtTreeItem* item = (CrtTreeItem*)index.internalPointer();
    CrtController* controller = (CrtController*)item->Data();
    CrtProject* proj = (CrtProject*)controller->Parent();

    treeProject->deleteItem(index);

    proj->m_lstController.removeOne(controller);
    SAFE_DELETE(controller);
}

void MainWindow::OnAddLoop()
{
    QModelIndex index = treeProject->currentIndex();
    if(!index.isValid())return;

    CrtTreeItem* parent = (CrtTreeItem*)index.internalPointer();
    CrtController* controller = (CrtController*)parent->Data();

    int id = controller->getAvaliableLoopID();
    if(id == -1)
    {
        QMessageBox::information(this,tr("warning"),tr("Upper limit reached!"));
        return;
    }

    CrtLoop* loop = new CrtLoop(controller);
    //this id is not correct
    loop->setID(id);
    loop->setName(QString(tr("NT-Loop%1")).arg(id));
    controller->m_lstLoop.append(loop);

    treeProject->insertItem(loop,index);
}

void MainWindow::OnDeleteLoop()
{
    QModelIndex index = treeProject->currentIndex();
    if(!index.isValid())return;
    CrtTreeItem* item = (CrtTreeItem*)index.internalPointer();
    CrtLoop* loop = (CrtLoop*)item->Data();
    CrtController* controller = (CrtController*)loop->Parent();

    treeProject->deleteItem(index);

    controller->m_lstLoop.removeOne(loop);
    SAFE_DELETE(loop);
}

void MainWindow::OnAddDevice()
{
    QModelIndex index = treeProject->currentIndex();
    if(!index.isValid())return;
    CrtTreeItem* parent = (CrtTreeItem*)index.internalPointer();
    CrtLoop* loop = (CrtLoop*)parent->Data();

    int id = loop->getAvaliableDeviceID();
    if(id == -1)
    {
        QMessageBox::information(this,tr("warning"),tr("Upper limit reached!"));
        return;
    }

    CrtDevice* device = new CrtDevice(loop);
    //this id is not correct
    device->setID(id);
    device->setName(QString(tr("NT-Device%1")).arg(id));
    device->setDeviceType(cmbDevList->currentText());
    loop->m_lstDevice.append(device);

    treeProject->insertItem(device,index);
}

void MainWindow::OnDeleteDevice()
{
    QModelIndex index = treeProject->currentIndex();
    if(!index.isValid())return;
    CrtTreeItem* item = (CrtTreeItem*)index.internalPointer();
    CrtDevice* device = (CrtDevice*)item->Data();
    CrtLoop* loop = (CrtLoop*)device->Parent();

    treeProject->deleteItem(index);

    loop->m_lstDevice.removeOne(device);
    SAFE_DELETE(device);
}

void MainWindow::OnAddBuilding()
{
    QModelIndex index = treeMap->currentIndex();
    if(!index.isValid())return;

    int id = CrtMaster::GetInstance()->Project()->getAvaliableBuildingID();
    if(id == -1)
    {
        QMessageBox::information(this,tr("warning"),tr("Upper limit reached!"));
        return;
    }

    CrtBuilding* building = new CrtBuilding(CrtMaster::GetInstance()->Project());
    //this id is not correct
    building->setID(id);
    building->setName(QString(tr("NT-Building%1")).arg(id));
    CrtMaster::GetInstance()->Project()->m_lstBuilding.append(building);

    treeMap->insertItem(building,index);
}

void MainWindow::OnDeleteBuilding()
{
    QModelIndex index = treeMap->currentIndex();
    if(!index.isValid())return;
    CrtTreeItem* item = (CrtTreeItem*)index.internalPointer();
    CrtBuilding* building = (CrtBuilding*)item->Data();
    CrtProject* proj = (CrtProject*)building->Parent();

    treeMap->deleteItem(index);

    proj->m_lstBuilding.removeOne(building);
    SAFE_DELETE(building);
}

void MainWindow::OnAddLayer()
{
    QModelIndex index = treeMap->currentIndex();
    if(!index.isValid())return;
    CrtTreeItem* parent = (CrtTreeItem*)index.internalPointer();
    CrtBuilding* building = (CrtBuilding*)parent->Data();

    int id = building->getAvaliableLayerID();
    if(id == -1)
    {
        QMessageBox::information(this,tr("warning"),tr("Upper limit reached!"));
        return;
    }

    CrtLayer* layer = new CrtLayer(building);
    //this id is not correct
    layer->setID(id);
    layer->setName(QString(tr("NT-Layer%1")).arg(id));
    building->m_lstLayer.append(layer);

    treeMap->insertItem(layer,index);
}

void MainWindow::OnDeleteLayer()
{
    QModelIndex index = treeMap->currentIndex();
    if(!index.isValid())return;
    CrtTreeItem* item = (CrtTreeItem*)index.internalPointer();
    CrtLayer* layer = (CrtLayer*)item->Data();
    CrtBuilding* building = (CrtBuilding*)layer->Parent();

    treeMap->deleteItem(index);

    building->m_lstLayer.removeOne(layer);
    SAFE_DELETE(layer);
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

    //load file
    map->setWmfFile(path);
    mapView->setSceneRect(map->boundingRect());
}

void MainWindow::OnProjectItemChanged()
{
    QModelIndex index = treeProject->currentIndex();
    if(!index.isValid())return;
    CrtTreeItem* item = (CrtTreeItem*)index.internalPointer();
    if(item)
    {
        if(!item->Data()->Type().compare("project"))
           emit UpdateToolbarState(1);
        else if(!item->Data()->Type().compare("controller"))
            emit UpdateToolbarState(2);
        else if(!item->Data()->Type().compare("loop"))
            emit UpdateToolbarState(6);
        else if(!item->Data()->Type().compare("device"))
            emit UpdateToolbarState(7);
        else
            emit UpdateToolbarState(0);
    }
}

void MainWindow::OnMapItemChanged()
{
    QModelIndex index = treeMap->currentIndex();
    if(!index.isValid())return;
    CrtTreeItem* item = (CrtTreeItem*)index.internalPointer();
    if(item)
    {
        if(!item->Data()->Type().compare("project"))
           emit UpdateToolbarState(3);
        else if(!item->Data()->Type().compare("building"))
            emit UpdateToolbarState(4);
        else if(!item->Data()->Type().compare("layer"))
            emit UpdateToolbarState(5);
        else
            emit UpdateToolbarState(0);
    }
}

void MainWindow::OnTabChanged(int index)
{
    if(index == 0)
    {
        emit OnProjectItemChanged();
    }
    else if(index == 1)
    {
        emit OnMapItemChanged();
    }
}

void MainWindow::OnEditDeviceChanged(int nIndex)
{
    mapView->setViewMode(Edit);
    mapView->setEditDevicePath(cmbDevList->itemData(nIndex).toString());
}

void MainWindow::UpdateToolbarState(int state)
{
    foreach(QAction* btn,QList<QAction*>()<<btnCreateProj<<btnOpenProj<<btnSaveProj
            <<btnCloseProj<<btnAddController<<btnDeleteController<<btnAddLoop
            <<btnDeleteLoop<<btnAddDevice<<btnDeleteDevice<<btnAddBuilding<<btnDeleteBuilding<<btnAddLayer
            <<btnDeleteLayer<<btnSetBackImage<<btnPan<<btnZoomin<<btnZoomout<<actDevList)
    {
        btn->setVisible(false);
    }


    btnCreateProj->setVisible(true);
    btnOpenProj->setVisible(true);
    btnSaveProj->setVisible(true);
    btnCloseProj->setVisible(true);

    switch(state)
    {
    case 0://project
    {
        btnCreateProj->setVisible(true);
        btnOpenProj->setVisible(true);
        btnSaveProj->setVisible(true);
        btnCloseProj->setVisible(true);
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
        btnSetBackImage->setVisible(true);
        btnPan->setVisible(true);
        btnZoomin->setVisible(true);
        btnZoomout->setVisible(true);
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

void MainWindow::closeEvent(QCloseEvent *)
{
    CrtMaster::GetInstance()->Destroy();
}
