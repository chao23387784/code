#ifndef QCLOCK_H
#define QCLOCK_H

#include <QTimer>
#include <QLabel>

class QClock : public QLabel
{
    Q_OBJECT
public:
    explicit QClock(QWidget *parent=Q_NULLPTR, Qt::WindowFlags f=Qt::WindowFlags());

signals:

public slots:
    void slotTimeout();
private:
    QTimer* m_timer;
};

#endif // QCLOCK_H
