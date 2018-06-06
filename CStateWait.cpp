#include "CStateWait.h"

CStateWait::CStateWait(FSM *fsm, EGameState state):CAbState(fsm, state)
{
    ;
}

EGameState CStateWait::getCurState()
{
    return this->m_curState;
}

void CStateWait::toNextState(EGameState state)
{
    
}

//void CStateWait::onStateEnter()
//{
//    ;
//}

//void CStateWait::onStateTick()
//{
//    //从这里进入
//    m_pfsm->transState(m_pfsm->State_Start);
    
//}

//void CStateWait::onStateExit()
//{
//    ;
//}



