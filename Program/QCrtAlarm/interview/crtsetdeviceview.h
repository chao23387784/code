#ifndef CRTSETDEVICEVIEW_H
#define CRTSETDEVICEVIEW_H
#include <QTableView>


class CrtSetDeviceView : public QTableView
{
public:
    CrtSetDeviceView(QWidget *parent = 0);
protected:
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // CRTSETDEVICEVIEW_H
