#ifndef CRTSETDEVICEDLG_H
#define CRTSETDEVICEDLG_H
#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QTableView>
#include "crtsetdevicemodel.h"
#include "crtsetdeviceproxymodel.h"
#include "crtobject.h"

class CrtSetDeviceDlg : public QWidget
{
    Q_OBJECT
public:
    explicit CrtSetDeviceDlg(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~CrtSetDeviceDlg();
    void loadData();
    void releaseData();
    CrtObject* getCurrentObject();
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
