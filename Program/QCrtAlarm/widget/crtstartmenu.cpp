#include "crtstartmenu.h"
#include <QIcon>
#include <QFont>
#include <QObject>

CrtStartMenu::CrtStartMenu(QWidget *parent)
{
    Q_UNUSED(parent);
    initUi();
}

void CrtStartMenu::initUi()
{
    m_mnSystem = new QMenu(tr("System"),this);
    m_mnSystem->setIcon(QIcon(":/img/Gear.ico"));
    addMenu(m_mnSystem);

    m_mnSystem->addAction(QIcon(":/img/shutdd.jpg"),tr("Shutdown"),this,SLOT(slotShutDown()));

    m_mnOperate = new QMenu(tr("Operate"),this);
    m_mnOperate->setIcon(QIcon(":/img/program.png"));
    addMenu(m_mnOperate);

    m_mnOperate->addAction(QIcon(":/img/reset.png"),tr("Reset"),this,SLOT(slotReset()));
    m_mnOperate->addAction(QIcon(":/img/play.png"),tr("Mute"),this,SLOT(slotMute()));

    m_mnView = new QMenu(tr("View"),this);
    m_mnView->setIcon(QIcon(":/img/search.png"));
    addMenu(m_mnView);

    m_mnView->addAction(QIcon(":/img/design.png"),tr("Configuration Information"),this,SLOT(slotConfig()));
    m_mnView->addAction(QIcon(":/img/allregedit.png"),tr("Monitoring Information"),this,SLOT(slotMonitor()));
    m_mnView->addAction(QIcon(":/img/controllertest.png"),tr("Running Inforamtion"),this,SLOT(slotRun()));
    m_mnView->addAction(QIcon(":/img/loginregedit.png"),tr("Equipment Information"),this,SLOT(slotEquipment()));
    m_mnView->addAction(QIcon(":/img/custompath.png"),tr("Duty Information"),this,SLOT(slotDuty()));
    m_mnView->addAction(QIcon(":/img/deviceinfo.ico"),tr("Maintaining Information"),this,SLOT(slotMaintain()));
    m_mnView->addAction(QIcon(":/img/controller.png"),tr("Layout Plan List"),this,SLOT(slotDeviceType()));
    m_mnView->addAction(QIcon(":/img/firstfire.old.ico"),tr("Fire Alarm Processing Schedule"),this,SLOT(slotFireSchedule()));

    m_mnSetup = new QMenu(tr("Setup"),this);
    m_mnSetup->setIcon(QIcon(":/img/tool.jpg"));
    addMenu(m_mnSetup);

    m_mnSetup->addAction(QIcon(":/img/serial.ico"),tr("Communication Setup"),this,SLOT(slotCommunicate()));
    m_mnSetup->addAction(QIcon(":/img/12.ico"),tr("Network Setup"),this,SLOT(slotNetwork()));
    m_mnSetup->addAction(QIcon(":/img/administrator.png"),tr("User Management"),this,SLOT(slotUser()));
    m_mnSetup->addAction(QIcon(":/img/backgroundcolor.png"),tr("Screen Saver Setup"),this,SLOT(slotScreen()));
    m_mnSetup->addAction(QIcon(":/img/deviceinfo.png"),tr("Other Setup"),this,SLOT(slotOther()));

    m_mnHelp = new QMenu(tr("Help"),this);
    m_mnHelp->setIcon(QIcon(":/img/help.png"));
    addMenu(m_mnHelp);

    m_mnHelp->addAction(QIcon(":/img/info.png"),tr("About"),this,SLOT(slotAbout()));

//    QString sheet =  "QMenu {background-color: white; margin: 3px; font-size: 14px;}\
//            QMenu::item {padding: 3px 25px 3px 42px; border: 1px solid transparent; min-height: 32px; min-width: 70px; border-radius: 4px;}\
//            QMenu::separator {height: 2px; background: #CCCCFF; margin-left: 5px; margin-right: 5px;}\
//            QMenu::right-arrow { image: url(:/img/rr.jpg); }\
//            QMenu::item:selected {background-color: qlineargradient(x1: 0.5, y1: 0, x2: 0.5, y2: 1, stop: 0 #99CCFF, stop: 0.5 #CCFFFF, stop: 1 #99CCFF); border-color: #6699CC;}";

//    m_style = new CrtMyIconStyle();
//    setStyleSheet(sheet);
//    setStyle(m_style);

//    m_mnSystem->setStyleSheet(sheet);
//    m_mnSystem->setStyle(m_style);

//    m_mnOperate->setStyleSheet(sheet);
//    m_mnOperate->setStyle(m_style);

//    m_mnView->setStyleSheet(sheet);
//    m_mnView->setStyle(m_style);

//    m_mnSetup->setStyleSheet(sheet);
//    m_mnSetup->setStyle(m_style);

//    m_mnHelp->setStyleSheet(sheet);
//    m_mnHelp->setStyle(m_style);
}

void CrtStartMenu::slotShutDown()
{

}

void CrtStartMenu::slotReset()
{

}

void CrtStartMenu::slotMute()
{

}

void CrtStartMenu::slotConfig()
{

}

void CrtStartMenu::slotMonitor()
{

}

void CrtStartMenu::slotRun()
{

}

void CrtStartMenu::slotEquipment()
{

}

void CrtStartMenu::slotDuty()
{

}

void CrtStartMenu::slotMaintain()
{

}

void CrtStartMenu::slotDeviceType()
{

}

void CrtStartMenu::slotFireSchedule()
{

}

void CrtStartMenu::slotCommunicate()
{

}

void CrtStartMenu::slotNetwork()
{

}

void CrtStartMenu::slotUser()
{

}

void CrtStartMenu::slotScreen()
{

}

void CrtStartMenu::slotOther()
{

}

void CrtStartMenu::slotAbout()
{

}
