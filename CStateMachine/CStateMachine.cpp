#include "CStateMachine.h"
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

CStateMachine::CStateMachine(CJudge *judge)
    :m_judge(judge)
    ,m_states()
    ,m_curstate(nullptr)
{
    ;
}

CStateMachine::~CStateMachine()
{
    while (!this->m_states.empty())
    {
        auto iter = m_states.begin();
        delete iter.value();
        m_states.erase(iter);
    }
}

int CStateMachine::GetCurState() const
{
    return this->m_curstate->GetCurState();
}

int CStateMachine::ToNextState()
{
    int next = this->m_curstate->ToNextState();
    auto iter = this->m_states.find(next);
    if (iter != m_states.end())
    {
        this->m_curstate = iter.value();
    }
    
    return next;
}

void CStateMachine::InIt()
{ 
    //第一回合，初始化所有状态
    if (this->m_states.empty())
    {
        CState  *pstate = nullptr;
        
        //State start
        pstate = new CState(0);    
        this->m_curstate = pstate;      //Init curstate
        
        CAbstractTransform *start_to_wait = new CTFStartToWait(this->m_judge);
        pstate->AddTransform(start_to_wait);
        this->m_states.insert(0, pstate);
    
        
        //State wait
        pstate = new CState(1);
        CAbstractTransform *wait_to_my = new CTFWaitToMy(this->m_judge);
        CAbstractTransform *wait_to_other = new CTFWaitToOther(this->m_judge);
        pstate->AddTransform(wait_to_my);
        pstate->AddTransform(wait_to_other);
        this->m_states.insert(1, pstate);
        
        //State my
        pstate = new CState(2);
        CAbstractTransform *my_to_add = new CTFMyToAdd(this->m_judge);
        CAbstractTransform *my_to_error = new CTFMyToError(this->m_judge);
        CAbstractTransform *my_to_sub = new CTFMyToSub(this->m_judge);
        pstate->AddTransform(my_to_add);
        pstate->AddTransform(my_to_error);
        pstate->AddTransform(my_to_sub);
        this->m_states.insert(2, pstate);
        
        //State other
        pstate = new CState(3);
        CAbstractTransform *other_to_add = new CTFOtherToAdd(this->m_judge);
        CAbstractTransform *other_to_sub = new CTFOtherToSub(this->m_judge);
        pstate->AddTransform(other_to_add);
        pstate->AddTransform(other_to_sub);
        this->m_states.insert(3, pstate);
        
        //State add
        pstate = new CState(4);
        CAbstractTransform *add_to_wait = new CTFAddToWait(this->m_judge);
        pstate->AddTransform(add_to_wait);
        this->m_states.insert(4, pstate);
        
        //State sub
        pstate = new CState(5);
        CAbstractTransform *sub_to_end = new CTFSubToEnd(this->m_judge);
        CAbstractTransform *sub_to_wait = new CTFSubToWait(this->m_judge);
        pstate->AddTransform(sub_to_end);
        pstate->AddTransform(sub_to_wait);
        this->m_states.insert(5, pstate);
        
        //State end
        pstate = new CState(6);
        this->m_states.insert(6, pstate);
    }
    
    //非第一回合，仅初始化开始状态
    else
    {
        this->m_curstate = m_states.find(0).value();
    }
 
    
}



