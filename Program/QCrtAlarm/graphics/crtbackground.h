#ifndef WMFMAP_H
#define WMFMAP_H
#include <QGraphicsItem>
#include <QImage>

class CrtBackground : public QGraphicsItem
{
public:
    CrtBackground(QGraphicsItem *parent = Q_NULLPTR);
    ~CrtBackground();
    QRectF boundingRect() const;
    void initWmfFile();
    void setWmfFile(const QString& wmfFile);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
private:
    QString m_wmfFile;
    QSizeF m_wmfSize;
    QImage* m_bkImage;
    //QSizeF m_viewSize;
};

#endif // WMFMAP_H
