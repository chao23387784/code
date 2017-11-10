#ifndef CRTGRAPHICSITEM_H
#define CRTGRAPHICSITEM_H
#include <QGraphicsItem>

enum GraphicsType
{
    GT_ORIGIN,
    GT_DEVICE,
    GT_TEXT
};

class CrtGraphicsItem : public QGraphicsItem
{
public:
    explicit CrtGraphicsItem(QGraphicsItem *parent = 0);
    void setType(GraphicsType type);
    GraphicsType getType(){return m_type;}
    QPolygonF rectToPolygon(const QRectF &rect, const QMatrix &matrix) const;
private:
    GraphicsType m_type;
};

#endif // CRTGRAPHICSITEM_H
