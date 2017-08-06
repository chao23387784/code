#ifndef WMFSCENE_H
#define WMFSCENE_H
#include <QGraphicsScene>
#include "crtbackground.h"
#include "crtdeviceitem.h"
#include <QList>

class CrtScene : public QGraphicsScene
{
public:
    CrtScene(QObject *parent = Q_NULLPTR);
    CrtBackground* Background();
    void setBackground(CrtBackground* pBackground);
private:
    CrtBackground* backgroundItem;
    QList<CrtDeviceItem*> lstDeivce;
};

#endif // WMFSCENE_H
