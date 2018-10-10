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
    return true;
}

int CTFStartToWait::srcState() const
{
    return this->m_src;
}

int CTFStartToWait::tarState() const
{
    return this->m_tar;
}
