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
    void onSet();
private:
    QLineEdit* editControllerID;
    QLineEdit* editControllerName;
    QComboBox* cmbControllerType;
    QComboBox* cmbControllerSystem;
    QLineEdit* editControllerNetID;
    CrtPropView* tblLoop;
    QPushButton* btnSet;
    CrtController* source;
    CrtLoopPropModel* model;
    CrtLoopPropDelegate* delegate;
};

#endif // CRTCONTROLLERPROPERTYPANEL_H
