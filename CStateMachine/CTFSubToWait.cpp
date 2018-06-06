#include "CTFSubToWait.h"

CTFSubToWait::CTFSubToWait(CGameLoop *gameloop)
    :m_src(State_Start)
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
    return true;
}

int CTFSubToWait::srcState()
{
    return this->m_src;
}

int CTFSubToWait::tarState()
{
    return this->m_tar;
}
