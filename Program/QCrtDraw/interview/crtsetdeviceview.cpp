#include "crtsetdeviceview.h"
#include <QMimeData>
#include <QDrag>
#include <QMouseEvent>
#include "crtdevice.h"
#include "crtsetdeviceproxymodel.h"

CrtSetDeviceView::CrtSetDeviceView(QWidget *parent) : QTableView(parent)
{
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
}

void CrtSetDeviceView::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        QModelIndex index = currentIndex();
        if(index.isValid())
        {
            QByteArray itemData;
            QDataStream dataStream(&itemData, QIODevice::WriteOnly);
            QModelIndex s_index = dynamic_cast<CrtSetDeviceProxyModel*>(model())->mapToSource(index);
            if(s_index.isValid())
            {
                CrtObject* node = (CrtObject*)s_index.internalPointer();
                if (node && node->getType() == OT_DEVICE && !dynamic_cast<CrtDevice*>(node)->isOnMap())
                {
                    dataStream << reinterpret_cast<qlonglong>(node);
                    QMimeData *data = new QMimeData;
                    data->setData("project/items",itemData);
                    QDrag* drag = new QDrag(this);
                    drag->setMimeData(data);
                    drag->setPixmap(QPixmap(QString(":/device/%1.bmp").arg(dynamic_cast<CrtDevice*>(node)->getDeviceType())));
                    drag->exec(Qt::MoveAction);
                }
            }
        }
    }
}
