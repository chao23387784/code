#include "crtpropertycontianer.h"

CrtPropertyContianer::CrtPropertyContianer(QWidget *parent):QStackedWidget(parent)
{
    panelProject = new CrtProjectPropPanel(this);
    panelController = new CrtControllerPropPanel(this);
    panelLoop = new CrtLoopPropPanel(this);
    panelDevice = new CrtDevicePropPanel(this);
    panelWelcom = new CrtWelcomWidget(this);

    addWidget(panelWelcom);
    addWidget(panelProject);
    addWidget(panelController);
    addWidget(panelLoop);
    addWidget(panelDevice);
}

void CrtPropertyContianer::setCurrentPanel(CrtObject *obj)
{
    if(!obj->Type().compare("project"))
    {
        panelProject->initPanel(obj);
        setCurrentIndex(1);
    }else if(!obj->Type().compare("controller"))
    {
        panelController->initPanel(obj);
        setCurrentIndex(2);
    }else if(!obj->Type().compare("loop"))
    {
        panelLoop->initPanel(obj);
        setCurrentIndex(3);
    }else if(!obj->Type().compare("device"))
    {
        panelDevice->initPanel(obj);
        setCurrentIndex(4);
    }else
    {
        setCurrentIndex(0);
    }
}
