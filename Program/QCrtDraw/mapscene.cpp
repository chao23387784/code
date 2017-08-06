#include "mapscene.h"
#include <QDataStream>
#include <QFile>

MapScene::MapScene(QObject *parent):
    QGraphicsScene(parent)
{
}

void MapScene::drawBackground(QPainter* painter, const QRectF& rect)
{
    Libwmf::WmfPainterBackend backend(painter, QSizeF(sceneRect().width(),sceneRect().height()));
    backend.load(m_wmfPath);
    painter->save();
    backend.play();
    painter->restore();
}

void MapScene::LoadWmfData(const QString &filepath)
{
    m_wmfPath = filepath;
}
