#include "CTFMyToError.h"

CTFMyToError::CTFMyToError(CGameLoop *gameloop)
    :m_src(State_Start)
    ,m_tar(State_Wait)
    ,m_gameloop(gameloop)
{
    
}

CTFMyToError::~CTFMyToError()
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

bool CTFMyToError::transForm()
{
    return true;
}

int CTFMyToError::srcState()
{
    return this->m_src;
}

int CTFMyToError::tarState()
{
    return this->m_tar;
}
