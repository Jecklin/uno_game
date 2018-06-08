#include "CTFAddToWait.h"

CTFAddToWait::CTFAddToWait(CGameLoop *gameloop)
    :m_src(State_Add)
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
    this->m_gameloop->curPlayerInCard();
    return true;
}

int CTFAddToWait::srcState() const
{
    return this->m_src;
}

int CTFAddToWait::tarState() const
{
    return this->m_tar;
}
