#include "crtprojectproppanel.h"
#include <QLayout>
#include <QValidator>
#include <QHeaderView>
#include "crtmaster.h"


CrtProjectPropPanel::CrtProjectPropPanel(QWidget *parent) : QWidget(parent)
{
    QLabel* lab = new QLabel(tr("Project Name:"),this);
    m_editProjectName = new QLineEdit(this);
    m_editProjectName->setMaxLength(256);
    m_tblController = new CrtPropView(this);
    m_btnSet = new QPushButton(tr("set"),this);

    QHBoxLayout* layoutTop = new QHBoxLayout(this);
    layoutTop->addWidget(lab);
    layoutTop->addWidget(m_editProjectName);
    layoutTop->addWidget(m_btnSet);

    QWidget* layoutContainer = new QWidget(this);
    layoutContainer->setLayout(layoutTop);

    QVBoxLayout* layoutMain = new QVBoxLayout(this);
    layoutMain->addWidget(layoutContainer);
    layoutMain->addWidget(m_tblController);

    setLayout(layoutMain);

    m_source = NULL;

    connect(m_btnSet,SIGNAL(clicked(bool)),this,SLOT(slotSet()));

    m_model = new CrtControllerPropModel(this);
    m_tblController->setModel(m_model);
    m_delegate = new CrtControllerPropDelegate(this);
    m_tblController->setItemDelegate(m_delegate);

    m_tblController->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(m_delegate,SIGNAL(sigValueChanged(QString)),m_tblController,SLOT(slotItemDataChanged(QString)));
}

void CrtProjectPropPanel::initPanel(CrtObject *obj)
{
    if(!obj || obj->getType().compare("project") || !m_model)return;

    m_source = dynamic_cast<CrtProject*>(obj);

    m_editProjectName->setText(m_source->getName());

    m_model->unload();
    m_model->load(obj);
}

void CrtProjectPropPanel::slotSet()
{
    if(m_editProjectName->text().trimmed().isEmpty() || !m_source)return;
    m_source->setName(m_editProjectName->text().trimmed());
    CrtMaster::getInstance()->getProjectTreeView()->slotUpdateItem(m_source);
}

