#include "crtgraphicsviewcontainer.h"
#include "crtmaster.h"
#include <QLayout>

CrtGraphicsViewContainer::CrtGraphicsViewContainer(CrtGraphicsView *view, QToolBar *toolbar, QWidget *parent):QStackedWidget(parent)
{
    welcom = new CrtWelcomWidget(parent);
    this->view = view;
    this->toolbar = toolbar;

    QWidget* widget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(this->toolbar);
    layout->addWidget(this->view);
    widget->setLayout(layout);

    addWidget(welcom);
    addWidget(widget);
}

void CrtGraphicsViewContainer::setCurrentPanel(CrtObject *obj)
{
    if(!obj->Type().compare("layer"))
    {
        setCurrentIndex(1);
    }
    else
    {
        setCurrentIndex(0);
    }
}
