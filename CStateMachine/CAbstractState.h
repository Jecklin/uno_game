#ifndef CABSTRACTSTATE_H
#define CABSTRACTSTATE_H

#include <iostream>

class CAbstractState
{    
public:
    virtual int getCurState() const     = 0;
    virtual int toNextState()           = 0;
};

#endif // CABSTRACTSTATE_H
