#include "CTFOtherToAdd.h"

CTFOtherToAdd::CTFOtherToAdd(CGameLoop *gameloop)
    :m_src(State_Start)
    ,m_tar(State_Wait)
    ,m_gameloop(gameloop)
{
    
}

CTFOtherToAdd::~CTFOtherToAdd()
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

bool CTFOtherToAdd::transForm()
{
    return true;
}

int CTFOtherToAdd::srcState()
{
    return this->m_src;
}

int CTFOtherToAdd::tarState()
{
    return this->m_tar;
}
