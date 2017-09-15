#ifndef WMFSCENE_H
#define WMFSCENE_H
#include <QGraphicsScene>
#include "crtbackground.h"
#include "crtdeviceitem.h"
#include <QList>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

class CrtLayer;

class CrtGraphicsScene : public QGraphicsScene
{
public:
    CrtGraphicsScene(QObject *parent = Q_NULLPTR);
    CrtGraphicsScene(CrtLayer *layer);
    ~CrtGraphicsScene();
    CrtBackground* Background();
    void setBackground(QString strPath);
    CrtLayer* Layer(){return layer;}
protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void keyPressEvent(QKeyEvent *event);
private:
    CrtBackground* backgroundItem;
    CrtLayer* layer;
};

#endif // WMFSCENE_H
