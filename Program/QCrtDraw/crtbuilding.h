#ifndef CRTBUILDING_H
#define CRTBUILDING_H

#include "crtlayer.h"
#include "crtobject.h"
#include <QList>

class CrtBuilding : public CrtObject
{
public:
    explicit CrtBuilding(CrtObject *parent = 0);
public:
    QList<CrtLayer*> m_lstLayer;
};

#endif // CRTBUILDING_H
