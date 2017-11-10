#include "crtloopproppanel.h"
#include <QLayout>
#include <QLabel>
#include <QValidator>
#include <QHeaderView>
#include "crtmaster.h"

CrtLoopPropPanel::CrtLoopPropPanel(QWidget *parent) : QWidget(parent)
{
    QLabel* lab = new QLabel(tr("Loop ID:"),this);
    m_editLoopID = new QLineEdit(this);
    m_editLoopID->setReadOnly(true);
    //editLoopID->setValidator(new QIntValidator(1,99,this));
    QLabel* labName = new QLabel(tr("Loop Name:"),this);
    m_editLoopName = new QLineEdit(this);
    m_editLoopName->setMaxLength(256);
    m_tblDevice = new CrtPropView(this);

    m_btnSet = new QPushButton(tr("set"),this);

    QHBoxLayout* layoutTop = new QHBoxLayout(this);
    layoutTop->addWidget(lab);
    layoutTop->addWidget(m_editLoopID);
    layoutTop->addWidget(labName);
    layoutTop->addWidget(m_editLoopName);
    layoutTop->addWidget(m_btnSet);

    QWidget* layoutContainer = new QWidget(this);
    layoutContainer->setLayout(layoutTop);

    QVBoxLayout* layoutMain = new QVBoxLayout(this);
    layoutMain->addWidget(layoutContainer);
    layoutMain->addWidget(m_tblDevice);

    setLayout(layoutMain);

    m_source = NULL;

    connect(m_btnSet,SIGNAL(clicked(bool)),this,SLOT(slotSet()));

    m_model = new CrtDevicePropModel(this);
    m_tblDevice->setModel(m_model);
    m_delegate = new CrtDevicePropDelegate(this);
    m_tblDevice->setItemDelegate(m_delegate);

    m_tblDevice->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(m_delegate,SIGNAL(sigValueChanged(QString)),m_tblDevice,SLOT(slotItemDataChanged(QString)));
}

void CrtLoopPropPanel::initPanel(CrtObject *obj)
{
    if(obj->getType() != OT_LOOP || !m_model)return;

    m_source = dynamic_cast<CrtLoop*>(obj);

    m_editLoopID->setText(QString("%1").arg(m_source->getID()));
    m_editLoopName->setText(m_source->getName());

    m_model->unload();
    m_model->load(obj);
}

void CrtLoopPropPanel::slotSet()
{
    if(!m_source)return;

    /*if(!editLoopID->text().trimmed().isEmpty())
        source->setID(editLoopID->text().trimmed().toInt());*/

    if(!m_editLoopName->text().trimmed().isEmpty())
        m_source->setName(m_editLoopName->text().trimmed());
    else
        m_source->setName(QString(tr("NT-Loop%1")).arg(m_source->getID()));

    CrtMaster::getInstance()->getProjectTreeView()->slotUpdateItem(m_source);
}

