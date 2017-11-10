#include "crtcontrollerproppanel.h"
#include <QLabel>
#include <QLayout>
#include "crtcontroller.h"
#include "crtmaster.h"
#include <QValidator>
#include <QHeaderView>
#include "crtmaster.h"


CrtControllerPropPanel::CrtControllerPropPanel(QWidget *parent) : QWidget(parent)
{
    QLabel* labID = new QLabel(tr("Controller ID:"),this);
    m_editControllerID = new QLineEdit(this);
    m_editControllerID->setReadOnly(true);
    //editControllerID->setValidator(new QIntValidator(1,999,this));

    QLabel* labName = new QLabel(tr("Controller Name:"),this);
    m_editControllerName = new QLineEdit(this);
    m_editControllerName->setMaxLength(256);

    QLabel* labNetID = new QLabel(tr("NetID:"),this);
    m_editControllerNetID = new QLineEdit(this);
    m_editControllerNetID->setValidator(new QIntValidator(0,999,this));

    QLabel* labType = new QLabel(tr("Controller Type:"),this);
    m_cmbControllerType = new QComboBox(this);
    m_cmbControllerType->addItems(*(CrtMaster::getInstance()->getControllerType()));

    QLabel* labSystem = new QLabel(tr("System Type:"),this);
    m_cmbControllerSystem = new QComboBox(this);
    m_cmbControllerSystem->addItems(*(CrtMaster::getInstance()->getSystemType()));

    m_btnSet = new QPushButton(tr("set"),this);

    m_tblLoop = new CrtPropView(this);

    QHBoxLayout* layoutTop1 = new QHBoxLayout(this);
    layoutTop1->addWidget(labID);
    layoutTop1->addWidget(m_editControllerID);
    layoutTop1->addWidget(labName);
    layoutTop1->addWidget(m_editControllerName);
    layoutTop1->addWidget(labNetID);
    layoutTop1->addWidget(m_editControllerNetID);

    QWidget* layoutContainer1 = new QWidget(this);
    layoutContainer1->setLayout(layoutTop1);

    QHBoxLayout* layoutTop2 = new QHBoxLayout(this);
    layoutTop2->addWidget(labType);
    layoutTop2->addWidget(m_cmbControllerType);
    layoutTop2->addWidget(labSystem);
    layoutTop2->addWidget(m_cmbControllerSystem);
    layoutTop2->addStretch(2);
    layoutTop2->addWidget(m_btnSet);
    layoutTop2->setStretchFactor(labType,1);
    layoutTop2->setStretchFactor(m_cmbControllerType,3);
    layoutTop2->setStretchFactor(labSystem,1);
    layoutTop2->setStretchFactor(m_cmbControllerSystem,3);
    layoutTop2->setStretchFactor(m_btnSet,1);

    QWidget* layoutContainer2 = new QWidget(this);
    layoutContainer2->setLayout(layoutTop2);

    QVBoxLayout* layoutMain = new QVBoxLayout(this);
    layoutMain->addWidget(layoutContainer1);
    layoutMain->addWidget(layoutContainer2);
    layoutMain->addWidget(m_tblLoop);

    setLayout(layoutMain);

    m_source = NULL;

    connect(m_btnSet,SIGNAL(clicked(bool)),this,SLOT(slotSet()));

    m_model = new CrtLoopPropModel(this);
    m_tblLoop->setModel(m_model);
    m_delegate = new CrtLoopPropDelegate(this);
    m_tblLoop->setItemDelegate(m_delegate);

    m_tblLoop->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(m_delegate,SIGNAL(sigValueChanged(QString)),m_tblLoop,SLOT(slotItemDataChanged(QString)));
}

void CrtControllerPropPanel::initPanel(CrtObject *obj)
{
    if(!obj || obj->getType() != OT_CONTROLLER || !m_model)return;

    m_source = dynamic_cast<CrtController*>(obj);

    m_editControllerID->setText(QString("%1").arg(m_source->getID()));
    m_editControllerName->setText(m_source->getName());
    m_editControllerNetID->setText(QString("%1").arg(m_source->getNetID()));

    int nIndex = m_cmbControllerType->findText(m_source->getControllerType());
    nIndex == -1 ? m_cmbControllerType->setCurrentText(m_source->getControllerType()) :
                   m_cmbControllerType->setCurrentIndex(nIndex);

    nIndex = m_cmbControllerSystem->findText(m_source->getSystemType());
    nIndex == -1 ? m_cmbControllerSystem->setCurrentText(m_source->getSystemType()) :
                   m_cmbControllerSystem->setCurrentIndex(nIndex);

    m_model->unload();
    m_model->load(obj);
}

void CrtControllerPropPanel::slotSet()
{
    if(!m_source)return;

    /*if(!editControllerID->text().trimmed().isEmpty())
    {
        source->setID(editControllerID->text().trimmed().toInt());
    }*/

    if(!m_editControllerName->text().trimmed().isEmpty())
    {
        m_source->setName(m_editControllerName->text().trimmed());
    }else
    {
        m_source->setName(QString(tr("NT-Controller%1")).arg(m_source->getID()));
    }

    if(!m_editControllerNetID->text().trimmed().isEmpty())
    {
        m_source->setNetID(m_editControllerNetID->text().trimmed().toInt());
    }else
    {
        m_source->setNetID(0);
    }

    m_source->setControllerType(m_cmbControllerType->currentText());

    m_source->setSystemType(m_cmbControllerSystem->currentText());

    CrtMaster::getInstance()->getProjectTreeView()->slotUpdateItem(m_source);
}
