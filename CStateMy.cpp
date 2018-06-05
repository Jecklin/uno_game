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
//    test_counter++;
//    可以设置定时器，暂未添加
    
    //Choice changed
<<<<<<< Updated upstream
    
    if (m_pfsm->getChoice() != -1)
    {
        bool is_giveup = m_pfsm->curPlayerGiveUp(m_pfsm->getChoice());
        if (is_giveup)
        {
            m_pfsm->transState(m_pfsm->State_Add);
        }
        else
        {
            bool is_allow = m_pfsm->curPlayerAllowOut(m_pfsm->getChoice());
            if (is_allow)
=======
    do
    { 
        if (m_pfsm->getChoiceOfNum() != -1)
        {
            bool is_giveup = m_pfsm->curPlayerGiveUp(m_pfsm->getChoiceOfNum());
            if (is_giveup)
>>>>>>> Stashed changes
            {
                m_pfsm->transState(m_pfsm->State_Sub);
            }
            else
            {
<<<<<<< Updated upstream
                m_pfsm->transState(m_pfsm->State_Error);
            }
        }
    }
    else
    {
        m_pfsm->transState(m_pfsm->State_My);
    }
=======
                bool is_allow = m_pfsm->curPlayerAllowOut(m_pfsm->getChoiceOfNum());
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
        else if (m_pfsm->getIsChoiced())
        {
            bool is_allow = m_pfsm->cardAllowOut(m_pfsm->getOutCard());
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
        else
        {
            ;
        }

        
    }while(false);
    
 
>>>>>>> Stashed changes

}

void CStateMy::onStateExit()
{
    ;
}
