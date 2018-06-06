#include "CTFSubToEnd.h"

CTFSubToEnd::CTFSubToEnd(CGameLoop *gameloop)
    :m_src(State_Start)
    ,m_tar(State_Wait)
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
    return true;
}

int CTFSubToEnd::srcState()
{
    return this->m_src;
}

int CTFSubToEnd::tarState()
{
    return this->m_tar;
}
