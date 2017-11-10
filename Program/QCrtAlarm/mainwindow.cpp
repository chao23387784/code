#include "mainwindow.h"
#include <QToolBar>
#include <QStatusBar>
#include <QPalette>
#include <QLabel>
#include <QFont>
#include <QLayout>
#include <QIcon>
#include <QValidator>
#include <QDockWidget>
#include <QColor>
#include <QDebug>
#include "crtmaster.h"
#include "qclock.h"
#include "crtgraphicsviewcontainer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowState(Qt::WindowFullScreen);
    initUi();
    initConnect();
}

MainWindow::~MainWindow()
{

}

void MainWindow::initUi()
{
    QDockWidget wid;
    /////////////////////////top toolbar//////////////////////////////////////
    QToolBar* toolBar = new QToolBar(this);
    toolBar->setFixedHeight(80);
    toolBar->setMovable(false);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
     addToolBar(toolBar);

    QLabel* labTitle = new QLabel("NEAT\r\nNEAT Corp",this);
    labTitle->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    labTitle->setFont(QFont("Aria",20,10));
    labTitle->setFixedWidth(200);
    toolBar->addWidget(labTitle);

    m_btnReset = new QAction(QIcon(":/img/reset.png"),tr("Reset"),this);
    toolBar->addAction(m_btnReset);
    m_btnMute = new QAction(QIcon(":/img/play.png"),tr("Mute"),this);
    toolBar->addAction(m_btnMute);
    m_btnFirstAlarmPage = new QAction(QIcon(":/img/markalarmpoint.png"),tr("First Fire\r\nPage"),this);
    toolBar->addAction(m_btnFirstAlarmPage);
    m_btnNextAlarmPage = new QAction(QIcon(":/img/alarmpoint.png"),tr("Next Fire\r\nPage"),this);
    toolBar->addAction(m_btnNextAlarmPage);
    m_btnFirstPage = new QAction(QIcon(":/img/map.png"),tr("First Page"),this);
    toolBar->addAction(m_btnFirstPage);
    m_btnNextPage = new QAction(QIcon(":/img/design.png"),tr("Next Page"),this);
    toolBar->addAction(m_btnNextPage);
    m_btnFirstAlarm = new QAction(QIcon(":/img/simulatefirstfire96.png"),tr("First Alarm"),this);
    toolBar->addAction(m_btnFirstAlarm);
    m_btnNextAlarm = new QAction(QIcon(":/img/simulatefire96.png"),tr("Next Alarm"),this);
    toolBar->addAction(m_btnNextAlarm);
    m_btnMonitorInfo = new QAction(QIcon(":/img/allregedit.png"),tr("Monitoring\r\nInformation"),this);
    toolBar->addAction(m_btnMonitorInfo);
    m_btnRunningInfo = new QAction(QIcon(":/img/controllertest.png"),tr("Running\r\nInformation"),this);
    toolBar->addAction(m_btnRunningInfo);
    m_btnShutDown = new QAction(QIcon(":/img/shutdd.jpg"),tr("Shutdown"),this);
    toolBar->addAction(m_btnShutDown);

    QWidget *spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolBar->addWidget(spacer);

    QWidget* widLogin = new QWidget(this);
    QGridLayout* layoutLogin = new QGridLayout(this);
    QLabel* labUser = new QLabel(tr("User:"),this);
    m_labInfo = new QLabel(tr("Password:"),this);
    m_editUser = new QLineEdit(this);
    m_editUser->setMaxLength(256);
    m_editPassword = new QLineEdit(this);
    m_editPassword->setMaxLength(256);
    m_editPassword->setEchoMode(QLineEdit::Password);
    m_labUser = new QLabel(this);
    m_labLevel = new QLabel(this);
    layoutLogin->addWidget(labUser,0,0,1,1);
    layoutLogin->addWidget(m_editUser,0,1,1,1);
    layoutLogin->addWidget(m_labUser,0,2,1,1);
    layoutLogin->addWidget(m_labInfo,1,0,1,1);
    layoutLogin->addWidget(m_editPassword,1,1,1,1);
    layoutLogin->addWidget(m_labLevel,1,2,1,1);
    widLogin->setLayout(layoutLogin);
    widLogin->setFixedWidth(250);
    toolBar->addWidget(widLogin);

    m_btnLogin = new QAction(QIcon(":/img/user.ico"),tr("Login"),this);
    toolBar->addAction(m_btnLogin);
    m_btnLogout = new QAction(QIcon(":/img/escape_exit.png"),tr("Logout"),this);
    toolBar->addAction(m_btnLogout);
    ///////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////central widget////////////////////////////////////
    m_tabTree = new QTabWidget(this);
    //m_tabTree->setFixedWidth(250);

    m_treeProject = new CrtTreeView(this);
    m_treeProject->setHeaderHidden(true);
    CrtMaster::getInstance()->setPtojectTreeView(m_treeProject);
    m_tabTree->addTab(m_treeProject,tr("Project"));

    m_treeMap = new CrtTreeView(this);
    m_treeMap->setHeaderHidden(true);
    CrtMaster::getInstance()->setMapTreeView(m_treeMap);
    m_tabTree->addTab(m_treeMap,tr("Desing"));

    m_treeProjectModel = new CrtTreeModel(this);
    m_treeProject->setModel(m_treeProjectModel);
    m_treeProject->setSelectionModel(new QItemSelectionModel());
    m_treeMapModel = new CrtTreeModel(this,1);
    m_treeMap->setModel(m_treeMapModel);
    m_treeMap->setSelectionModel(new QItemSelectionModel());

    m_mapView = new CrtGraphicsView(this);
    m_mapView->setBackgroundBrush(Qt::black);
    CrtMaster::getInstance()->setCrtGraphicsView(m_mapView);

    m_frmView = new CrtGraphicsViewContainer(m_mapView,this);

    QDockWidget* widTree = new QDockWidget(this);
    widTree->setWidget(m_tabTree);
    widTree->setTitleBarWidget(new QWidget(this));
    widTree->setFeatures(QDockWidget::NoDockWidgetFeatures);
    widTree->setAllowedAreas(Qt::LeftDockWidgetArea);
    widTree->setMaximumWidth(500);

    addDockWidget(Qt::LeftDockWidgetArea,widTree);

    setCentralWidget(m_frmView);
    ///////////////////////////////////////////////////////////////////////////////////////////////

    /////////////////////////////////status bar///////////////////////////////////////////////////
    statusBar()->setFixedHeight(30);

    m_mnStart = new CrtStartMenu(this);
    m_btnMenu = new QToolButton(this);
    m_btnMenu->setText(tr("NEAT"));
    m_btnMenu->setFont(QFont("Aria",20,10));
    m_btnMenu->setFixedHeight(25);
    m_btnMenu->setPopupMode(QToolButton::InstantPopup);
    m_btnMenu->setFocusPolicy(Qt::NoFocus);
    //m_btnMenu->setMenu(m_mnStart);
    //m_btnMenu->setPopupMode(QToolButton::InstantPopup);
    statusBar()->addWidget(m_btnMenu);

    QLabel* labComState = new QLabel(this);
    labComState->setPixmap(QPixmap(":/img/connect.ico"));
    statusBar()->addWidget(labComState);

    m_labComState = new QLabel(tr("Normal Communication"),this);
    statusBar()->addWidget(m_labComState,1);

    QLabel* labPageInfo = new QLabel(this);
    labPageInfo->setPixmap(QPixmap(":/img/status.ico"));
    statusBar()->addWidget(labPageInfo);

    m_labPageInfo = new QLabel(tr("A total of 0 alarm pages"));
    statusBar()->addWidget(m_labPageInfo,1);

    QLabel* labCurPage = new QLabel(this);
    labCurPage->setPixmap(QPixmap(":/img/Panel.ico"));
    statusBar()->addWidget(labCurPage);

    m_labCurPage = new QLabel(tr("No alarm page"));
    statusBar()->addWidget(m_labCurPage,1);

    QLabel* labNetState = new QLabel(this);
    labNetState->setPixmap(QPixmap(":/img/12.ico"));
    statusBar()->addWidget(labNetState);

    m_labNetState = new QLabel(tr("Connecting monitoring center..."),this);
    statusBar()->addWidget(m_labNetState,1);

    QLabel* labClock = new QLabel(this);
    labClock->setPixmap(QPixmap(":/img/clock.bmp"));
    statusBar()->addWidget(labClock);

    QClock* clk = new QClock(this);
    statusBar()->addWidget(clk,1);    
    /////////////////////////////////////////////////////////////////////////////////////
}

void MainWindow::initConnect()
{
    connect(m_btnMenu,SIGNAL(clicked(bool)),this,SLOT(slotStartMenu()));
    connect(m_btnReset,SIGNAL(triggered(bool)),this,SLOT(slotReset()));
    connect(m_btnMute,SIGNAL(triggered(bool)),this,SLOT(slotMute()));
    connect(m_btnShutDown,SIGNAL(triggered(bool)),this,SLOT(slotShutDown()));
    connect(m_btnFirstAlarm,SIGNAL(triggered(bool)),this,SLOT(slotFirstAlarm()));
    connect(m_btnFirstAlarmPage,SIGNAL(triggered(bool)),this,SLOT(slotFirstAlarmPage()));
    connect(m_btnNextAlarmPage,SIGNAL(triggered(bool)),this,SLOT(slotNextAlarmPage()));
    connect(m_btnNextAlarm,SIGNAL(triggered(bool)),this,SLOT(slotNextAlarm()));
    connect(m_btnFirstPage,SIGNAL(triggered(bool)),this,SLOT(slotFirstPage()));
    connect(m_btnNextPage,SIGNAL(triggered(bool)),this,SLOT(slotNextPage()));
}

void MainWindow::slotStartMenu()
{
    QPoint pt = statusBar()->mapToGlobal(QPoint(0,0));
    m_mnStart->popup(QPoint(pt.x(),pt.y() - 120));
}

void MainWindow::slotFirstAlarm()
{

}

void MainWindow::slotResolution()
{

}

void MainWindow::slotReset()
{

}

void MainWindow::slotMute()
{
    m_btnMute->setIcon(QIcon(":/img/mute.png"));
}

void MainWindow::slotFirstAlarmPage()
{

}

void MainWindow::slotNextAlarmPage()
{

}

void MainWindow::slotFirstPage()
{

}

void MainWindow::slotNextPage()
{

}

void MainWindow::slotNextAlarm()
{

}

void MainWindow::slotShutDown()
{

}
