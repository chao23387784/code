#include "crtbackground.h"
#include "wmf/libwmf/WmfPainterBackend.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QPixmap>
#include <QFileInfo>

CrtBackground::CrtBackground(QGraphicsItem *parent)
    :QGraphicsItem(parent)
{
    bkImage = NULL;
}

QRectF CrtBackground::boundingRect() const
{
    QRectF rect(QPointF(0, 0), m_wmfSize);
    return rect;
}

void CrtBackground::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(bkImage == NULL)
    {
        Libwmf::WmfPainterBackend backend(painter,m_wmfSize/*QSizeF(80,80)*/);
        backend.load(m_wmfFile);
        painter->save();
        backend.play();
        painter->restore();
    }
    else
    {
        //painter->save();
        painter->drawImage(0,0,*bkImage);
        //painter->restore();
    }
}

void CrtBackground::initWmfFile()
{
    Libwmf::WmfPainterBackend backend(0, QSizeF(0, 0));
    if(!backend.load(m_wmfFile))
        return;
    int xdpi = QApplication::desktop()->logicalDpiX();
    int ydpi = QApplication::desktop()->logicalDpiY();
    int dpi = backend.defaultDpi();

    backend.setOutputSize(backend.boundingRect().width() * 1.0 / dpi * xdpi,
                              backend.boundingRect().height() * 1.0 / dpi * ydpi);

    m_wmfSize = backend.outputSize();
    //m_viewSize = QSizeF(5730 * 1.0 / dpi * xdpi,5227 * 1.0 / dpi * ydpi);
}

void CrtBackground::setWmfFile(const QString& wmfFile)
{
    m_wmfFile = wmfFile;
    if(!QFileInfo(m_wmfFile).suffix().compare("wmf"))
    {
        bkImage = NULL;
        initWmfFile();
    }
    else
    {
        bkImage = new QImage(m_wmfFile);
        m_wmfSize = QSizeF((qreal)bkImage->width(),(qreal)bkImage->height());
    }
}
