#pragma once
#include <QList>

class CAbstractState
{    
public:
    virtual int GetCurState() const     = 0;
    virtual int ToNextState()           = 0;
    
};


