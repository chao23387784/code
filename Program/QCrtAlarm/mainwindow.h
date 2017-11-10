#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QAction>
#include <QLineEdit>
#include <QTabWidget>
#include <QDateTimeEdit>
#include <QMenu>
#include <QToolButton>
#include <QMouseEvent>
#include "crttreeview.h"
#include "crttreemodel.h"
#include "crtgraphicsview.h"
#include "crtgraphicsviewcontainer.h"
#include "crtstartmenu.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initUi();
    void initConnect();

private slots:
    void slotStartMenu();
    void slotFirstAlarm();
    void slotResolution();
    void slotReset();
    void slotMute();
    void slotFirstAlarmPage();
    void slotNextAlarmPage();
    void slotFirstPage();
    void slotNextPage();
    void slotNextAlarm();
    void slotShutDown();
private:
    QAction* m_btnMute;
    QAction* m_btnReset;
    QAction* m_btnFirstAlarmPage;
    QAction* m_btnNextAlarmPage;
    QAction* m_btnFirstPage;
    QAction* m_btnNextPage;
    QAction* m_btnFirstAlarm;
    QAction* m_btnNextAlarm;
    QAction* m_btnMonitorInfo;
    QAction* m_btnRunningInfo;
    QAction* m_btnShutDown;

    QLabel* m_labInfo;
    QLabel* m_labUser;
    QLabel* m_labLevel;
    QLineEdit* m_editUser;
    QLineEdit* m_editPassword;
    QAction* m_btnLogin;
    QAction* m_btnLogout;

    QTabWidget* m_tabTree;

    CrtTreeView* m_treeProject;
    CrtTreeView* m_treeMap;
    CrtTreeModel* m_treeProjectModel;
    CrtTreeModel* m_treeMapModel;

    CrtGraphicsView* m_mapView;

    QToolButton* m_btnMenu;
    QLabel* m_labComState;
    QLabel* m_labPageInfo;
    QLabel* m_labCurPage;
    QLabel* m_labNetState;

    CrtStartMenu* m_mnStart;
    CrtGraphicsViewContainer* m_frmView;
};

#endif // MAINWINDOW_H
