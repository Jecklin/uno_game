#include "CTFWaitToMy.h"

CTFWaitToMy::CTFWaitToMy(CGameLoop *gameloop)
    :m_src(State_Wait)
    ,m_tar(State_My)
    ,m_gameloop(gameloop)
{
    
}

CTFWaitToMy::~CTFWaitToMy()
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

bool CTFWaitToMy::transForm()
{
    bool is_ok = false;
    if (this->m_gameloop->curPlayerIsMy())
    {
        is_ok = true;
    }
    else
    {
        ;
    }
    return is_ok;
}

int CTFWaitToMy::srcState() const
{
    return this->m_src;
}

int CTFWaitToMy::tarState() const
{
    return this->m_tar;
}
