#include "crttextpropdlg.h"
#include <QLabel>
#include <QPalette>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QGridLayout>
#include <QColorDialog>
#include <QGraphicsScene>

CrtTextPropDlg::CrtTextPropDlg(CrtTextItem *item, QWidget *parent, Qt::WindowFlags f):QDialog(parent,f)
{
    Q_ASSERT(item);

    m_item = item;
    QLabel* labTxt = new QLabel(tr("text:"),this);
    m_editTxt = new QLineEdit(this);
    m_editTxt->setText(m_item->getText());
    QLabel* labColor = new QLabel(tr("color:"),this);
    m_editColor = new QLineEdit(this);
    QPalette pal = m_editColor->palette();
    pal.setColor(QPalette::Base,m_item->getColor());
    m_editColor->setPalette(pal);
    m_editColor->setReadOnly(true);
    QPushButton* btnColor = new QPushButton("...",this);
    QLabel* labSize = new QLabel(tr("size:"),this);
    m_sbSize = new QSpinBox(this);
    m_sbSize->setValue(m_item->getSize());
    QPushButton* btnOk = new QPushButton(tr("ok"),this);
    QPushButton* btnCancel = new QPushButton(tr("cancel"),this);

    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(labTxt,0,0,1,1);
    layout->addWidget(m_editTxt,0,1,1,4);
    layout->addWidget(labColor,1,0,1,1);
    layout->addWidget(m_editColor,1,1,1,4);
    layout->addWidget(btnColor,1,5,1,1);
    layout->addWidget(labSize,2,0,1,1);
    layout->addWidget(m_sbSize,2,1,1,1);
    layout->addWidget(btnOk,3,4,1,1);
    layout->addWidget(btnCancel,3,5,1,1);

    setLayout(layout);

    connect(btnColor,SIGNAL(clicked(bool)),this,SLOT(slotColor()));
    connect(btnOk,SIGNAL(clicked(bool)),this,SLOT(slotOk()));
    connect(btnCancel,SIGNAL(clicked(bool)),this,SLOT(slotCancel()));

    setFixedSize(450,200);

    setAttribute(Qt::WA_DeleteOnClose);
}

CrtTextPropDlg::~CrtTextPropDlg()
{

}

void CrtTextPropDlg::slotOk()
{
    Q_ASSERT(m_item);
    m_item->setText(m_editTxt->text());
    m_item->setColor(m_editColor->palette().color(QPalette::Base));
    m_item->setSize(m_sbSize->value());
    m_item->scene()->update(m_item->scene()->sceneRect());
    close();
}

void CrtTextPropDlg::slotCancel()
{
    close();
}

void CrtTextPropDlg::slotColor()
{
    QColor color = QColorDialog::getColor(m_editColor->palette().color(QPalette::Base), this, tr("text color"));
    if (color.isValid()) {
        QPalette pal = m_editColor->palette();
        pal.setColor(QPalette::Base, color);
        m_editColor->setPalette(pal);
    }
}
