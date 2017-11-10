#ifndef CRTCONTROLLERPROPERTYPANEL_H
#define CRTCONTROLLERPROPERTYPANEL_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include "crtcontroller.h"
#include "crtlooppropmodel.h"
#include "crtlooppropdelegate.h"
#include "crtpropview.h"

class CrtControllerPropPanel : public QWidget
{
    Q_OBJECT
public:
    explicit CrtControllerPropPanel(QWidget *parent = 0);
    void initPanel(CrtObject* obj);
signals:

public slots:
    void slotSet();
private:
    QLineEdit* m_editControllerID;
    QLineEdit* m_editControllerName;
    QComboBox* m_cmbControllerType;
    QComboBox* m_cmbControllerSystem;
    QLineEdit* m_editControllerNetID;
    CrtPropView* m_tblLoop;
    QPushButton* m_btnSet;
    CrtController* m_source;
    CrtLoopPropModel* m_model;
    CrtLoopPropDelegate* m_delegate;
};

#endif // CRTCONTROLLERPROPERTYPANEL_H
