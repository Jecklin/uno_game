#include "CGameLoop.h"
#include "CStateWait.h"
#include "CStateStart.h"
#include "CStateMy.h"
#include "CStateOther.h"
#include "CStateAdd.h"
#include "CStateSub.h"
#include "CStateEnd.h"
#include "CStateError.h"

#include <iostream>

CGameLoop::CGameLoop()
    :m_fsm(nullptr)
    ,m_stateWait(nullptr)
    ,m_stateStart(nullptr)
    ,m_stateMy(nullptr)
    ,m_stateOther(nullptr)
    ,m_stateAdd(nullptr)
    ,m_stateSub(nullptr)
    ,m_stateEnd(nullptr)
{
    this->m_fsm         = new FSM();
    this->m_stateWait   = new CStateWait(this->m_fsm);
    this->m_stateStart  = new CStateStart(this->m_fsm);
    this->m_stateMy     = new CStateMy(this->m_fsm);
    this->m_stateOther  = new CStateOther(this->m_fsm);
    this->m_stateAdd    = new CStateAdd(this->m_fsm);
    this->m_stateSub    = new CStateSub(this->m_fsm);
    this->m_stateEnd    = new CStateEnd(this->m_fsm);
    this->m_stateError  = new CStateError(this->m_fsm);
    
    this->m_fsm->registerState(m_fsm->State_Wait, this->m_stateWait);
    this->m_fsm->registerState(m_fsm->State_Start, this->m_stateStart);
    this->m_fsm->registerState(m_fsm->State_My, this->m_stateMy);
    this->m_fsm->registerState(m_fsm->State_Other, this->m_stateOther);
    this->m_fsm->registerState(m_fsm->State_Add, this->m_stateAdd);
    this->m_fsm->registerState(m_fsm->State_Sub, this->m_stateSub);
    this->m_fsm->registerState(m_fsm->State_End, this->m_stateEnd);
    this->m_fsm->registerState(m_fsm->State_Error, this->m_stateError);
    
    //Init State = wait;
    this->m_fsm->InitState(m_fsm->State_Wait);
}

CGameLoop::~CGameLoop()
{
    delete this->m_fsm;
    delete this->m_stateWait;
    delete this->m_stateStart;
    delete this->m_stateMy;
    delete this->m_stateOther;
    delete this->m_stateAdd;
    delete this->m_stateSub;
    delete this->m_stateEnd;
    delete this->m_stateError;
  
    this->m_fsm         = nullptr;
    this->m_stateWait   = nullptr;
    this->m_stateStart  = nullptr;
    this->m_stateMy     = nullptr;
    this->m_stateOther  = nullptr;    
    this->m_stateAdd    = nullptr;
    this->m_stateSub    = nullptr;
    this->m_stateEnd    = nullptr;
    this->m_stateError  = nullptr;

}

void CGameLoop::gameStart()
{       
    emit firstRound();
    
    do
    {
        this->m_fsm->tick();
        
        if (this->m_fsm->curStateIsMy())
        {
            emit myRound();
        }
        else
        {
            ;
        }
        if (this->m_fsm->curStateIsError())
        {
            emit error();
        }
        

        emit playerChanged();
        emit endCardChanged();
        emit scoreChanged();  
//        sleep(5);
        
    }while(!this->m_fsm->curStateIsEnd());

    emit gameOver();
}

CPlayer CGameLoop::getPlayer(int num)
{
    return this->m_fsm->getPlayer(num);
}

CCardInfo CGameLoop::getEndCard()
{
    return this->m_fsm->getEndCard();
}

int CGameLoop::getCurrent()
{
    return this->m_fsm->getCurrent();
}

void CGameLoop::setChoice(int choice)
{
    this->m_fsm->setChoice(choice);
}

int CGameLoop::getChoice()
{
    return this->m_fsm->getChoice();
}




