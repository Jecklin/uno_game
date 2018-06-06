#ifndef CABSTATE_H
#define CABSTATE_H

#include <iostream>
#include "FSM.h"
#include "datatypedefine.h"

using namespace std;

class FSM;

class CAbState
{
public:
    CAbState(FSM *pfsm, EGameState state)
    {
        m_pfsm      = pfsm;
        m_curState  = state;
    }
    virtual ~CAbState(){}
    

    
public:
//    virtual void onStateEnter() = 0;
//    virtual void onStateTick()  = 0;
//    virtual void onStateExit()  = 0;
    
    virtual EGameState      getCurState()   = 0;
    virtual void            toNextState(EGameState state)   = 0;
    
protected:

    FSM                       *m_pfsm;
    EGameState                 m_curState;                     //当前状态
    
};

#endif // CABSTATE_H
