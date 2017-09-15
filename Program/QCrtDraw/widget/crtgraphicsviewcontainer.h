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
    CrtGraphicsView* view;
    CrtWelcomWidget* welcom;
    QToolBar* toolbar;
};

#endif // CRTVIEWCONTAINER_H
