#include "crtgraphicsviewcontainer.h"
#include "crtmaster.h"
#include <QLayout>
#include <QIcon>
#include <QList>

CrtGraphicsViewContainer::CrtGraphicsViewContainer(CrtGraphicsView *view,QWidget *parent):QWidget(parent)
{
    m_welcom = new CrtWelcomWidget(parent);

    m_toolbar = new QToolBar(this);
    m_labFirstAlarm = new QToolButton(this);
    m_labFirstAlarm->setText(tr("First Fire Alarm:No Alarm"));
    m_labResolution = new QToolButton(this);
    m_labResolution->setText(tr("Fire Alarm Processing Schedule"));

    m_toolbar->addWidget(m_labFirstAlarm);
    m_toolbar->addWidget(m_labResolution);
    //toolBarView->setFixedHeight(20);
    m_labFirstAlarm->setFixedWidth(700);

    m_view = view;

    m_widMain = new QStackedWidget(this);

    m_widMain->addWidget(m_welcom);
    m_widMain->addWidget(view);

    m_toolbarEvent = new QToolBar(this);

    m_btnFireAlarm = new QToolButton(this);
    m_btnFireAlarm->setIcon(QIcon(":/img/A00.BMP"));
    m_btnFireAlarm->setText(tr("Fire Alarm"));

    m_btnAlarm = new QToolButton(this);
    m_btnAlarm->setIcon(QIcon(":/img/A00.BMP"));
    m_btnAlarm->setText(tr("Alarm"));

    m_btnStart = new QToolButton(this);
    m_btnStart->setIcon(QIcon(":/img/A00.BMP"));
    m_btnStart->setText(tr("Start"));

    m_btnFeedback = new QToolButton(this);
    m_btnFeedback->setIcon(QIcon(":/img/A00.BMP"));
    m_btnFeedback->setText(tr("Feedback"));

    m_btnSupervise = new QToolButton(this);
    m_btnSupervise->setIcon(QIcon(":/img/A00.BMP"));
    m_btnSupervise->setText(tr("Supervise"));

    m_btnFault = new QToolButton(this);
    m_btnFault->setIcon(QIcon(":/img/F00.BMP"));
    m_btnFault->setText(tr("Fault"));

    m_btnDisable = new QToolButton(this);
    m_btnDisable->setIcon(QIcon(":/img/F00.BMP"));
    m_btnDisable->setText(tr("Disable"));

    m_btnStatus = new QToolButton(this);
    m_btnStatus->setIcon(QIcon(":/img/R00.BMP"));
    m_btnStatus->setText(tr("Status"));

    m_btnOther = new QToolButton(this);
    m_btnOther->setIcon(QIcon(":/img/R00.BMP"));
    m_btnOther->setText(tr("Other"));


    foreach(QToolButton* btn,QList<QToolButton*>() <<m_btnFireAlarm<<m_btnAlarm<<m_btnStart<<m_btnFeedback
            <<m_btnSupervise<<m_btnFault<<m_btnDisable<<m_btnStatus<<m_btnOther)
    {
        btn->setCheckable(true);
        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        m_toolbarEvent->addWidget(btn);
        connect(btn,SIGNAL(clicked(bool)),this,SLOT(slotEvent()));
    }

    m_btnTrans = new QToolButton(this);
    m_btnTrans->setIcon(QIcon(":/img/A00.BMP"));
    m_btnTrans->setText(tr("Transmission"));
    m_btnTrans->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_toolbarEvent->addWidget(m_btnTrans);

    m_btnNormal = new QToolButton(this);
    m_btnNormal->setIcon(QIcon(":/img/R00.BMP"));
    m_btnNormal->setText(tr("Normal"));
    m_btnNormal->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_toolbarEvent->addWidget(m_btnNormal);

    m_toolbarEvent->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    //m_viewEvent = new CrtPropView(this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(m_toolbar);
    layout->addWidget(m_widMain);
    layout->addWidget(m_toolbarEvent);
    //layout->addWidget(m_viewEvent);

    //m_viewEvent->setVisible(false);

    setLayout(layout);

    m_timerEvent = new QTimer(this);
    connect(m_timerEvent,SIGNAL(timeout()),this,SLOT(slotFlash()));
    m_timerEvent->setInterval(500);
    m_timerEvent->start();
}

void CrtGraphicsViewContainer::setCurrentPanel(CrtObject *obj)
{
    if(!obj)
    {
        m_widMain->setCurrentIndex(0);
    }
    else
    {
        if(obj->getType() == OT_LAYER)
        {
            m_widMain->setCurrentIndex(1);
        }
        else
        {
            m_widMain->setCurrentIndex(0);
        }
    }
}

void CrtGraphicsViewContainer::slotFlash()
{
    static bool bLight = true;
    if(bLight)
    {
        m_btnNormal->setIcon(QIcon(":/img/R01.BMP"));
    }else
    {
        m_btnNormal->setIcon(QIcon(":/img/R00.BMP"));
    }
    bLight = !bLight;
}

void CrtGraphicsViewContainer::slotEvent()
{
   QToolButton* s = static_cast<QToolButton*>(sender());

   if(s->isChecked())
   {
       foreach(QToolButton* btn,QList<QToolButton*>() <<m_btnFireAlarm<<m_btnAlarm<<m_btnStart<<m_btnFeedback
               <<m_btnSupervise<<m_btnFault<<m_btnDisable<<m_btnStatus<<m_btnOther)
       {
           if(btn != s)
               btn->setChecked(false);
       }

       if(s == m_btnFireAlarm)
       {

       }else if(s == m_btnAlarm)
       {

       }else if(s == m_btnStart)
       {

       }else if(s == m_btnFeedback)
       {

       }else if(s == m_btnSupervise)
       {

       }else if(s == m_btnFault)
       {

       }else if(s == m_btnDisable)
       {

       }else if(s == m_btnStatus)
       {

       }else if(s == m_btnOther)
       {

       }else
       {

       }
   }
   else
   {
       //m_viewEvent->setVisible(false);
   }
}

