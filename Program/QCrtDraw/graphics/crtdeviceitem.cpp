#include "crtdeviceitem.h"
#include <QPainter>
#include "common.h"
#include <QStyleOptionGraphicsItem>
#include "crtmaster.h"
#include "crttreemodel.h"

CrtDeviceItem::CrtDeviceItem(CrtDevice *device, QGraphicsItem *parent)
    :CrtGraphicsItem(parent)
{
    setType(GT_DEVICE);
    m_img = NULL;
    this->m_device = device;
    initItem();
}

CrtDeviceItem::CrtDeviceItem(const QByteArray &imgData, CrtDevice *device, QGraphicsItem *parent):CrtGraphicsItem(parent)
{
    setType(GT_DEVICE);
    m_img = new QImage();
    m_img->loadFromData(imgData);
    this->m_device = device;
    initItem();
}

CrtDeviceItem::CrtDeviceItem(const QString &imgPath, CrtDevice *device, QGraphicsItem *parent):CrtGraphicsItem(parent)
{
    setType(GT_DEVICE);
    m_img = new QImage();
    m_img->load(imgPath);
    this->m_device = device;
    initItem();
}

CrtDeviceItem::~CrtDeviceItem()
{
    SAFE_DELETE(m_img);
}

void CrtDeviceItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->save();
    if(m_img != NULL)
    {
        painter->drawImage(0,0,*m_img);
        if(option->state & QStyle::State_MouseOver)
        {
            QRectF rc = m_img->rect();
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
            QRectF rc = m_img->rect();
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
    if(m_img != NULL)
        return QRectF(0,0,m_img->width(),m_img->height());

    return QRectF();
}

void CrtDeviceItem::setImage(const QString &imgPath)
{
    if(!m_img)
        m_img = new QImage();
    m_img->load(imgPath);
}

void CrtDeviceItem::initItem()
{
        setAcceptHoverEvents(true);
        setFlag(QGraphicsItem::ItemIsSelectable, true);
        setFlag(QGraphicsItem::ItemIsMovable, true);
        setToolTip(QString().sprintf("Controller ID : %02d\r\n"
                                     "Loop ID : %02d\r\n"
                                     "Device ID : %03d",
                                     m_device->getParent()->getParent()->getID(),
                                     m_device->getParent()->getID(),m_device->getID()));
}

void CrtDeviceItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QModelIndex index = static_cast<CrtTreeModel*>(CrtMaster::getInstance()->getProjectTreeView()->model())->indexFromItem(m_device);
    if(index.isValid())
    {
        CrtMaster::getInstance()->getProjectTreeView()->setCurrentIndex(index);
    }
    QGraphicsItem::mouseDoubleClickEvent(event);
}
