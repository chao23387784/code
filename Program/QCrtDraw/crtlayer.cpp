#include "crtlayer.h"

CrtLayer::CrtLayer(CrtObject *parent) : CrtObject(parent)
{
    setType("layer");
}

CrtLayer::~CrtLayer()
{
    m_lstDevice.clear();
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

