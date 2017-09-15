#ifndef WMFVIEW_H
#define WMFVIEW_H
#include <QGraphicsView>
#include <QWheelEvent>

enum ViewStatus
{
    Pan,
    Zoomin,
    Zoomout,
    Edit,
    None
};

class CrtGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    CrtGraphicsView(QWidget *parent = Q_NULLPTR);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void setViewStatus(ViewStatus mode);
    void zoomIn();
    void zoomOut();
signals:
    void dragDone();
private:
    ViewStatus viewStatus;
};

#endif // WMFVIEW_H
