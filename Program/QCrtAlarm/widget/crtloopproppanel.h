#ifndef CRTLOOPPROPPANEL_H
#define CRTLOOPPROPPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include "crtloop.h"
#include "crtdevicepropmodel.h"
#include "crtdevicepropdelegate.h"
#include "crtpropview.h"

class CrtLoopPropPanel : public QWidget
{
    Q_OBJECT
public:
    explicit CrtLoopPropPanel(QWidget *parent = 0);
    void initPanel(CrtObject* obj);
signals:

public slots:
    void slotSet();
private:
    QLineEdit* m_editLoopID;
    QLineEdit* m_editLoopName;
    CrtPropView* m_tblDevice;
    QPushButton* m_btnSet;
    CrtLoop* m_source;
    CrtDevicePropModel* m_model;
    CrtDevicePropDelegate* m_delegate;
};

#endif // CRTLOOPPROPPANEL_H
