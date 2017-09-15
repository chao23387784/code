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
    void onSet();
private:
    QLineEdit* editLoopID;
    QLineEdit* editLoopName;
    CrtPropView* tblDevice;
    QPushButton* btnSet;
    CrtLoop* source;
    CrtDevicePropModel* model;
    CrtDevicePropDelegate* delegate;
};

#endif // CRTLOOPPROPPANEL_H
