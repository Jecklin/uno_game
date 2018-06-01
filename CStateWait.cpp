#include "CStateWait.h"

CStateWait::CStateWait(FSM *fsm):CAbState(fsm)
{
    ;
}

void CStateWait::onStateEnter()
{
    ;
}

void CStateWait::onStateTick()
{
    //从这里进入
    m_pfsm->curAdd();
    m_pfsm->transState(m_pfsm->State_Start);
    
}

void CStateWait::onStateExit()
{
    ;
}



