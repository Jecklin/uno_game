#include "CTFWaitToOther.h"

CTFWaitToOther::CTFWaitToOther(CGameLoop *gameloop)
    :m_src(State_Start)
    ,m_tar(State_Wait)
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
    return true;
}

int CTFWaitToOther::srcState()
{
    return this->m_src;
}

int CTFWaitToOther::tarState()
{
    return this->m_tar;
}
