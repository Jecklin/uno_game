#include "CTFSubToWait.h"

CTFSubToWait::CTFSubToWait(CGameLoop *gameloop)
    :m_src(State_Sub)
    ,m_tar(State_Wait)
    ,m_gameloop(gameloop)
{
    
}

CTFSubToWait::~CTFSubToWait()
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

bool CTFSubToWait::transForm()
{
    this->m_gameloop->curPlayerOutCard();
    this->m_gameloop->doPunish();
    this->m_gameloop->curToNext();
    
    bool is_ok = false;
    if (this->m_gameloop->curPlayerIsWinner())
    {
        ;
    }
    else
    {
        is_ok = true;
    }
    return is_ok;
}

int CTFSubToWait::srcState() const
{
    return this->m_src;
}

int CTFSubToWait::tarState() const
{
    return this->m_tar;
}
