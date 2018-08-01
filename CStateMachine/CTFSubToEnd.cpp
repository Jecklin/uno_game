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
    bool is_ok = false;
    if (this->m_gameloop->curPlayerEmpty())
    {
        this->m_gameloop->setAllScores();
        is_ok = true;
    }

    return is_ok;
}

int CTFSubToEnd::srcState() const
{
    return this->m_src;
}

int CTFSubToEnd::tarState() const
{
    return this->m_tar;
}
