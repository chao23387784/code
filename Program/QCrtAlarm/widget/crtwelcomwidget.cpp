#include "crtwelcomwidget.h"
#include <QPainter>

CrtWelcomWidget::CrtWelcomWidget(QWidget *parent) : QWidget(parent)
{
   /*setAutoFillBackground(true);
   QPalette palette;
   QPixmap pixmap(":/img/neatlogo2.jpg");
   palette.setBrush(QPalette::Window, QBrush(pixmap));
   setPalette(palette);*/
}

void CrtWelcomWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QPixmap img(":/img/qt.jpg");
    painter.drawPixmap((this->width()-img.width())/2,(this->height()-img.height())/2,
                       img.width(),img.height(),QPixmap(":/img/qt.jpg"));
}

