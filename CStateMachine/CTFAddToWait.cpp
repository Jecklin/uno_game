#include "CTFAddToWait.h"

CTFAddToWait::CTFAddToWait(CGameLoop *gameloop)
    :m_src(State_Start)
    ,m_tar(State_Wait)
    ,m_gameloop(gameloop)
{
    
}

CTFAddToWait::~CTFAddToWait()
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

bool CTFAddToWait::transForm()
{
    return true;
}

int CTFAddToWait::srcState()
{
    return this->m_src;
}

int CTFAddToWait::tarState()
{
    return this->m_tar;
}
