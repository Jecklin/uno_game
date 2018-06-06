#include "CStateMachine.h"
#include "CGameLoop.h"
#include "CState.h"
#include "CTFWaitToMy.h"

CStateMachine::CStateMachine()
    :m_states()
    ,m_gameloop(nullptr)
    ,m_cur_state(0)
{
    this->init();
}

CStateMachine::~CStateMachine()
{
    this->unInit();
}

int CStateMachine::getCurState() const
{
    return this->m_cur_state;
}

int CStateMachine::toNextState()
{
    CState *pstate = this->m_states[this->m_cur_state];
    pstate->toNextState();
}

void CStateMachine::init()
{
    //State wait
    CState state_wait(0);
    CTFWaitToStart wait_to_start(this->m_gameloop);
    state_wait.addTransform(wait_to_start);
    this->m_states.push_back(state_wait);
    
    //State start
    CState state_start(1);
    
    
}

void CStateMachine::unInit()
{

}
