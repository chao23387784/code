#ifndef WMFVIEW_H
#define WMFVIEW_H
#include <QGraphicsView>
#include <QWheelEvent>
#include <QLineEdit>
#include <QGraphicsProxyWidget>

enum ViewStatus
{
    Pan,
    Zoomin,
    Zoomout,
    Edit,
    None
};

enum EditStatus
{
    SetDevice,
    SetText,
    NoOperate
};

class CrtGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    CrtGraphicsView(QWidget *parent = Q_NULLPTR);
    ~CrtGraphicsView();
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void setViewStatus(ViewStatus mode);
    void setEditStatue(EditStatus mode);
    EditStatus getEditStatus(){return m_editStatus;}
    void zoomIn();
    void zoomOut();
    void markText(QPointF pos);
signals:
    void sigDropDevice();
private slots:
    void slotAddTextItem();
private:
    ViewStatus m_viewStatus;
    EditStatus m_editStatus;
public:
    QLineEdit* m_editText;
    QGraphicsProxyWidget* m_gEditText;
};

#endif // WMFVIEW_H
