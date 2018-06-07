#include "CTFSubToEnd.h"

CTFSubToEnd::CTFSubToEnd(CGameLoop *gameloop)
    :m_src(State_Sub)
    ,m_tar(State_End)
    ,m_gameloop(gameloop)
{
    
}

CTFSubToEnd::~CTFSubToEnd()
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

bool CTFSubToEnd::transForm()
{
    this->m_gameloop->curPlayerOutCard();
    
    bool is_ok = false;
    if (this->m_gameloop->curPlayerIsWinner())
    {
        is_ok = true;
    }
    else
    {
        this->m_gameloop->doPunish();
        this->m_gameloop->curToNext();
    }
    return is_ok;
}

int CTFSubToEnd::srcState()
{
    return this->m_src;
}

int CTFSubToEnd::tarState()
{
    return this->m_tar;
}
