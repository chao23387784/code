#ifndef WMFVIEW_H
#define WMFVIEW_H
#include <QGraphicsView>
#include <QWheelEvent>

enum ViewMode
{
    Pan,
    Zoomin,
    Zoomout,
    Edit,
    None
};

class CrtView : public QGraphicsView
{
public:
    CrtView(QWidget *parent = Q_NULLPTR);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void setViewMode(ViewMode mode);
    void setEditDevicePath(QString strDevPath);
private:
    ViewMode viewMode;
    QString strCurEditDevPath;
};

#endif // WMFVIEW_H
