#ifndef CRTMASTER_H
#define CRTMASTER_H

#include <QHash>
#include "crtproject.h"
#include "datamanager.h"
#include <QIcon>
#include <QStringList>
#include "crttreeview.h"
#include "crtgraphicsview.h"
#include "crtsetdevicedlg.h"
//#include "crtwelcomwidget.h"

class CrtMaster
{
public:
    static CrtMaster* GetInstance();
    void Destroy();
    void setProject(CrtProject* proj);
    CrtProject* Project(){return project;}
    void setManager(DataManager* manager);
    DataManager* Manager(){return manager;}
    void initDeviceIcon();
    void initTreeIcon();
    void initSystemType();
    void initControllerType();
    QIcon* DeviceIcon(QString strDeviceType);
    QIcon* TreeIcon(QString strTreeIconType);
    const QStringList* ControllerType();
    const QStringList* SystemType();
    void ClearDeviceIconHashTable();
    void clearTreeIconHashTable();
    void setPtojectTreeView(CrtTreeView* view);
    CrtTreeView* ProjectTreeView();
    void setMapTreeView(CrtTreeView* view);
    CrtTreeView* MapTreeView();
    void setCrtGraphicsView(CrtGraphicsView* view);
    CrtGraphicsView *getCrtGraphicsView();
    void setCrtSetDeviceDlg(CrtSetDeviceDlg* dlg);
    CrtSetDeviceDlg* getCrtSetDeviceDlg();
   // void setWelcomeWidget(CrtWelcomWidget* welcom);
    //CrtWelcomWidget* WelcomWidget();

    CrtObject* findProjectObject(int project_id,int controller_id);
    CrtObject* findProjectObject(int project_id,int controller_id,int loop_id);
    CrtObject* findProjectObject(int project_id,int controller_id,int loop_id,int device_id);
    CrtObject* findMapObject(int project_id,int building_id);
    CrtObject* findMapObject(int project_id,int building_id,int layer_id);
    CrtObject* findMapObject(int project_id,int building_id,int layer_id,int device_id);
private:
    explicit CrtMaster();
    ~CrtMaster();
    static CrtMaster* m_inst;   
    QHash<QString,QIcon*> m_lstDevTypeIcon;
    QHash<QString,QIcon*> m_lstTreeIcon;
    QStringList* m_lstSystemType;
    QStringList* m_lstControllerType;
    QHash<int,QString> m_lstDevType;
    CrtProject* project;
    DataManager* manager;
    CrtTreeView* treeProjectView;
    CrtTreeView* treeMapView;
    CrtGraphicsView* view;
    CrtSetDeviceDlg* setDeviceDlg;
    //CrtWelcomWidget* welcomWidget;
};

#endif // CRTMASTER_H
