#ifndef CRTSETDEVICEDLG_H
#define CRTSETDEVICEDLG_H
#include <QDialog>
#include <QComboBox>
#include <QLabel>
#include <QTableView>
#include "crtsetdevicemodel.h"
#include "crtsetdeviceproxymodel.h"

class CrtSetDeviceDlg : public QDialog
{
    Q_OBJECT
public:
    explicit CrtSetDeviceDlg(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~CrtSetDeviceDlg();
protected slots:
    void OnComboItemSelected();
    void OnDragDone();
private:
    QComboBox* cmbProject;
    QComboBox* cmbController;
    QComboBox* cmbLoop;
    QComboBox* cmbDeviceType;
    QTableView* DeviceTable;
    CrtSetDeviceModel* model;
    CrtSetDeviceProxyModel* proxymodel;
};

#endif // CRTSETDEVICEDLG_H
