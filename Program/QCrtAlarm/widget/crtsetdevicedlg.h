#ifndef CRTSETDEVICEDLG_H
#define CRTSETDEVICEDLG_H
#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include "crtsetdevicemodel.h"
#include "crtsetdeviceproxymodel.h"
#include "crtobject.h"
#include "crtsetdeviceview.h"

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
    void slotComboItemSelected();
    void slotDragDone();
private:
    QComboBox* m_cmbProject;
    QComboBox* m_cmbController;
    QComboBox* m_cmbLoop;
    QComboBox* m_cmbDeviceType;
    CrtSetDeviceView* m_DeviceTable;
    CrtSetDeviceModel* m_model;
    CrtSetDeviceProxyModel* m_proxymodel;
};

#endif // CRTSETDEVICEDLG_H
