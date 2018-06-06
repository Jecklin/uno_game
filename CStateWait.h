#ifndef CSTATEWAIT_H
#define CSTATEWAIT_H

#include "CAbState.h"

class CStateWait:public CAbState
{
public:
    CStateWait(FSM *fsm, EGameState state);

//    void onStateEnter();
//    void onStateTick();
//    void onStateExit();
    virtual EGameState      getCurState();
    virtual void            toNextState(EGameState state);
    
};

#endif // CSTATEWAIT_H
