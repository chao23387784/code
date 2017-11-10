#include "crtgraphicsview.h"
#include "crtgraphicsscene.h"
#include "crtbackground.h"
#include "crttextitem.h"
#include "common.h"
#include <QDebug>
#include <QPoint>
#include "crttextpropdlg.h"


CrtGraphicsView::CrtGraphicsView(QWidget *parent)
    :QGraphicsView(parent)
{
    m_viewStatus = None;
    m_editStatus = NoOperate;

    m_editText = new QLineEdit;
    m_editText->setVisible(false);

    m_gEditText = new QGraphicsProxyWidget;
    m_gEditText->setWidget(m_editText);

//    m_gEditText = new QGraphicsProxyWidget;
//    m_gEditText->setWidget(m_editText);
    //m_gEditText->setVisible(false);
    connect(m_editText,SIGNAL(returnPressed()),this,SLOT(slotAddTextItem));

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

CrtGraphicsView::~CrtGraphicsView()
{
    SAFE_DELETE(m_editText);
    //SAFE_DELETE(m_gEditText);
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

    if(m_viewStatus == Pan)
    {
        setDragMode(QGraphicsView::ScrollHandDrag);
    }

    if(m_editStatus == SetText)
    {
        if(event->button() == Qt::LeftButton)
        {
            CrtBackground* item = static_cast<CrtGraphicsScene*>(scene())->getBackground();
            QPointF ptItem = item->mapFromScene(mapToScene(event->pos()));
            markText(ptItem);
        }
    }

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
    if(m_viewStatus == Pan)
    {
        setDragMode(QGraphicsView::RubberBandDrag);
    }
}

void CrtGraphicsView::setViewStatus(ViewStatus mode)
{
    m_viewStatus = mode;
}

void CrtGraphicsView::setEditStatue(EditStatus mode)
{
    if(mode == SetText && m_editStatus != SetText)
    {
        scene()->addItem(m_gEditText);
        m_gEditText->setZValue(10);
        m_gEditText->setParentItem(static_cast<CrtGraphicsScene*>(scene())->getBackground());
    }
    else if(mode != SetText && m_editStatus == SetText)
    {
        if(m_gEditText->scene())
        {
            if (m_gEditText->isVisible())
            {
                m_gEditText->setVisible(false);
                slotAddTextItem();
            }
            m_gEditText->scene()->removeItem(m_gEditText);
        }
    }
    m_editStatus = mode;
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

void CrtGraphicsView::markText(QPointF pos)
{
    if(m_editStatus != SetText || m_gEditText == NULL)return;

    if(m_gEditText->scene() != scene())
    {
        scene()->addItem(m_gEditText);
        m_gEditText->setZValue(10);
        m_gEditText->setParentItem(static_cast<CrtGraphicsScene*>(scene())->getBackground());
    }

    QPointF newPos = pos;
    QPointF widgetPos = m_gEditText->pos();
    QRectF widgetRect = m_gEditText->rect();

    if (!m_gEditText->isVisible())
    {
        m_gEditText->setPos(newPos);
        m_editText->setText("");
        m_editText->setVisible(true);
        m_gEditText->setFocus();
    }
    else
    {
        if((newPos.rx() >= widgetPos.rx()) && (newPos.rx() <= widgetPos.rx() + widgetRect.width()) &&
                (newPos.ry() >= widgetPos.ry()) && (newPos.ry() <= widgetPos.ry() + widgetRect.height()))
        {
            return;
        }
        else
        {
            slotAddTextItem();
            m_gEditText->setVisible(false);
        }
    }

}

void CrtGraphicsView::slotAddTextItem()
{
    if(m_gEditText == NULL)return;

    m_gEditText->setVisible(false);
    QString str = m_editText->text();
    if(!str.isEmpty())
    {
        CrtTextItem* item = new CrtTextItem(str);
        QRectF rect = item->boundingRect();
        QPointF postopLeft(m_gEditText->pos().x(), m_gEditText->pos().y() + rect.height() - 5);
        item->setPos(postopLeft);
        scene()->addItem(item);
        item->setZValue(2);
    }
}
