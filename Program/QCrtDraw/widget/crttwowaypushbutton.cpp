#include "crttwowaypushbutton.h"
#include <QMessageBox>
#include <QDebug>
#include <QMouseEvent>
#include <QPoint>
#include "common.h"

CrtTwoWayToolButton::CrtTwoWayToolButton(QWidget *parent):QToolButton(parent)
{
    initTimer();
}

CrtTwoWayToolButton::~CrtTwoWayToolButton()
{

}

void CrtTwoWayToolButton::initTimer()
{
    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(slotTimeOut()));
    if(m_timer->isActive())m_timer->stop();
    //connect(this,SIGNAL(quickpress()),this,SLOT(OnClick()));
}

void CrtTwoWayToolButton::slotTimeOut()
{
    if(m_timer->isActive())m_timer->stop();
    emit sigHoldPress();

    QMouseEvent* event = new QMouseEvent(QEvent::MouseButtonRelease,QPoint(18,19),Qt::LeftButton,0,Qt::NoModifier);
    QToolButton::mouseReleaseEvent(event);
    SAFE_DELETE(event);
}

/*void CrtTwoWayPushButton::OnClick()
{
    QMessageBox::information(this,tr("info"),tr("short click!"));
}*/

void CrtTwoWayToolButton::mousePressEvent(QMouseEvent *e)
{
    m_timer->start();
    QToolButton::mousePressEvent(e);
}

void CrtTwoWayToolButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(m_timer->isActive())
    {
        m_timer->stop();
        emit sigQuickPress();
    }
    QToolButton::mouseReleaseEvent(e);
}
