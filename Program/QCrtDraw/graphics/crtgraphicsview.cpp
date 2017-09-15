#include "crtgraphicsview.h"
#include "crtgraphicsscene.h"
#include "crtbackground.h"
#include <QDebug>
#include <QPoint>


CrtGraphicsView::CrtGraphicsView(QWidget *parent)
    :QGraphicsView(parent)
{
    viewStatus = None;

    setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing |
                   QPainter::HighQualityAntialiasing | QPainter::SmoothPixmapTransform);
    //setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setResizeAnchor(AnchorViewCenter);
    //setInteractive(true);

    setTransformationAnchor(AnchorUnderMouse);

    setDragMode(QGraphicsView::RubberBandDrag);
    //setDragMode(QGraphicsView::ScrollHandDrag);
    setAcceptDrops(true);
}

void CrtGraphicsView::wheelEvent(QWheelEvent *event)
{
    if(!scene())
    {
        QGraphicsView::wheelEvent(event);
        return;
    }
   // if(viewStatus == Zoomin || viewStatus == Zoomout)
    //{
        if (event->delta() > 0)
            scale(1.2, 1.2);
        else
            scale(1.0/1.2, 1.0/1.2);
    //}

    event->accept();
}

void CrtGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(!scene())
    {
        QGraphicsView::mousePressEvent(event);
        return;
    }
    /*if (event->button() == Qt::RightButton)
    {
        // If there's a rubber band already started it doesn't autmatically get cleared when we switch to
        // scroll hand mode. We should probably keep track of things properly but it seems to work if you just do this.
        // I'm not sure why buttons has to be 0 here - if you just clear the left button it doesn't work.
        QMouseEvent releaseEvent(QEvent::MouseButtonRelease, event->localPos(), event->screenPos(), event->windowPos(),
                                 Qt::LeftButton, 0, event->modifiers());
        QGraphicsView::mouseReleaseEvent(&releaseEvent);

        setDragMode(QGraphicsView::ScrollHandDrag);
        // We need to pretend it is actually the left button that was pressed!
        QMouseEvent fakeEvent(event->type(), event->localPos(), event->screenPos(), event->windowPos(),
                             Qt::LeftButton, event->buttons() | Qt::LeftButton, event->modifiers());
        QGraphicsView::mousePressEvent(&fakeEvent);
    }
    else
    {
        QGraphicsView::mousePressEvent(event);
    }*/

    if(viewStatus == Pan)
    {
        setDragMode(QGraphicsView::ScrollHandDrag);
    }
    //else if(viewStatus == Edit)
    //{
        /*CrtDeviceItem* item = new CrtDeviceItem(strCurEditDevPath);
        QPointF pt = mapToScene(event->pos());
        item->setPos(pt);
        scene()->addItem(item);*/
    //}

    QGraphicsView::mousePressEvent(event);
}

void CrtGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
}

void CrtGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if(!scene())
    {
        QGraphicsView::mouseReleaseEvent(event);
        return;
    }
    /*if (event->button() == Qt::RightButton)
    {
        QMouseEvent fakeEvent(event->type(), event->localPos(), event->screenPos(), event->windowPos(),
                             Qt::LeftButton, event->buttons() & ~Qt::LeftButton, event->modifiers());
        QGraphicsView::mouseReleaseEvent(&fakeEvent);
        setDragMode(QGraphicsView::RubberBandDrag);
    }
    else
    {
        QGraphicsView::mouseReleaseEvent(event);
    }*/

    QGraphicsView::mouseReleaseEvent(event);
    if(viewStatus == Pan)
    {
        setDragMode(QGraphicsView::RubberBandDrag);
    }
}

void CrtGraphicsView::setViewStatus(ViewStatus mode)
{
    viewStatus = mode;
}

void CrtGraphicsView::zoomIn()
{
    if(scene())
        scale(1.2, 1.2);
}

void CrtGraphicsView::zoomOut()
{
    if(scene())
        scale(1.0/1.2, 1.0/1.2);
}
