#ifndef CRTVIEWCONTAINER_H
#define CRTVIEWCONTAINER_H
#include <QStackedWidget>
#include "crtgraphicsview.h"
#include "crtobject.h"
#include <QToolBar>
#include <QTimer>
#include <QToolButton>
#include <QAction>
#include "crtwelcomwidget.h"
#include "crtpropview.h"

class CrtGraphicsViewContainer : public QWidget
{
    Q_OBJECT
public:
    CrtGraphicsViewContainer(CrtGraphicsView* view,QWidget *parent=0);
    void setCurrentPanel(CrtObject* obj);
protected slots:
    void slotFlash();
    void slotEvent();
private:
    CrtGraphicsView* m_view;
    CrtWelcomWidget* m_welcom;
    QToolBar* m_toolbar;
    QStackedWidget* m_widMain;
    QToolBar* m_toolbarEvent;
    CrtPropView* m_viewEvent; //saperate to multi view when reload model slow
    QToolButton* m_labFirstAlarm;
    QToolButton* m_labResolution;
    QToolButton* m_btnFireAlarm;
    QToolButton* m_btnAlarm;
    QToolButton* m_btnStart;
    QToolButton* m_btnFeedback;
    QToolButton* m_btnSupervise;
    QToolButton* m_btnFault;
    QToolButton* m_btnDisable;
    QToolButton* m_btnStatus;
    QToolButton* m_btnOther;
    QToolButton* m_btnTrans;
    QToolButton* m_btnNormal;

    QTimer* m_timerEvent;
};

#endif // CRTVIEWCONTAINER_H
