#include "crtdeviceitem.h"
#include <QPainter>
#include "common.h"
#include <QStyleOptionGraphicsItem>
#include "crtmaster.h"
#include "crttreemodel.h"

CrtDeviceItem::CrtDeviceItem(CrtDevice *device, QGraphicsItem *parent)
    :QGraphicsItem(parent)
{
    img = NULL;
    this->device = device;
    initItem();
}

CrtDeviceItem::CrtDeviceItem(const QByteArray &imgData, CrtDevice *device, QGraphicsItem *parent)
{
    Q_UNUSED(parent);
    img = new QImage();
    img->loadFromData(imgData);
    this->device = device;
    initItem();
}

CrtDeviceItem::CrtDeviceItem(const QString &imgPath, CrtDevice *device, QGraphicsItem *parent)
{
    Q_UNUSED(parent);
    img = new QImage();
    img->load(imgPath);
    this->device = device;
    initItem();
}

CrtDeviceItem::~CrtDeviceItem()
{
    SAFE_DELETE(img);
}

void CrtDeviceItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->save();
    if(img != NULL)
    {
        painter->drawImage(0,0,*img);
        if(option->state & QStyle::State_MouseOver)
        {
            QRectF rc = img->rect();
            QMatrix oldMatrix = painter->matrix();
            QPolygonF polygon = rectToPolygon(rc, oldMatrix);
            painter->resetMatrix();
            QPen pen(Qt::red, 2, Qt::DotLine, Qt::SquareCap, Qt::MiterJoin);
            painter->setPen(pen);
            if(option->state & QStyle::State_Selected)
            {
                QBrush brush(QColor(0, 200, 255, 100), Qt::SolidPattern);
                painter->setBrush(brush);
            }
            painter->drawPolygon(polygon);
            painter->setMatrix(oldMatrix);
        }
        else if(option->state & QStyle::State_Selected)
        {
            QRectF rc = img->rect();
            QMatrix oldMatrix = painter->matrix();
            QPolygonF polygon = rectToPolygon(rc, oldMatrix);
            painter->resetMatrix();
            QPen pen(Qt::red, 2, Qt::DotLine, Qt::SquareCap, Qt::MiterJoin);
            painter->setPen(pen);
            QBrush brush(QColor(0, 200, 255, 100), Qt::SolidPattern);
            painter->setBrush(brush);
            painter->drawPolygon(polygon);
            painter->setMatrix(oldMatrix);
        }
    }
    painter->restore();
}

QRectF CrtDeviceItem::boundingRect() const
{
    if(img != NULL)
        return QRectF(0,0,img->width(),img->height());

    return QRectF();
}

void CrtDeviceItem::setImage(const QString &imgPath)
{
    if(!img)
        img = new QImage();
    img->load(imgPath);
}

void CrtDeviceItem::initItem()
{
        setAcceptHoverEvents(true);
        setFlag(QGraphicsItem::ItemIsSelectable, true);
        setFlag(QGraphicsItem::ItemIsMovable, true);
        setToolTip(QString().sprintf("Controller ID : %02d\r\n"
                                     "Loop ID : %02d\r\n"
                                     "Device ID : %03d",
                                     device->Parent()->Parent()->ID(),
                                     device->Parent()->ID(),device->ID()));
}

void CrtDeviceItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverEnterEvent(event);
}

void CrtDeviceItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverLeaveEvent(event);
}

void CrtDeviceItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverMoveEvent(event);
}

void CrtDeviceItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QModelIndex index = static_cast<CrtTreeModel*>(CrtMaster::GetInstance()->ProjectTreeView()->model())->indexFromItem(device);
    if(index.isValid())
    {
        CrtMaster::GetInstance()->ProjectTreeView()->setCurrentIndex(index);
    }
    QGraphicsItem::mouseDoubleClickEvent(event);
}

QPolygonF CrtDeviceItem::rectToPolygon(const QRectF &rect, const QMatrix &matrix) const
{
    QPolygonF polygon;
    polygon.append(matrix.map(rect.topLeft()));
    polygon.append(matrix.map(rect.topRight()));
    polygon.append(matrix.map(rect.bottomRight()));
    polygon.append(matrix.map(rect.bottomLeft()));
    return polygon;
}
