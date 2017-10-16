#include "crtbackground.h"
#include "wmf/libwmf/WmfPainterBackend.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QPixmap>
#include <QFileInfo>
#include "common.h"

CrtBackground::CrtBackground(QGraphicsItem *parent)
    :QGraphicsItem(parent)
{
    m_bkImage = NULL;
}

CrtBackground::~CrtBackground()
{
    SAFE_DELETE(m_bkImage);
}

QRectF CrtBackground::boundingRect() const
{
    QRectF rect(QPointF(0, 0), m_wmfSize);
    return rect;
}

void CrtBackground::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(m_bkImage == NULL)
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
        painter->drawImage(0,0,*m_bkImage);
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
    SAFE_DELETE(m_bkImage);
    m_wmfFile = wmfFile;
    if(!QFileInfo(m_wmfFile).suffix().compare("wmf"))
    {
        initWmfFile();
    }
    else
    {
        m_bkImage = new QImage(m_wmfFile);
        m_wmfSize = QSizeF((qreal)m_bkImage->width(),(qreal)m_bkImage->height());
    }
}
