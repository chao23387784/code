#include "crtmaster.h"
#include "common.h"
#include <QDir>
#include <QFileInfo>

CrtMaster* CrtMaster::m_inst = NULL;

CrtMaster::CrtMaster()
{
    project = NULL;
    manager = NULL;
    initDeviceIcon();
    initTreeIcon();
    initSystemType();
    initControllerType();
}

CrtMaster::~CrtMaster()
{

}

CrtMaster *CrtMaster::GetInstance()
{
    if(!m_inst)
        m_inst = new CrtMaster();
    return m_inst;
}

void CrtMaster::Destroy()
{
    clearTreeIconHashTable();
    ClearDeviceIconHashTable();
    SAFE_DELETE(project);
    SAFE_DELETE(manager);
    SAFE_DELETE(m_lstControllerType);
    SAFE_DELETE(m_lstSystemType);
    SAFE_DELETE(m_inst);
}

void CrtMaster::setProject(CrtProject *proj)
{
    SAFE_DELETE(project);
    project = proj;
}

void CrtMaster::setManager(DataManager *manager)
{
    SAFE_DELETE(this->manager);
    this->manager = manager;
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
    m_lstTreeIcon.insert("project",new QIcon(":/img/project.png"));
    m_lstTreeIcon.insert("controller",new QIcon(":/img/controller.png"));
    m_lstTreeIcon.insert("loop",new QIcon(":/img/loop.png"));
    m_lstTreeIcon.insert("building",new QIcon(":/img/building.png"));
    m_lstTreeIcon.insert("layer",new QIcon(":/img/layer.png"));
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

QIcon *CrtMaster::DeviceIcon(QString strDeviceType)
{
    return m_lstDevTypeIcon.value(strDeviceType,NULL);
}

QIcon *CrtMaster::TreeIcon(QString strTreeIconType)
{
    return m_lstTreeIcon.value(strTreeIconType,NULL);
}

const QStringList *CrtMaster::ControllerType()
{
    return m_lstControllerType;
}

const QStringList *CrtMaster::SystemType()
{
    return m_lstSystemType;
}

void CrtMaster::ClearDeviceIconHashTable()
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
    treeProjectView = view;
}

CrtTreeView *CrtMaster::ProjectTreeView()
{
    return treeProjectView;
}

void CrtMaster::setMapTreeView(CrtTreeView *view)
{
    treeMapView = view;
}

CrtTreeView *CrtMaster::MapTreeView()
{
    return treeMapView;
}

void CrtMaster::setCrtGraphicsView(CrtGraphicsView *view)
{
    this->view = view;
}

CrtGraphicsView *CrtMaster::getCrtGraphicsView()
{
    return view;
}

void CrtMaster::setCrtSetDeviceDlg(CrtSetDeviceDlg *dlg)
{
    setDeviceDlg = dlg;
}

CrtSetDeviceDlg *CrtMaster::getCrtSetDeviceDlg()
{
    return setDeviceDlg;
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
    if(!project)return NULL;
    CrtObject* obj = NULL;
    foreach(CrtObject* item,project->m_lstController)
    {
        if(item->ID() == controller_id)
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
    if(!project)return NULL;
    CrtObject* obj = NULL;
    foreach(CrtObject* item,project->m_lstController)
    {
        if(item->ID() == controller_id)
        {
            obj = item;
            break;
        }
    }

    if(!obj)return obj;

    foreach(CrtObject* item,dynamic_cast<CrtController*>(obj)->m_lstLoop)
    {
        if(item->ID() == loop_id)
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
    if(!project)return NULL;
    CrtObject* obj = NULL;
    foreach(CrtObject* item,project->m_lstController)
    {
        if(item->ID() == controller_id)
        {
            obj = item;
            break;
        }
    }

    if(!obj)return obj;

    foreach(CrtObject* item,dynamic_cast<CrtController*>(obj)->m_lstLoop)
    {
        if(item->ID() == loop_id)
        {
            obj = item;
            break;
        }
    }

    if(!obj)return obj;

    foreach(CrtObject* item,dynamic_cast<CrtLoop*>(obj)->m_lstDevice)
    {
        if(item->ID() == device_id)
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
    if(!project)return NULL;
    CrtObject* obj = NULL;
    foreach(CrtObject* item,project->m_lstBuilding)
    {
        if(item->ID() == building_id)
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
    if(!project)return NULL;
    CrtObject* obj = NULL;
    foreach(CrtObject* item,project->m_lstBuilding)
    {
        if(item->ID() == building_id)
        {
            obj = item;
            break;
        }
    }

    if(!obj)return obj;

    foreach(CrtObject* item,dynamic_cast<CrtBuilding*>(obj)->m_lstLayer)
    {
        if(item->ID() == layer_id)
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
    if(!project)return NULL;
    CrtObject* obj = NULL;
    foreach(CrtObject* item,project->m_lstBuilding)
    {
        if(item->ID() == building_id)
        {
            obj = item;
            break;
        }
    }

    if(!obj)return obj;

    foreach(CrtObject* item,dynamic_cast<CrtBuilding*>(obj)->m_lstLayer)
    {
        if(item->ID() == layer_id)
        {
            obj = item;
            break;
        }
    }

    if(!obj)return obj;

    foreach(CrtObject* item,dynamic_cast<CrtLayer*>(obj)->m_lstDevice)
    {
        if(item->ID() == device_id)
        {
            obj = item;
            break;
        }
    }

    return obj;
}

