#ifndef CRTWELCOMWIDGET_H
#define CRTWELCOMWIDGET_H

#include <QWidget>

class CrtWelcomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CrtWelcomWidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);

signals:

public slots:
};

#endif // CRTWELCOMWIDGET_H
