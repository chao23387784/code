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
    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer,SIGNAL(timeout()),this,SLOT(OnTimeOut()));
    if(timer->isActive())timer->stop();
    //connect(this,SIGNAL(quickpress()),this,SLOT(OnClick()));
}

void CrtTwoWayToolButton::OnTimeOut()
{
    if(timer->isActive())timer->stop();
    emit holdpress();

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
    timer->start();
    QToolButton::mousePressEvent(e);
}

void CrtTwoWayToolButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(timer->isActive())
    {
        timer->stop();
        emit quickpress();
    }
    QToolButton::mouseReleaseEvent(e);
}
