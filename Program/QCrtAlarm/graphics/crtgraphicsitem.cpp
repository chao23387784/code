#include "crtgraphicsitem.h"

CrtGraphicsItem::CrtGraphicsItem(QGraphicsItem *parent):QGraphicsItem(parent)
{
    setType(GT_ORIGIN);
}

void CrtGraphicsItem::setType(GraphicsType type)
{
    m_type = type;
}

QPolygonF CrtGraphicsItem::rectToPolygon(const QRectF &rect, const QMatrix &matrix) const
{
    QPolygonF polygon;
    polygon.append(matrix.map(rect.topLeft()));
    polygon.append(matrix.map(rect.topRight()));
    polygon.append(matrix.map(rect.bottomRight()));
    polygon.append(matrix.map(rect.bottomLeft()));
    return polygon;
}
