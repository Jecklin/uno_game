#include "CStateMachine.h"
#include "CGame/CGameLoop.h"
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

CStateMachine::CStateMachine(CGameLoop *loop)
    :m_gameloop(loop)
    ,m_states()
    ,m_curstate(nullptr)
{
    ;
}

CStateMachine::~CStateMachine()
{
    this->unInit();
}

int CStateMachine::getCurState() const
{
    return this->m_curstate->getCurState();
}

int CStateMachine::toNextState()
{
    int next = this->m_curstate->toNextState();
    auto iter = this->m_states.find(next);
    if (iter == m_states.end())
    {
        ;
    }
    else
    {
        this->m_curstate = iter->second;
    }
    
    return next;
}

void CStateMachine::initMachine()
{ 
    if (this->m_states.empty())
    {
        ;
    }
    else
    {
        this->unInit();
    }
        
    CState  *pstate = nullptr;
    
    //State start
    pstate = new CState(0);    
    this->m_curstate = pstate;      //Init curstate
    
    CAbstractTransform *start_to_wait = new CTFStartToWait(this->m_gameloop);
    pstate->addTransform(start_to_wait);
    this->m_states.insert(StateMap::value_type(0, pstate));

    
    //State wait
    pstate = new CState(1);
    CAbstractTransform *wait_to_my = new CTFWaitToMy(this->m_gameloop);
    CAbstractTransform *wait_to_other = new CTFWaitToOther(this->m_gameloop);
    pstate->addTransform(wait_to_my);
    pstate->addTransform(wait_to_other);
    this->m_states.insert(StateMap::value_type(1, pstate));
    
    //State my
    pstate = new CState(2);
    CAbstractTransform *my_to_add = new CTFMyToAdd(this->m_gameloop);
    CAbstractTransform *my_to_error = new CTFMyToError(this->m_gameloop);
    CAbstractTransform *my_to_sub = new CTFMyToSub(this->m_gameloop);
    pstate->addTransform(my_to_add);
    pstate->addTransform(my_to_error);
    pstate->addTransform(my_to_sub);
    this->m_states.insert(StateMap::value_type(2, pstate));
    
    //State other
    pstate = new CState(3);
    CAbstractTransform *other_to_add = new CTFOtherToAdd(this->m_gameloop);
    CAbstractTransform *other_to_sub = new CTFOtherToSub(this->m_gameloop);
    pstate->addTransform(other_to_add);
    pstate->addTransform(other_to_sub);
    this->m_states.insert(StateMap::value_type(3, pstate));
    
    //State add
    pstate = new CState(4);
    CAbstractTransform *add_to_wait = new CTFAddToWait(this->m_gameloop);
    pstate->addTransform(add_to_wait);
    this->m_states.insert(StateMap::value_type(4, pstate));
    
    //State sub
    pstate = new CState(5);
    CAbstractTransform *sub_to_end = new CTFSubToEnd(this->m_gameloop);
    CAbstractTransform *sub_to_wait = new CTFSubToWait(this->m_gameloop);
    pstate->addTransform(sub_to_end);
    pstate->addTransform(sub_to_wait);
    this->m_states.insert(StateMap::value_type(5, pstate));
    
    //State end
    pstate = new CState(6);
    this->m_states.insert(StateMap::value_type(6, pstate));
    
    
}

void CStateMachine::unInit()
{ 
    if (this->m_states.empty())
    {
        ;
    }
    else
    {
        for (int i = this->m_states.size() - 1; i >= 0; --i)
        {
            CState *ptr = nullptr;
            auto iter = this->m_states.find(i);
            if (iter == this->m_states.end())
            {
                ;
            }
            else
            {
                ptr = iter->second;
                delete ptr;
                ptr = nullptr;
                this->m_states.erase(iter);
            }
        }
    }

}


