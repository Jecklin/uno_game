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
    if (!m_gameloop->curPlayerIsGiveUp())
    {
        if (m_gameloop->isChoicedCard())
        {
            if (!m_gameloop->myAllowOut())
            {
                is_ok = true;
                this->m_gameloop->errorPromt(); 
                this->m_gameloop->resetChoicedCard();
            }
        }
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
