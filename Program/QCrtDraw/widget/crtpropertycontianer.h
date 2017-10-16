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
    CrtProjectPropPanel* m_panelProject;
    CrtControllerPropPanel* m_panelController;
    CrtLoopPropPanel* m_panelLoop;
    CrtDevicePropPanel* m_panelDevice;
    CrtWelcomWidget* m_panelWelcom;
};

#endif // CRTPROPERTYCONTIANER_H
