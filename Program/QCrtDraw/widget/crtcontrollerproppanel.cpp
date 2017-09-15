#include "crtcontrollerproppanel.h"
#include <QLabel>
#include <QLayout>
#include "crtcontroller.h"
#include "crtmaster.h"
#include <QValidator>
#include <QHeaderView>\
#include "crtmaster.h"

CrtControllerPropPanel::CrtControllerPropPanel(QWidget *parent) : QWidget(parent)
{
    QLabel* labID = new QLabel(tr("Controller ID:"),this);
    editControllerID = new QLineEdit(this);
    editControllerID->setReadOnly(true);
    //editControllerID->setValidator(new QIntValidator(1,999,this));

    QLabel* labName = new QLabel(tr("Controller Name:"),this);
    editControllerName = new QLineEdit(this);
    editControllerName->setMaxLength(256);

    QLabel* labNetID = new QLabel(tr("NetID:"),this);
    editControllerNetID = new QLineEdit(this);
    editControllerNetID->setValidator(new QIntValidator(0,999,this));

    QLabel* labType = new QLabel(tr("Controller Type:"),this);
    cmbControllerType = new QComboBox(this);
    cmbControllerType->addItems(*(CrtMaster::GetInstance()->ControllerType()));

    QLabel* labSystem = new QLabel(tr("System Type:"),this);
    cmbControllerSystem = new QComboBox(this);
    cmbControllerSystem->addItems(*(CrtMaster::GetInstance()->SystemType()));

    btnSet = new QPushButton(tr("set"),this);

    tblLoop = new CrtPropView(this);

    QHBoxLayout* layoutTop1 = new QHBoxLayout(this);
    layoutTop1->addWidget(labID);
    layoutTop1->addWidget(editControllerID);
    layoutTop1->addWidget(labName);
    layoutTop1->addWidget(editControllerName);
    layoutTop1->addWidget(labNetID);
    layoutTop1->addWidget(editControllerNetID);

    QWidget* layoutContainer1 = new QWidget(this);
    layoutContainer1->setLayout(layoutTop1);

    QHBoxLayout* layoutTop2 = new QHBoxLayout(this);
    layoutTop2->addWidget(labType);
    layoutTop2->addWidget(cmbControllerType);
    layoutTop2->addWidget(labSystem);
    layoutTop2->addWidget(cmbControllerSystem);
    layoutTop2->addStretch(2);
    layoutTop2->addWidget(btnSet);
    layoutTop2->setStretchFactor(labType,1);
    layoutTop2->setStretchFactor(cmbControllerType,3);
    layoutTop2->setStretchFactor(labSystem,1);
    layoutTop2->setStretchFactor(cmbControllerSystem,3);
    layoutTop2->setStretchFactor(btnSet,1);

    QWidget* layoutContainer2 = new QWidget(this);
    layoutContainer2->setLayout(layoutTop2);

    QVBoxLayout* layoutMain = new QVBoxLayout(this);
    layoutMain->addWidget(layoutContainer1);
    layoutMain->addWidget(layoutContainer2);
    layoutMain->addWidget(tblLoop);

    setLayout(layoutMain);

    source = NULL;

    connect(btnSet,SIGNAL(clicked(bool)),this,SLOT(onSet()));

    model = new CrtLoopPropModel(this);
    tblLoop->setModel(model);
    delegate = new CrtLoopPropDelegate(this);
    tblLoop->setItemDelegate(delegate);

    tblLoop->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(delegate,SIGNAL(valueChanged(QString)),tblLoop,SLOT(itemDataChanged(QString)));
}

void CrtControllerPropPanel::initPanel(CrtObject *obj)
{
    if(!obj || obj->Type().compare("controller") || !model)return;

    source = dynamic_cast<CrtController*>(obj);

    editControllerID->setText(QString("%1").arg(source->ID()));
    editControllerName->setText(source->Name());
    editControllerNetID->setText(QString("%1").arg(source->NetID()));

    int nIndex = cmbControllerType->findText(source->ControllerType());
    nIndex == -1 ? cmbControllerType->setCurrentText(source->ControllerType()) :
                   cmbControllerType->setCurrentIndex(nIndex);

    nIndex = cmbControllerSystem->findText(source->SystemType());
    nIndex == -1 ? cmbControllerSystem->setCurrentText(source->SystemType()) :
                   cmbControllerSystem->setCurrentIndex(nIndex);

    model->unload();
    model->load(obj);
}

void CrtControllerPropPanel::onSet()
{
    if(!source)return;

    /*if(!editControllerID->text().trimmed().isEmpty())
    {
        source->setID(editControllerID->text().trimmed().toInt());
    }*/

    if(!editControllerName->text().trimmed().isEmpty())
    {
        source->setName(editControllerName->text().trimmed());
    }else
    {
        source->setName(QString(tr("NT-Controller%1")).arg(source->ID()));
    }

    if(!editControllerNetID->text().trimmed().isEmpty())
    {
        source->setNetID(editControllerNetID->text().trimmed().toInt());
    }else
    {
        source->setNetID(0);
    }

    source->setControllerType(cmbControllerType->currentText());

    source->setSystemType(cmbControllerSystem->currentText());

    CrtMaster::GetInstance()->ProjectTreeView()->updateItem(source);
}
