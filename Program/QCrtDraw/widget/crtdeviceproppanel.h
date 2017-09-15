#ifndef CRTDEVICEPROPPANEL_H
#define CRTDEVICEPROPPANEL_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include "crtdevice.h"

class CrtDevicePropPanel : public QWidget
{
    Q_OBJECT
public:
    explicit CrtDevicePropPanel(QWidget *parent = 0);
    void initPanel(CrtObject* obj);
signals:

public slots:
    void onSet();
private:
    QPushButton* btnSet;
    QComboBox* cmbDevTypeList;
    QLineEdit* editDeviceName;
    QLineEdit* editDeviceID;
    CrtDevice* source;
};

#endif // CRTDEVICEPROPPANEL_H
