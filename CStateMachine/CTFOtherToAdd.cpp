#include "CTFOtherToAdd.h"

CTFOtherToAdd::CTFOtherToAdd(CGameLoop *gameloop)
    :m_src(State_Other)
    ,m_tar(State_Add)
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
    bool is_ok = false;
    if (this->m_gameloop->otherAllowOut())
    {
        ;
    }
    else
    {
        is_ok = true;
    }
    return is_ok;
}

int CTFOtherToAdd::srcState()
{
    return this->m_src;
}

int CTFOtherToAdd::tarState()
{
    return this->m_tar;
}
