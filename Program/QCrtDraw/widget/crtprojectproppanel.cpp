#include "crtprojectproppanel.h"
#include <QLayout>
#include <QValidator>
#include <QHeaderView>
#include "crtmaster.h"


CrtProjectPropPanel::CrtProjectPropPanel(QWidget *parent) : QWidget(parent)
{
    QLabel* lab = new QLabel(tr("Project Name:"),this);
    editProjectName = new QLineEdit(this);
    editProjectName->setMaxLength(256);
    tblController = new CrtPropView(this);
    btnSet = new QPushButton(tr("set"),this);

    QHBoxLayout* layoutTop = new QHBoxLayout(this);
    layoutTop->addWidget(lab);
    layoutTop->addWidget(editProjectName);
    layoutTop->addWidget(btnSet);

    QWidget* layoutContainer = new QWidget(this);
    layoutContainer->setLayout(layoutTop);

    QVBoxLayout* layoutMain = new QVBoxLayout(this);
    layoutMain->addWidget(layoutContainer);
    layoutMain->addWidget(tblController);

    setLayout(layoutMain);

    source = NULL;

    connect(btnSet,SIGNAL(clicked(bool)),this,SLOT(onSet()));

    model = new CrtControllerPropModel(this);
    tblController->setModel(model);
    delegate = new CrtControllerPropDelegate(this);
    tblController->setItemDelegate(delegate);

    tblController->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(delegate,SIGNAL(valueChanged(QString)),tblController,SLOT(itemDataChanged(QString)));
}

void CrtProjectPropPanel::initPanel(CrtObject *obj)
{
    if(!obj || obj->Type().compare("project") || !model)return;

    source = dynamic_cast<CrtProject*>(obj);

    editProjectName->setText(source->Name());

    model->unload();
    model->load(obj);
}

void CrtProjectPropPanel::onSet()
{
    if(editProjectName->text().trimmed().isEmpty() || !source)return;
    source->setName(editProjectName->text().trimmed());
    CrtMaster::GetInstance()->ProjectTreeView()->updateItem(source);
}

