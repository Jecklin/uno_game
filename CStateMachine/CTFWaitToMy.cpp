#include "CTFWaitToMy.h"

CTFWaitToMy::CTFWaitToMy(CGameLoop *gameloop)
    :m_src(State_Start)
    ,m_tar(State_Wait)
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
    return true;
}

int CTFWaitToMy::srcState()
{
    return this->m_src;
}

int CTFWaitToMy::tarState()
{
    return this->m_tar;
}
