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
    void slotSet();
private:
    QPushButton* m_btnSet;
    QComboBox* m_cmbDevTypeList;
    QLineEdit* m_editDeviceName;
    QLineEdit* m_editDeviceID;
    QLineEdit* m_editDeviceZone;
    QLineEdit* m_editDeviceAddress;
    CrtDevice* m_source;
};

#endif // CRTDEVICEPROPPANEL_H
