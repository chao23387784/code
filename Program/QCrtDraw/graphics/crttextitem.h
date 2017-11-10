#ifndef CRTTEXTITEM_H
#define CRTTEXTITEM_H
#include <QColor>
#include "crtgraphicsitem.h"

class CrtTextItem : public CrtGraphicsItem
{
public:
    CrtTextItem(QGraphicsItem *parent = 0);
    ~CrtTextItem();
    CrtTextItem(const QString& txt,QGraphicsItem *parent = Q_NULLPTR);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    QRectF boundingRect() const;
    void setText(const QString& txt);
    QString getText(){return m_strText;}
    void setColor(const QColor &color);
    QColor getColor(){return m_color;}
    void setSize(int s);
    int getSize(){return m_nSize;}

    void initItem();
    //QPolygonF rectToPolygon(const QRectF &rect, const QMatrix &matrix) const;
protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
private:
    QString m_strText;
    QColor m_color;
    int m_nSize;
};

#endif // CRTTEXTITEM_H
