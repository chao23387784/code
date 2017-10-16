#ifndef CRTVIEWCONTAINER_H
#define CRTVIEWCONTAINER_H
#include <QStackedWidget>
#include "crtgraphicsview.h"
#include "crtobject.h"
#include <QToolBar>
#include "crtwelcomwidget.h"

class CrtGraphicsViewContainer : public QStackedWidget
{
    Q_OBJECT
public:
    CrtGraphicsViewContainer(CrtGraphicsView* view,QToolBar* toolbar,QWidget *parent=0);
    void setCurrentPanel(CrtObject* obj);
private:
    CrtGraphicsView* m_view;
    CrtWelcomWidget* m_welcom;
    QToolBar* m_toolbar;
};

#endif // CRTVIEWCONTAINER_H
