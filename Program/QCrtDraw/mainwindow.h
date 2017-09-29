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
#include "crtpropertycontianer.h"
#include "crtgraphicsviewcontainer.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
	void InitUi();
	void InitConnect();
    void InitModel();
    void loadProject(QString path = "");
private slots:
    void OnOpenProject();
    void OnCreateProject();
    void OnSaveProject();
    void OnCloseProject();
    void OnViewTransform();
    void OnAddController();
    void OnAddControllers();
    void OnDeleteController();
    void OnAddLoop();
    void OnAddLoops();
    void OnDeleteLoop();
    void OnAddDevice();
    void OnAddDevices();
    void OnDeleteDevice();
    void OnAddBuilding();
    void OnAddBuildings();
    void OnDeleteBuilding();
    void OnAddLayer();
    void OnAddLayers();
    void OnDeleteLayer();
    void OnSetBackImage();
    void OnProjectItemChanged();
    void OnMapItemChanged();
    void OnSetDevice();
public slots:
    void UpdateToolbarProjectState(int state);
    void UpdateToolbarMapState(int state);
    void UpdateCurrentVisibleTab(int index);//0 property,1 view
protected:
    void closeEvent(QCloseEvent *);
private:
    QTabWidget* tabMain;
    CrtPropertyContianer* frmProperty;
    CrtGraphicsViewContainer* frmView;

    CrtTreeView* treeProject;
    CrtTreeView* treeMap;
    CrtTreeModel* treeProjectModel;
    CrtTreeModel* treeMapModel;
    CrtGraphicsView* mapView;
    QDockWidget* panelProject;
    QDockWidget* panelMap;
    QDockWidget* panelDevice;

    QAction* btnCreateProj;
    QAction* btnOpenProj;
    QAction* btnSaveProj;
    QAction* btnCloseProj;
    CrtTwoWayToolButton* crtBtnAddController;
    QAction* btnAddController;
    QAction* btnDeleteController;
    CrtTwoWayToolButton* crtBtnAddLoop;
    QAction* btnAddLoop;
    QAction* btnDeleteLoop;
    CrtTwoWayToolButton* crtBtnAddBuilding;
    QAction* btnAddBuilding;
    QAction* btnDeleteBuilding;
    CrtTwoWayToolButton* crtBtnAddLayer;
    QAction* btnAddLayer;
    QAction* btnDeleteLayer;
    CrtTwoWayToolButton* crtBtnAddDevice;
    QAction* btnAddDevice;
    QAction* btnDeleteDevice;

    QComboBox* cmbDevList;
    QComboBox* cmbCtrlList;
    QAction* actDevList;
    QAction* actCtrlList;

    QAction* btnSetBackImage;
    QToolButton* tbPan;
    QToolButton* tbSetDevice;
    QAction* btnPan;
    QAction* btnZoomin;
    QAction* btnZoomout;
    QAction* btnSetDevice;
};

#endif // MAINWINDOW_H
