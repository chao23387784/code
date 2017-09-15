#ifndef CRTPROJECTPROPPANEL_H
#define CRTPROJECTPROPPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include "crtproject.h"
#include "crtcontrollerpropmodel.h"
#include "crtcontrollerpropdelegate.h"
#include "crtpropview.h"

class CrtProjectPropPanel : public QWidget
{
    Q_OBJECT
public:
    explicit CrtProjectPropPanel(QWidget *parent = 0);
    void initPanel(CrtObject* obj);
signals:

public slots:
    void onSet();
private:
    CrtPropView* tblController;
    QLineEdit* editProjectName;
    QPushButton* btnSet;
    CrtProject* source;
    CrtControllerPropModel* model;
    CrtControllerPropDelegate* delegate;
};

#endif // CRTPROJECTPROPPANEL_H
