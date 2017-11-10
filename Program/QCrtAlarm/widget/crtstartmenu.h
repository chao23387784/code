#ifndef CRTSTARTMENU_H
#define CRTSTARTMENU_H
#include <QMenu>
#include "crtmyiconstyle.h"

class CrtStartMenu : public QMenu
{
    Q_OBJECT
public:
    explicit CrtStartMenu(QWidget *parent = Q_NULLPTR);
    void initUi();
private slots:
    void slotShutDown();
    void slotReset();
    void slotMute();
    void slotConfig();
    void slotMonitor();
    void slotRun();
    void slotEquipment();
    void slotDuty();
    void slotMaintain();
    void slotDeviceType();
    void slotFireSchedule();
    void slotCommunicate();
    void slotNetwork();
    void slotUser();
    void slotScreen();
    void slotOther();
    void slotAbout();
private:
    QMenu* m_mnSystem;
    QMenu* m_mnView;
    QMenu* m_mnOperate;
    QMenu* m_mnSetup;
    QMenu* m_mnHelp;
    CrtMyIconStyle* m_style;
};

#endif // CRTSTARTMENU_H
