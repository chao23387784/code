#include "crtmaster.h"
#include "common.h"

CrtMaster* CrtMaster::m_inst = NULL;

CrtMaster::CrtMaster()
{
    project = NULL;
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
    SAFE_DELETE(m_inst)
}

