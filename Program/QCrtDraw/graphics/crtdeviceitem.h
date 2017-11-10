#ifndef CRTDEVICEITEM_H
#define CRTDEVICEITEM_H
#include <QImage>
#include <QByteArray>
#include "crtdevice.h"
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneWheelEvent>
#include "crtgraphicsitem.h"

class CrtDevice;

class CrtDeviceItem : public CrtGraphicsItem
{
public:
    CrtDeviceItem(CrtDevice* device,QGraphicsItem *parent = Q_NULLPTR);
    ~CrtDeviceItem();
    CrtDeviceItem(const QByteArray& imgData,CrtDevice* device,QGraphicsItem *parent = Q_NULLPTR);
    CrtDeviceItem(const QString& imgPath,CrtDevice* device,QGraphicsItem *parent = Q_NULLPTR);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    QRectF boundingRect() const;
    CrtDevice* getDevice(){return m_device;}
    void setImage(const QString& imgPath);
    void initItem();
protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
private:
    QImage* m_img;
    CrtDevice* m_device;
};

#endif // CRTDEVICEITEM_H
