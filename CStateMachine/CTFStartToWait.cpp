#include "CTFStartToWait.h"

CTFStartToWait::CTFStartToWait(CGameLoop *gameloop)
    :m_src(State_Start)
    ,m_tar(State_Wait)
    ,m_gameloop(gameloop)
{
    
}

CTFStartToWait::~CTFStartToWait()
{
    if (this->m_gameloop == nullptr)
    {
        ;
    }
    else
    {
        this->m_gameloop = nullptr;
    }
}

bool CTFStartToWait::transForm()
{
    this->m_gameloop->initGame();
    return true;
}

int CTFStartToWait::srcState()
{
    return this->m_src;
}

int CTFStartToWait::tarState()
{
    return this->m_tar;
}
