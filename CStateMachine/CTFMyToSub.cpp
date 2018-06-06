#include "CTFMyToSub.h"

CTFMyToSub::CTFMyToSub(CGameLoop *gameloop)
    :m_src(State_Start)
    ,m_tar(State_Wait)
    ,m_gameloop(gameloop)
{
    
}

CTFMyToSub::~CTFMyToSub()
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

bool CTFMyToSub::transForm()
{
    return true;
}

int CTFMyToSub::srcState()
{
    return this->m_src;
}

int CTFMyToSub::tarState()
{
    return this->m_tar;
}
