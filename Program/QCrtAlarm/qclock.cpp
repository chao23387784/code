#include "qclock.h"
#include <QLabel>
#include <QPixmap>
#include <QLayout>
#include <QDateTime>

QClock::QClock(QWidget *parent, Qt::WindowFlags f)
{
    Q_UNUSED(parent);
    Q_UNUSED(f);

    QDateTime now = QDateTime::currentDateTime();
    QString str = now.toString("yyyy-MM-dd hh:mm:ss dddd");
    setText(str);

    m_timer = new QTimer(this);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(slotTimeout()));
    m_timer->setInterval(1000);
    m_timer->start();
}

void QClock::slotTimeout()
{
    QDateTime now = QDateTime::currentDateTime();
    QString str = now.toString("yyyy-MM-dd hh:mm:ss dddd");
    setText(str);
}
