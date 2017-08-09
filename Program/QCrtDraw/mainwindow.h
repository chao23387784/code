#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>
#include <QTableWidget>
#include "crtscene.h"
#include "crtview.h"
#include <QAction>
#include "crtbackground.h"
#include <QComboBox>
#include "crttreemodel.h"
#include "crttreeview.h"

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
    void OnDeleteController();
    void OnAddLoop();
    void OnDeleteLoop();
    void OnAddBuilding();
    void OnDeleteBuilding();
    void OnAddLayer();
    void OnDeleteLayer();
    void OnSetBackImage();
    void OnProjectItemChanged();
    void OnMapItemChanged();
public slots:
    void OnEditDeviceChanged(int nIndex);
    void UpdateToolbarState(int state);
protected:
    void closeEvent(QCloseEvent *);
private:
    CrtTreeView* treeProject;
    CrtTreeView* treeMap;
    CrtTreeModel* treeProjectModel;
    CrtTreeModel* treeMapModel;
	QTableWidget* tbProp;
    CrtView* mapView;
    CrtScene* mapScene;
    CrtBackground* map;

    QAction* btnCreateProj;
    QAction* btnOpenProj;
    QAction* btnSaveProj;
    QAction* btnCloseProj;
    QAction* btnAddController;
    QAction* btnDeleteController;
    QAction* btnAddLoop;
    QAction* btnDeleteLoop;
    QAction* btnAddBuilding;
    QAction* btnDeleteBuilding;
    QAction* btnAddLayer;
    QAction* btnDeleteLayer;
    //QAction* btnAddDevice;
    //QAction* btnDeleteDevice;

    QComboBox* cmbDevList;

    QAction* btnSetBackImage;
    QAction* btnPan;
    QAction* btnZoomin;
    QAction* btnZoomout;
};

#endif // MAINWINDOW_H
