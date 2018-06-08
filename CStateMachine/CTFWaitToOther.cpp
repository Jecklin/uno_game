#include "CTFWaitToOther.h"

CTFWaitToOther::CTFWaitToOther(CGameLoop *gameloop)
    :m_src(State_Wait)
    ,m_tar(State_Other)
    ,m_gameloop(gameloop)
{
    
}

CTFWaitToOther::~CTFWaitToOther()
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

bool CTFWaitToOther::transForm()
{
    bool is_ok = false;
    if (!this->m_gameloop->curPlayerIsMy())
    {
        is_ok = true;
    }
    else
    {
        ;
    }
    return is_ok;
}

int CTFWaitToOther::srcState() const
{
    return this->m_src;
}

int CTFWaitToOther::tarState() const
{
    return this->m_tar;
}
