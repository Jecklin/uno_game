#include "CStateError.h"

CStateError::CStateError(FSM *fsm):CAbState(fsm)
{
    
}

void CStateError::onStateEnter()
{
    
}

void CStateError::onStateTick()
{
    m_pfsm->transState(m_pfsm->State_My);
}

void CStateError::onStateExit()
{
    
}
