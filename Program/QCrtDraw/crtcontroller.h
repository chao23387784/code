#ifndef CRTCONTROLLER_H
#define CRTCONTROLLER_H

#include <QList>
#include "crtloop.h"
#include "crtobject.h"

class CrtController : public CrtObject
{
public:
    explicit CrtController(CrtObject *parent = 0);
    ~CrtController();
    int getAvaliableLoopID();
public:
    int maxLoopID;
    QList<CrtLoop*> m_lstLoop;
};

#endif // CRTCONTROLLER_H
