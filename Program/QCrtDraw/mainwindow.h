#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>
#include <QTableView>
#include "crtgraphicsview.h"
#include <QAction>
#include <QComboBox>
#include "crttreemodel.h"
#include "crttreeview.h"
#include <QTabWidget>
#include "crttwowaypushbutton.h"
#include <QToolButton>
#include <QDockWidget>
#include <QMenu>
#include "crtpropertycontianer.h"
#include "crtgraphicsviewcontainer.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initUi();
    void initConnect();
    void initModel();
    void loadProject(QString path = "");
private slots:
    void slotOpenProject();
    void slotCreateProject();
    void slotSaveProject();
    void slotCloseProject();
    void slotViewTransform();
    void slotAddController();
    void slotAddControllers();
    void slotDeleteController();
    void slotAddLoop();
    void slotAddLoops();
    void slotDeleteLoop();
    void slotAddDevice();
    void slotAddDevices();
    void slotDeleteDevice();
    void slotAddBuilding();
    void slotAddBuildings();
    void slotDeleteBuilding();
    void slotAddLayer();
    void slotAddLayers();
    void slotDeleteLayer();
    void slotSetBackImage();
    void slotProjectItemChanged();
    void slotMapItemChanged();
    void slotSetDevice();
    void slotCustomSize(QAction* action);
public slots:
    void slotUpdateToolbarProjectState(int state);
    void slotUpdateToolbarMapState(int state);
    void slotUpdateCurrentVisibleTab(int index);//0 property,1 view
protected:
    void closeEvent(QCloseEvent *);
private:
    QTabWidget* m_tabMain;
    CrtPropertyContianer* m_frmProperty;
    CrtGraphicsViewContainer* m_frmView;

    CrtTreeView* m_treeProject;
    CrtTreeView* m_treeMap;
    CrtTreeModel* m_treeProjectModel;
    CrtTreeModel* m_treeMapModel;
    CrtGraphicsView* m_mapView;
    QDockWidget* m_panelProject;
    QDockWidget* m_panelMap;
    QDockWidget* m_panelDevice;

    QAction* m_btnCreateProj;
    QAction* m_btnOpenProj;
    QAction* m_btnSaveProj;
    QAction* m_btnCloseProj;
    CrtTwoWayToolButton* m_crtBtnAddController;
    QAction* m_btnAddController;
    QAction* m_btnDeleteController;
    CrtTwoWayToolButton* m_crtBtnAddLoop;
    QAction* m_btnAddLoop;
    QAction* m_btnDeleteLoop;
    CrtTwoWayToolButton* m_crtBtnAddBuilding;
    QAction* m_btnAddBuilding;
    QAction* m_btnDeleteBuilding;
    CrtTwoWayToolButton* m_crtBtnAddLayer;
    QAction* m_btnAddLayer;
    QAction* m_btnDeleteLayer;
    CrtTwoWayToolButton* m_crtBtnAddDevice;
    QAction* m_btnAddDevice;
    QAction* m_btnDeleteDevice;

    QComboBox* m_cmbDevList;
    QComboBox* m_cmbCtrlList;
    QAction* m_actDevList;
    QAction* m_actCtrlList;

    QAction* m_btnSetBackImage;
    QToolButton* m_tbPan;
    QToolButton* m_tbSetDevice;
    QToolButton* m_tbCustomSize;
    QMenu* m_customSizeMenu;
    QAction* m_btnPan;
    QAction* m_btnZoomin;
    QAction* m_btnZoomout;
    QAction* m_btnSetDevice;
};

#endif // MAINWINDOW_H
