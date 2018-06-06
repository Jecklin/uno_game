#include "CTFOtherToSub.h"

CTFOtherToSub::CTFOtherToSub(CGameLoop *gameloop)
    :m_src(State_Start)
    ,m_tar(State_Wait)
    ,m_gameloop(gameloop)
{
    
}

CTFOtherToSub::~CTFOtherToSub()
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

bool CTFOtherToSub::transForm()
{
    return true;
}

int CTFOtherToSub::srcState()
{
    return this->m_src;
}

int CTFOtherToSub::tarState()
{
    return this->m_tar;
}
