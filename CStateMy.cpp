#include "CStateMy.h"


CStateMy::CStateMy(FSM *fsm):CAbState(fsm)
{
    ;
}

void CStateMy::onStateEnter()
{
    test_counter = 0;

}

void CStateMy::onStateTick()
{
    
    //Choice changed
    do
    { 
        if (m_pfsm->getChoice() != -1)
        {
            bool is_giveup = m_pfsm->curPlayerGiveUp(m_pfsm->getChoice());
            if (is_giveup)
            {
                m_pfsm->transState(m_pfsm->State_Add);
                break;
            }
            else
            {
                bool is_allow = m_pfsm->curPlayerAllowOut(m_pfsm->getChoice());
                if (is_allow)
                {
                    m_pfsm->transState(m_pfsm->State_Sub);
                    break;
                }
                else
                {
                    m_pfsm->transState(m_pfsm->State_Error);
                    break;
                }
            }
        }
        else
        {
            ;
        }

        
    }while(false);
    
 

}

void CStateMy::onStateExit()
{
    ;
}
