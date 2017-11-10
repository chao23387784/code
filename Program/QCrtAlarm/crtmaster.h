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
    static CrtMaster* getInstance();
    void destroy();
    void setProject(CrtProject* proj);
    CrtProject* getProject(){return m_project;}
    void setManager(DataManager* manager);
    DataManager* getManager(){return m_manager;}
    void initDeviceIcon();
    void initTreeIcon();
    void initSystemType();
    void initControllerType();
    QIcon* getDeviceIcon(QString strDeviceType);
    QIcon* getTreeIcon(int nTreeIconType);
    const QStringList* getControllerType();
    const QStringList* getSystemType();
    void clearDeviceIconHashTable();
    void clearTreeIconHashTable();
    void setPtojectTreeView(CrtTreeView* view);
    CrtTreeView* getProjectTreeView();
    void setMapTreeView(CrtTreeView* view);
    CrtTreeView* getMapTreeView();
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
    QHash<int,QIcon*> m_lstTreeIcon;
    QStringList* m_lstSystemType;
    QStringList* m_lstControllerType;
    QHash<int,QString> m_lstDevType;
    CrtProject* m_project;
    DataManager* m_manager;
    CrtTreeView* m_treeProjectView;
    CrtTreeView* m_treeMapView;
    CrtGraphicsView* m_view;
    CrtSetDeviceDlg* m_setDeviceDlg;
    //CrtWelcomWidget* welcomWidget;
};

#endif // CRTMASTER_H
