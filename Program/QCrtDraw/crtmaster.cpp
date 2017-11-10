#include "crtmaster.h"
#include "common.h"
#include <QDir>
#include <QFileInfo>

CrtMaster* CrtMaster::m_inst = NULL;

CrtMaster::CrtMaster()
{
    m_project = NULL;
    m_manager = NULL;
    initDeviceIcon();
    initTreeIcon();
    initSystemType();
    initControllerType();
}

CrtMaster::~CrtMaster()
{

}

CrtMaster *CrtMaster::getInstance()
{
    if(!m_inst)
        m_inst = new CrtMaster();
    return m_inst;
}

void CrtMaster::destroy()
{
    clearTreeIconHashTable();
    clearDeviceIconHashTable();
    SAFE_DELETE(m_project);
    SAFE_DELETE(m_manager);
    SAFE_DELETE(m_lstControllerType);
    SAFE_DELETE(m_lstSystemType);
    SAFE_DELETE(m_inst);
}

void CrtMaster::setProject(CrtProject *proj)
{
    SAFE_DELETE(m_project);
    m_project = proj;
}

void CrtMaster::setManager(DataManager *manager)
{
    SAFE_DELETE(this->m_manager);
    this->m_manager = manager;
}

void CrtMaster::initDeviceIcon()
{
    QDir dir(":/device");//change to local device dir
    dir.setFilter(QDir::Files | QDir::NoSymLinks);

    QFileInfoList lst = dir.entryInfoList();

    for(int i=0;i<lst.size();i++)
    {
        QFileInfo fi = lst.at(i);
        if(fi.suffix() == "bmp")
        {
            //if(!m_lstDevTypeIcon.contains(fi.baseName()))
            m_lstDevTypeIcon.insert(fi.baseName(),new QIcon(fi.filePath()));
        }
    }
}

void CrtMaster::initTreeIcon()
{
    m_lstTreeIcon.insert(OT_PROJECT,new QIcon(":/img/project.png"));
    m_lstTreeIcon.insert(OT_CONTROLLER,new QIcon(":/img/controller.png"));
    m_lstTreeIcon.insert(OT_LOOP,new QIcon(":/img/loop.png"));
    m_lstTreeIcon.insert(OT_BUILDING,new QIcon(":/img/building.png"));
    m_lstTreeIcon.insert(OT_LAYER,new QIcon(":/img/layer.png"));
}

void CrtMaster::initSystemType()
{
    m_lstSystemType = new QStringList();
    m_lstSystemType->append(QObject::tr("Fire Alarm System"));
    m_lstSystemType->append(QObject::tr("Electrical Fire Monitoring System"));
    m_lstSystemType->append(QObject::tr("Combustible Gas Detection And Alarm System"));
    m_lstSystemType->append(QObject::tr("Fire Power Monitoring System"));
    m_lstSystemType->append(QObject::tr("Fire Door Monitoring System"));
}

void CrtMaster::initControllerType()
{
    m_lstControllerType = new QStringList();
    m_lstControllerType->append(QObject::tr("NT8001 Fire Alarm Controller"));
    m_lstControllerType->append(QObject::tr("NT8007 Fire Alarm Controller"));
    m_lstControllerType->append(QObject::tr("NT8021 Electric Fire Monitor"));
    m_lstControllerType->append(QObject::tr("NT8036 Combustible Gas Monitor"));
    m_lstControllerType->append(QObject::tr("NT8051 Fire Door Monitor"));
    m_lstControllerType->append(QObject::tr("NT8056 Fire Power Monitor"));
}

QIcon *CrtMaster::getDeviceIcon(QString strDeviceType)
{
    return m_lstDevTypeIcon.value(strDeviceType,NULL);
}

QIcon *CrtMaster::getTreeIcon(int nTreeIconType)
{
    return m_lstTreeIcon.value(nTreeIconType,NULL);
}

const QStringList *CrtMaster::getControllerType()
{
    return m_lstControllerType;
}

const QStringList *CrtMaster::getSystemType()
{
    return m_lstSystemType;
}

void CrtMaster::clearDeviceIconHashTable()
{
    foreach(QIcon* icon,m_lstDevTypeIcon.values())
    {
        SAFE_DELETE(icon);
    }
    m_lstDevTypeIcon.clear();
}

void CrtMaster::clearTreeIconHashTable()
{
    foreach(QIcon* icon,m_lstTreeIcon.values())
    {
        SAFE_DELETE(icon);
    }
    m_lstTreeIcon.clear();
}

void CrtMaster::setPtojectTreeView(CrtTreeView *view)
{
    m_treeProjectView = view;
}

CrtTreeView *CrtMaster::getProjectTreeView()
{
    return m_treeProjectView;
}

void CrtMaster::setMapTreeView(CrtTreeView *view)
{
    m_treeMapView = view;
}

CrtTreeView *CrtMaster::getMapTreeView()
{
    return m_treeMapView;
}

void CrtMaster::setCrtGraphicsView(CrtGraphicsView *view)
{
    this->m_view = view;
}

CrtGraphicsView *CrtMaster::getCrtGraphicsView()
{
    return m_view;
}

void CrtMaster::setCrtSetDeviceDlg(CrtSetDeviceDlg *dlg)
{
    m_setDeviceDlg = dlg;
}

CrtSetDeviceDlg *CrtMaster::getCrtSetDeviceDlg()
{
    return m_setDeviceDlg;
}

/*void CrtMaster::setWelcomeWidget(CrtWelcomWidget *welcom)
{
    welcomWidget = welcom;
}

CrtWelcomWidget *CrtMaster::WelcomWidget()
{
    return welcomWidget;
}*/

CrtObject *CrtMaster::findProjectObject(int project_id, int controller_id)
{
    Q_UNUSED(project_id);
    if(!m_project)return NULL;
    CrtObject* obj = NULL;
    foreach(CrtObject* item,m_project->m_lstController)
    {
        if(item->getID() == controller_id)
        {
            obj = item;
            break;
        }
    }

    return obj;
}

CrtObject *CrtMaster::findProjectObject(int project_id, int controller_id, int loop_id)
{
    Q_UNUSED(project_id);
    if(!m_project)return NULL;
    CrtObject* obj = NULL;
    foreach(CrtObject* item,m_project->m_lstController)
    {
        if(item->getID() == controller_id)
        {
            obj = item;
            break;
        }
    }

    if(!obj)return obj;

    foreach(CrtObject* item,dynamic_cast<CrtController*>(obj)->m_lstLoop)
    {
        if(item->getID() == loop_id)
        {
            obj = item;
            break;
        }
    }

    return obj;
}

CrtObject *CrtMaster::findProjectObject(int project_id, int controller_id, int loop_id, int device_id)
{
    Q_UNUSED(project_id);
    if(!m_project)return NULL;
    CrtObject* obj = NULL;
    foreach(CrtObject* item,m_project->m_lstController)
    {
        if(item->getID() == controller_id)
        {
            obj = item;
            break;
        }
    }

    if(!obj)return obj;

    foreach(CrtObject* item,dynamic_cast<CrtController*>(obj)->m_lstLoop)
    {
        if(item->getID() == loop_id)
        {
            obj = item;
            break;
        }
    }

    if(!obj)return obj;

    foreach(CrtObject* item,dynamic_cast<CrtLoop*>(obj)->m_lstDevice)
    {
        if(item->getID() == device_id)
        {
            obj = item;
            break;
        }
    }

    return obj;
}

CrtObject *CrtMaster::findMapObject(int project_id, int building_id)
{
    Q_UNUSED(project_id);
    if(!m_project)return NULL;
    CrtObject* obj = NULL;
    foreach(CrtObject* item,m_project->m_lstBuilding)
    {
        if(item->getID() == building_id)
        {
            obj = item;
            break;
        }
    }

    return obj;
}

CrtObject *CrtMaster::findMapObject(int project_id, int building_id, int layer_id)
{
    Q_UNUSED(project_id);
    if(!m_project)return NULL;
    CrtObject* obj = NULL;
    foreach(CrtObject* item,m_project->m_lstBuilding)
    {
        if(item->getID() == building_id)
        {
            obj = item;
            break;
        }
    }

    if(!obj)return obj;

    foreach(CrtObject* item,dynamic_cast<CrtBuilding*>(obj)->m_lstLayer)
    {
        if(item->getID() == layer_id)
        {
            obj = item;
            break;
        }
    }

    return obj;
}

CrtObject *CrtMaster::findMapObject(int project_id, int building_id, int layer_id, int device_id)
{
    Q_UNUSED(project_id);
    if(!m_project)return NULL;
    CrtObject* obj = NULL;
    foreach(CrtObject* item,m_project->m_lstBuilding)
    {
        if(item->getID() == building_id)
        {
            obj = item;
            break;
        }
    }

    if(!obj)return obj;

    foreach(CrtObject* item,dynamic_cast<CrtBuilding*>(obj)->m_lstLayer)
    {
        if(item->getID() == layer_id)
        {
            obj = item;
            break;
        }
    }

    if(!obj)return obj;

    foreach(CrtObject* item,dynamic_cast<CrtLayer*>(obj)->m_lstDevice)
    {
        if(item->getID() == device_id)
        {
            obj = item;
            break;
        }
    }

    return obj;
}

