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
    void slotSet();
private:
    CrtPropView* m_tblController;
    QLineEdit* m_editProjectName;
    QPushButton* m_btnSet;
    CrtProject* m_source;
    CrtControllerPropModel* m_model;
    CrtControllerPropDelegate* m_delegate;
};

#endif // CRTPROJECTPROPPANEL_H
