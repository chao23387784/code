#ifndef CRTDEVICEITEM_H
#define CRTDEVICEITEM_H
#include <QGraphicsItem>
#include <QImage>
#include <QByteArray>

class CrtDeviceItem : public QGraphicsItem
{
public:
    CrtDeviceItem(QGraphicsItem *parent = Q_NULLPTR);
    CrtDeviceItem(const QByteArray& imgData,QGraphicsItem *parent = Q_NULLPTR);
    CrtDeviceItem(const QString& imgPath,QGraphicsItem *parent = Q_NULLPTR);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    QRectF boundingRect() const;
private:
    QImage* img;
};

#endif // CRTDEVICEITEM_H
