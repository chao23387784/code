#ifndef CRTTWOWAYPUSHBUTTON_H
#define CRTTWOWAYPUSHBUTTON_H

#include <QToolButton>
#include <QTimer>
#include <qobjectdefs.h>

class CrtTwoWayToolButton : public QToolButton
{
    Q_OBJECT
public:
    explicit CrtTwoWayToolButton(QWidget * parent=0);
    ~CrtTwoWayToolButton();

signals:
    void sigQuickPress();
    void sigHoldPress();
private slots:
    void slotTimeOut();
    //void OnClick();
protected:
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void initTimer();
 private:
    QTimer* m_timer;
};

#endif // CRTTWOWAYPUSHBUTTON_H
