#ifndef CSTATEMY_H
#define CSTATEMY_H

#include "CAbState.h"

class CStateMy:public CAbState
{
public:
    CStateMy(FSM *fsm);
    
    void onStateEnter();
    void onStateTick();
    void onStateExit();
    
private:
    int test_counter = 0;
    int choice = -1;
};

#endif // CSTATEMY_H
