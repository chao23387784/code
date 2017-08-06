#include "crtdeviceitem.h"
#include <QPainter>

CrtDeviceItem::CrtDeviceItem(QGraphicsItem *parent)
    :QGraphicsItem(parent)
{
    img = NULL;
}

CrtDeviceItem::CrtDeviceItem(const QByteArray &imgData, QGraphicsItem *parent)
    :QGraphicsItem(parent)
{
    img = new QImage();
    img->loadFromData(imgData);
}

CrtDeviceItem::CrtDeviceItem(const QString &imgPath, QGraphicsItem *parent)
    :QGraphicsItem(parent)
{
    img = new QImage();
    img->load(imgPath);
}

void CrtDeviceItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(img != NULL)
    {
        painter->drawImage(0,0,*img);
    }
}

QRectF CrtDeviceItem::boundingRect() const
{
    if(img != NULL)
        return QRectF(0,0,img->width(),img->height());

    return QRectF();
}
