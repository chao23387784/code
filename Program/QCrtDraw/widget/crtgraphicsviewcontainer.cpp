#include "crtgraphicsviewcontainer.h"
#include "crtmaster.h"
#include <QLayout>

CrtGraphicsViewContainer::CrtGraphicsViewContainer(CrtGraphicsView *view, QToolBar *toolbar, QWidget *parent):QStackedWidget(parent)
{
    m_welcom = new CrtWelcomWidget(parent);
    this->m_view = view;
    this->m_toolbar = toolbar;

    QWidget* widget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(this->m_toolbar);
    layout->addWidget(this->m_view);
    widget->setLayout(layout);

    addWidget(m_welcom);
    addWidget(widget);
}

void CrtGraphicsViewContainer::setCurrentPanel(CrtObject *obj)
{
    if(!obj)
    {
        setCurrentIndex(0);
    }
    else
    {
        if(obj->getType() == OT_LAYER)
        {
            setCurrentIndex(1);
        }
        else
        {
            setCurrentIndex(0);
        }
    }
}
