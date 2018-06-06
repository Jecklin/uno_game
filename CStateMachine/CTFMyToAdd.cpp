#include "CTFMyToAdd.h"

CTFMyToAdd::CTFMyToAdd(CGameLoop *gameloop)
    :m_src(State_Start)
    ,m_tar(State_Wait)
    ,m_gameloop(gameloop)
{
    
}

CTFMyToAdd::~CTFMyToAdd()
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

bool CTFMyToAdd::transForm()
{
    return true;
}

int CTFMyToAdd::srcState()
{
    return this->m_src;
}

int CTFMyToAdd::tarState()
{
    return this->m_tar;
}
