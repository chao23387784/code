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
    treeModel = new CrtTreeModel(this);
    treeProject->setModel(treeModel);

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
    connect(btnPan,SIGNAL(toggled(bool)),this,SLOT(OnViewTransform()));
    connect(btnZoomin,SIGNAL(toggled(bool)),this,SLOT(OnViewTransform()));
    connect(btnZoomout,SIGNAL(toggled(bool)),this,SLOT(OnViewTransform()));
    //connect(cmbDevList,SIGNAL(currentIndexChanged(int)),this,SLOT(OnEditDeviceChanged(int)));
    connect(btnAddController,SIGNAL(toggled(bool)),this,SLOT(OnAddController()));
    connect(btnDeleteController,SIGNAL(toggled(bool)),this,SLOT(OnDeleteController()));
    connect(btnAddLoop,SIGNAL(toggled(bool)),this,SLOT(OnAddLoop()));
    connect(btnDeleteLoop,SIGNAL(toggled(bool)),this,SLOT(OnDeleteLoop()));
    connect(btnAddBuilding,SIGNAL(toggled(bool)),this,SLOT(OnAddBuilding()));
    connect(btnDeleteBuilding,SIGNAL(toggled(bool)),this,SLOT(OnDeleteBuilding()));
    connect(btnAddLayer,SIGNAL(toggled(bool)),this,SLOT(OnAddLayer()));
    connect(btnDeleteLayer,SIGNAL(toggled(bool)),this,SLOT(OnDeleteLayer()));
    connect(btnSetBackImage,SIGNAL(toggled(bool)),this,SLOT(OnSetBackImage()));
}

void MainWindow::InitModel()
{
    if(!treeModel)return;

    treeModel->load(CrtMaster::GetInstance()->Project());
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

}

void MainWindow::OnDeleteController()
{

}

void MainWindow::OnAddLoop()
{

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
        btnDeleteController->setVisible(true);
    }
        break;
    case 2://loop
    {
        btnAddLoop->setVisible(true);
        btnDeleteLoop->setVisible(true);
    }
        break;
    case 3://building
    {
        btnAddBuilding->setVisible(true);
        btnDeleteBuilding->setVisible(true);
    }
        break;
    case 4://layer
    {
        btnAddLayer->setVisible(true);
        btnDeleteLayer->setVisible(true);
    }
        break;
    case 5://map
    {
        btnSetBackImage->setVisible(true);
        btnPan->setVisible(true);
        btnZoomin->setVisible(true);
        btnZoomout->setVisible(true);
    }
        break;
    }
}
