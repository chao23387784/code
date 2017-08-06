#include "crtlayer.h"

CrtLayer::CrtLayer(CrtObject *parent) : CrtObject(parent)
{
    setType("layer");
}

void CrtLayer::setScene(CrtScene *s)
{
    if(scene)
    {
        delete scene;
        scene = NULL;
    }

    scene = s;
}

CrtScene *CrtLayer::Scene()
{
    return scene;
}

