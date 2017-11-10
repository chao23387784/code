#include "crttextitem.h"
#include <QStyleOptionGraphicsItem>
#include <QFontMetrics>
#include <QPainter>
#include <QApplication>
#include "crttextpropdlg.h"

CrtTextItem::CrtTextItem(QGraphicsItem *parent):CrtGraphicsItem(parent)
{
    setType(GT_TEXT);
    initItem();
}

CrtTextItem::~CrtTextItem()
{

}

CrtTextItem::CrtTextItem(const QString &txt, QGraphicsItem *parent):CrtGraphicsItem(parent)
{
    setType(GT_TEXT);
    initItem();
    setText(txt);
}

void CrtTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    painter->save();
    QFont font = QApplication::font();
    font.setPointSize(m_nSize);
    painter->setFont(font);
    painter->setPen(m_color);
    painter->drawText(option->rect, Qt::TextSingleLine, m_strText);

    if(option->state & QStyle::State_MouseOver)
    {
        QMatrix oldMatrix = painter->matrix();
        QPolygonF polygon = rectToPolygon(option->rect, oldMatrix);
        painter->resetMatrix();
        QPen pen(Qt::green, 2, Qt::DotLine, Qt::SquareCap, Qt::MiterJoin);
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
        QMatrix oldMatrix = painter->matrix();
        QPolygonF polygon = rectToPolygon(option->rect, oldMatrix);
        painter->resetMatrix();
        QPen pen(Qt::green, 2, Qt::DotLine, Qt::SquareCap, Qt::MiterJoin);
        painter->setPen(pen);
        QBrush brush(QColor(0, 200, 255, 100), Qt::SolidPattern);
        painter->setBrush(brush);
        painter->drawPolygon(polygon);
        painter->setMatrix(oldMatrix);
    }

    painter->restore();
}

QRectF CrtTextItem::boundingRect() const
{
    QFontMetrics fm(QFont(QApplication::font().family(),m_nSize));
    return fm.boundingRect(m_strText);
}

void CrtTextItem::setText(const QString &txt)
{
    m_strText = txt;
}

void CrtTextItem::setColor(const QColor &color)
{
    m_color = color;
}

void CrtTextItem::setSize(int s)
{
    if(s <= 0)return;
    m_nSize = s;
}

void CrtTextItem::initItem()
{
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    m_nSize = 12;
    m_color = QColor(255,0,0);
}

void CrtTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    CrtTextPropDlg* dlg = new CrtTextPropDlg(this);
    dlg->exec();
}
