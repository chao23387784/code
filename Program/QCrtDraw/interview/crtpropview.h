#ifndef CRTPROPVIEW_H
#define CRTPROPVIEW_H
#include <QTableView>
#include <QMouseEvent>

class CrtPropView : public QTableView
{
    Q_OBJECT
public:
    explicit CrtPropView(QWidget *parent = 0);
public slots:
    void itemDataChanged(QString value);
protected:
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // CRTPROPVIEW_H
