#include "crtscene.h"

CrtScene::CrtScene(QObject *parent)
    :QGraphicsScene(parent)
{

}

CrtBackground *CrtScene::Background()
{
    if(backgroundItem!=NULL)
        return backgroundItem;
    return NULL;
}

void CrtScene::setBackground(CrtBackground* pBackground)
{
    backgroundItem = pBackground;
}
