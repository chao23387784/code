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
    CrtBackground* getBackground();
    void setBackground(QString strPath);
    CrtLayer* getLayer(){return m_layer;}
protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    CrtBackground* m_backgroundItem;
    CrtLayer* m_layer;
};

#endif // WMFSCENE_H
