#include "CTFMyToError.h"

CTFMyToError::CTFMyToError(CGameLoop *gameloop)
    :m_src(State_My)
    ,m_tar(State_Error)
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
    bool is_ok = false;
    if (this->m_gameloop->curPlayerIsGiveUp())
    {
        ;
    }
    else if (this->m_gameloop->curPlayerIsChoicedCard())
    {
        if (this->m_gameloop->myAllowOut())
        {
            ;
        }
        else
        {
            is_ok = true;
            this->m_gameloop->errorPromt(); 
        }
    }
    else
    {
        ;
    }

    return is_ok;
}

int CTFMyToError::srcState() const
{
    return this->m_src;
}

int CTFMyToError::tarState() const
{
    return this->m_tar;
}
