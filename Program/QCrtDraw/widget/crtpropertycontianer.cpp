#include "crtpropertycontianer.h"

CrtPropertyContianer::CrtPropertyContianer(QWidget *parent):QStackedWidget(parent)
{
    m_panelProject = new CrtProjectPropPanel(this);
    m_panelController = new CrtControllerPropPanel(this);
    m_panelLoop = new CrtLoopPropPanel(this);
    m_panelDevice = new CrtDevicePropPanel(this);
    m_panelWelcom = new CrtWelcomWidget(this);

    addWidget(m_panelWelcom);
    addWidget(m_panelProject);
    addWidget(m_panelController);
    addWidget(m_panelLoop);
    addWidget(m_panelDevice);
}

void CrtPropertyContianer::setCurrentPanel(CrtObject *obj)
{
    if(obj->getType() == OT_PROJECT)
    {
        m_panelProject->initPanel(obj);
        setCurrentIndex(1);
    }else if(obj->getType() == OT_CONTROLLER)
    {
        m_panelController->initPanel(obj);
        setCurrentIndex(2);
    }else if(obj->getType() == OT_LOOP)
    {
        m_panelLoop->initPanel(obj);
        setCurrentIndex(3);
    }else if(obj->getType() == OT_DEVICE)
    {
        m_panelDevice->initPanel(obj);
        setCurrentIndex(4);
    }else
    {
        setCurrentIndex(0);
    }
}
