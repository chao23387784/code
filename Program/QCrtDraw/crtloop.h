#ifndef CRTLOOP_H
#define CRTLOOP_H

#include <QList>
#include "crtdevice.h"
#include "crtobject.h"

class CrtLoop : public CrtObject
{
public:
    explicit CrtLoop(CrtObject *parent = 0);
    ~CrtLoop();
public:
    QList<CrtDevice*> m_lstDevice;
};

#endif // CRTLOOP_H
