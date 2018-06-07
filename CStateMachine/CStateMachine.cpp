#include "CStateMachine.h"
#include "CGame/CGameLoop.h"
#include "CState.h"
#include "CTFStartToWait.h"
#include "CTFWaitToMy.h"
#include "CTFWaitToOther.h"
#include "CTFMyToAdd.h"
#include "CTFMyToError.h"
#include "CTFMyToSub.h"
#include "CTFOtherToAdd.h"
#include "CTFOtherToSub.h"
#include "CTFAddToWait.h"
#include "CTFSubToEnd.h"
#include "CTFSubToWait.h"
#include "CTFErrorToMy.h"

CStateMachine::CStateMachine(CGameLoop *loop)
    :m_states()
    ,m_gameloop(loop)
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
    CState *pstate = this->m_states[this->m_cur_state];
    return *pstate;
}

int CStateMachine::toNextState()
{
    CState *pstate = this->m_states[this->m_cur_state];
    this->m_cur_state = pstate->toNextState();
}

void CStateMachine::init()
{
     //State start
    CState          state_start(0);
    CTFStartToWait  start_to_wait(this->m_gameloop);
    state_start.addTransform(start_to_wait);
    this->m_states.push_back(state_start);
       
    //State wait
    CState          state_wait(1);
    CTFWaitToMy     wait_to_my(this->m_gameloop);
    CTFWaitToOther  wait_to_other(this->m_gameloop);
    state_wait.addTransform(wait_to_my);
    state_wait.addTransform(wait_to_other);
    this->m_states.push_back(state_wait);
    
    //State my
    CState          state_my(2);
    CTFMyToAdd      my_to_add(this->m_gameloop);
    CTFMyToError    my_to_error(this->m_gameloop);
    CTFMyToSub      my_to_sub(this->m_gameloop);
    state_my.addTransform(my_to_add);
    state_my.addTransform(my_to_error);
    state_my.addTransform(my_to_sub);
    this->m_states.push_back(state_my);
    
    //State other
    CState          state_other(3);
    CTFOtherToAdd   other_to_add(this->m_gameloop);
    CTFOtherToSub   other_to_sub(this->m_gameloop);
    state_other.addTransform(other_to_add);
    state_other.addTransform(other_to_sub);
    this->m_states.push_back(state_other);
    
    //State add
    CState          state_add(4);
    CTFAddToWait    add_to_wait(this->m_gameloop);
    state_add.addTransform(add_to_wait);
    this->m_states.push_back(state_add);
    
    //State sub
    CState          state_sub(5);
    CTFSubToEnd     sub_to_end(this->m_gameloop);
    CTFSubToWait    sub_to_wait(this->m_gameloop);
    state_sub.addTransform(sub_to_end);
    state_sub.addTransform(sub_to_wait);
    this->m_states.push_back(state_sub);
    
    //State end
    CState          state_end(6);
    this->m_states.push_back(state_end);
    
    //State error
    CState          state_error(7);
    CTFErrorToMy    error_to_my(this->m_gameloop);
    state_error.addTransform(error_to_my);
    this->m_states.push_back(state_error);
    
    this->m_gameloop->initGame();
}

void CStateMachine::unInit()
{
    
}

bool CStateMachine::isEndState()
{
    bool is_end = false;
    if (this->m_cur_state == 6)
    {
        is_end = true;
    }
    else
    {
        ;
    }
    return is_end;
    
}
