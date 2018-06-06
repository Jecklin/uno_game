#include "FSM.h"
#include "CStateWait.h"
#include "CStateStart.h"
#include "CStateMy.h"
#include "CStateOther.h"
#include "CStateAdd.h"
#include "CStateSub.h"
#include "CStateEnd.h"
#include "CStateError.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

FSM::FSM()
    :m_states()
    ,m_curState(-1)
    ,m_game_loop(nullptr)
{
    
}

FSM::~FSM()
{
    if (this->m_game_loop == nullptr)
    {
        ;
    }
    else
    {
        delete this->m_game_loop;
        this->m_game_loop = nullptr;
    }
}

bool FSM::registerState(int e, CAbState *pState)
{
    m_states[e] = pState;
    return true;
}

bool FSM::transState(int newState)
{
    m_states[m_curState]->onStateExit();
    m_states[newState]->onStateEnter();
    m_curState = newState;
    return true;
}

void FSM::initFSM()
{
    std::cout << "**** Begin **** Begin **** Begin **** Begin **** Begin ****" << std::endl << std::endl;
    //InitCurState
    m_curState = State_Wait;
    this->m_game_loop = new CGameLoop();
    
    CAbState *m_stateWait   = new CStateWait(*this);
    CAbState *m_stateStart  = new CStateStart(*this);
    CAbState *m_stateMy     = new CStateMy(*this);
    CAbState *m_stateOther  = new CStateOther(*this);
    CAbState *m_stateAdd    = new CStateAdd(*this);
    CAbState *m_stateSub    = new CStateSub(*this);
    CAbState *m_stateEnd    = new CStateEnd(*this);
    CAbState *m_stateError  = new CStateError(*this);
    
    this->registerState(State_Wait, m_stateWait);
    this->registerState(State_Start, m_stateStart);
    this->registerState(State_My, m_stateMy);
    this->registerState(State_Other, m_stateOther);
    this->registerState(State_Add, m_stateAdd);
    this->registerState(State_Sub, m_stateSub);
    this->registerState(State_End, m_stateEnd);
    this->registerState(State_Error, m_stateError);
        
}

void FSM::tick()
{
    m_states[m_curState]->onStateTick();
}


