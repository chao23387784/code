#include "crtmaster.h"
#include "common.h"

CrtMaster* CrtMaster::m_inst = NULL;

CrtMaster::CrtMaster()
{
    project = NULL;
    manager = NULL;
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
    //内存回收，工具类析构
    SAFE_DELETE(project);
    SAFE_DELETE(manager);
    SAFE_DELETE(m_inst);
}

void CrtMaster::setProject(CrtProject *proj)
{
    SAFE_DELETE(project);
    project = proj;
}

void CrtMaster::setManager(EntityManager *manager)
{
    SAFE_DELETE(this->manager);
    this->manager = manager;
}

