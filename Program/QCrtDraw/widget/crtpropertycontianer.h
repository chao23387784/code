#ifndef CRTPROPERTYCONTIANER_H
#define CRTPROPERTYCONTIANER_H
#include "crtprojectproppanel.h"
#include "crtcontrollerproppanel.h"
#include "crtloopproppanel.h"
#include "crtwelcomwidget.h"
#include "crtdeviceproppanel.h"
#include <QStackedWidget>


class CrtPropertyContianer : public QStackedWidget
{
public:
    CrtPropertyContianer(QWidget *parent=0);
    void setCurrentPanel(CrtObject* obj);
private:
    CrtProjectPropPanel* panelProject;
    CrtControllerPropPanel* panelController;
    CrtLoopPropPanel* panelLoop;
    CrtDevicePropPanel* panelDevice;
    CrtWelcomWidget* panelWelcom;
};

#endif // CRTPROPERTYCONTIANER_H
