#ifndef CRTLAYER_H
#define CRTLAYER_H

#include "crtscene.h"
#include "crtdevice.h"
#include "crtobject.h"
#include <QList>

class CrtLayer : public CrtObject
{
public:
    explicit CrtLayer(CrtObject *parent = 0);
    ~CrtLayer();
    void setScene(CrtScene* s);
    CrtScene* Scene();
private:
    CrtScene* scene;
public:
    QList<CrtDevice*> m_lstDevice;
};

#endif // CRTLAYER_H
