#include "crtloopproppanel.h"
#include <QLayout>
#include <QLabel>
#include <QValidator>
#include <QHeaderView>
#include "crtmaster.h"

CrtLoopPropPanel::CrtLoopPropPanel(QWidget *parent) : QWidget(parent)
{
    QLabel* lab = new QLabel(tr("Loop ID:"),this);
    editLoopID = new QLineEdit(this);
    editLoopID->setReadOnly(true);
    //editLoopID->setValidator(new QIntValidator(1,99,this));
    QLabel* labName = new QLabel(tr("Loop Name:"),this);
    editLoopName = new QLineEdit(this);
    editLoopName->setMaxLength(256);
    tblDevice = new CrtPropView(this);

    btnSet = new QPushButton(tr("set"),this);

    QHBoxLayout* layoutTop = new QHBoxLayout(this);
    layoutTop->addWidget(lab);
    layoutTop->addWidget(editLoopID);
    layoutTop->addWidget(labName);
    layoutTop->addWidget(editLoopName);
    layoutTop->addWidget(btnSet);

    QWidget* layoutContainer = new QWidget(this);
    layoutContainer->setLayout(layoutTop);

    QVBoxLayout* layoutMain = new QVBoxLayout(this);
    layoutMain->addWidget(layoutContainer);
    layoutMain->addWidget(tblDevice);

    setLayout(layoutMain);

    source = NULL;

    connect(btnSet,SIGNAL(clicked(bool)),this,SLOT(onSet()));

    model = new CrtDevicePropModel(this);
    tblDevice->setModel(model);
    delegate = new CrtDevicePropDelegate(this);
    tblDevice->setItemDelegate(delegate);

    tblDevice->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(delegate,SIGNAL(valueChanged(QString)),tblDevice,SLOT(itemDataChanged(QString)));
}

void CrtLoopPropPanel::initPanel(CrtObject *obj)
{
    if(obj->Type().compare("loop") || !model)return;

    source = dynamic_cast<CrtLoop*>(obj);

    editLoopID->setText(QString("%1").arg(source->ID()));
    editLoopName->setText(source->Name());

    model->unload();
    model->load(obj);
}

void CrtLoopPropPanel::onSet()
{
    if(!source)return;

    /*if(!editLoopID->text().trimmed().isEmpty())
        source->setID(editLoopID->text().trimmed().toInt());*/

    if(!editLoopName->text().trimmed().isEmpty())
        source->setName(editLoopName->text().trimmed());
    else
        source->setName(QString(tr("NT-Loop%1")).arg(source->ID()));

    CrtMaster::GetInstance()->ProjectTreeView()->updateItem(source);
}

