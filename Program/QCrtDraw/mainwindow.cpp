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

    btnAddLoop = new QAction(QIcon(":/img/add.png"),tr("Add Loop"),this);
    toolBar->addAction(btnAddLoop);
    btnDeleteLoop = new QAction(QIcon(":/img/sub.png"),tr("Delete Loop"),this);
    toolBar->addAction(btnDeleteLoop);

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

    //toolBar->addWidget(cmbDevList);
    addToolBar(toolBar);

    UpdateToolbarState(0);

    QDockWidget* treePanel = new QDockWidget(this);
    treePanel->setFeatures(QDockWidget::DockWidgetMovable);
    treePanel->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    QTabWidget* tabTree = new QTabWidget(this);

    treeProject = new QTreeView(this);
    tabTree->addTab(treeProject,tr("Project"));
    treeMap = new QTreeView(this);
    tabTree->addTab(treeMap,tr("Map"));

    CrtMaster::GetInstance()->setProject(new CrtProject());
    treeProjectModel = new CrtTreeModel(this);
    treeProject->setModel(treeProjectModel);
    treeMapModel = new CrtTreeModel(this);
    treeMap->setModel(treeMapModel);


    CrtMaster::GetInstance()->setManager(new EntityManager());

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

    InitModel();
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

    loadProject(path);
}

void MainWindow::OnCreateProject()
{
    if(!CrtMaster::GetInstance()->Project())
    {
        QMessageBox::information(this,tr("warning"),tr("close current project first!"));
        return;
    }
    CrtProject* proj = new CrtProject();
    proj->setID(/*getid*/0);
    proj->setName("project1");
    CrtMaster::GetInstance()->setProject(proj);
}

void MainWindow::OnSaveProject()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Save Project File"),
                                                QDir::currentPath(),
                                                tr("SQLite Database File (*.db)"));
    if(QFileInfo(path).exists())
    {
        QMessageBox::information(this,tr("warning"),tr("file exists!"));
        return;
    }

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
    //model clear
    //entity clear
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
    CrtTreeItem* parent = (CrtTreeItem*)index.internalPointer();
    CrtProject* proj = (CrtProject*)parent->Data();
    if(parent && proj)
    {
        CrtController* controller = new CrtController(proj);
        //this id is not correct
        controller->setID(CrtMaster::GetInstance()->Manager()->getAvaliableNumber("ControllerTb"));
        controller->setName(tr("NT-Controller"));
        controller->setStauts(New);
        proj->m_lstController.append(controller);

        CrtTreeItem* item = new CrtTreeItem();
        item->setParent(parent);
        item->setData(controller);
        item->setColumn(0);
        parent->addChild(item);
        item->setRow(parent->indexOf(item));

        treeProjectModel->reset();
        treeProject->expand(index);
        treeProject->setCurrentIndex(index);

        proj->m_lstModifyObjects.append(controller);
    }
}

void MainWindow::OnDeleteController()
{
    QModelIndex index = treeProject->currentIndex();
    if(!index.isValid())return;
    CrtTreeItem* item = (CrtTreeItem*)index.internalPointer();
    if(!item)return;
    CrtController* controller = (CrtController*)item->Data();
    CrtProject* proj = (CrtProject*)controller->Parent();
    CrtTreeItem* parent = item->Parent();
    if(!parent)return;
    parent->removeChild(parent->indexOf(item));

    treeProjectModel->reset();
    treeProject->setCurrentIndex(QModelIndex());

    proj->m_lstController.removeOne(controller);
    controller->setStauts(Delete);
    proj->m_lstModifyObjects.append(controller);
}

void MainWindow::OnAddLoop()
{
    QModelIndex index = treeProject->currentIndex();
    if(!index.isValid())return;
    CrtTreeItem* parent = (CrtTreeItem*)index.internalPointer();
    CrtController* controller = (CrtController*)parent->Data();
    if(parent && controller)
    {
        CrtLoop* loop = new CrtLoop(controller);
        //this id is not correct
        loop->setID(CrtMaster::GetInstance()->Manager()->getAvaliableNumber("LoopTb"));
        loop->setName(tr("NT-Loop"));
        loop->setStauts(New);
        controller->m_lstLoop.append(loop);

        CrtTreeItem* item = new CrtTreeItem();
        item->setParent(parent);
        item->setData(loop);
        item->setColumn(0);
        parent->addChild(item);
        item->setRow(parent->indexOf(item));

        treeProjectModel->reset();
        treeProject->expand(index);
        treeProject->setCurrentIndex(index);

        CrtMaster::GetInstance()->Project()->m_lstModifyObjects.append(loop);
    }
}

void MainWindow::OnDeleteLoop()
{

}

void MainWindow::OnAddBuilding()
{

}

void MainWindow::OnDeleteBuilding()
{

}

void MainWindow::OnAddLayer()
{

}

void MainWindow::OnDeleteLayer()
{

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

void MainWindow::OnEditDeviceChanged(int nIndex)
{
    mapView->setViewMode(Edit);
    mapView->setEditDevicePath(cmbDevList->itemData(nIndex).toString());
}

void MainWindow::UpdateToolbarState(int state)
{
    foreach(QAction* btn,QList<QAction*>()<<btnCreateProj<<btnOpenProj<<btnSaveProj
            <<btnCloseProj<<btnAddController<<btnDeleteController<<btnAddLoop
            <<btnDeleteLoop<<btnAddBuilding<<btnDeleteBuilding<<btnAddLayer
            <<btnDeleteLayer<<btnSetBackImage<<btnPan<<btnZoomin<<btnZoomout)
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
        btnDeleteLoop->setVisible(true);
    }
    }
}

void MainWindow::closeEvent(QCloseEvent *)
{
    CrtMaster::GetInstance()->Destroy();
}
