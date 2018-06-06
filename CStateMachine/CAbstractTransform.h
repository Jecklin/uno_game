#ifndef CABSTRACTTRANSFORM_H
#define CABSTRACTTRANSFORM_H

#include "CGame/CGameLoop.h"

class CAbstractTransform
{
public:
    virtual bool transForm()      = 0;
    virtual int  srcState() const = 0;
    virtual int  tarState() const = 0;
};

#endif // CABSTRACTTRANSFORM_H



