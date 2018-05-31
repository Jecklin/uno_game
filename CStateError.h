#ifndef CSTATEERROR_H
#define CSTATEERROR_H

#include "CAbState.h"

class CStateError:public CAbState
{
public:
    CStateError(FSM *fsm);
    
    void onStateEnter();
    void onStateTick();
    void onStateExit();
};

#endif // CSTATEERROR_H

