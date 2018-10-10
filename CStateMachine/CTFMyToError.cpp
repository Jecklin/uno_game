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
    if (!m_gameloop->giveUp())
    {
        if (m_gameloop->choiced())
        {
            if (!m_gameloop->myAllowed())
            {
                is_ok = true;
                this->m_gameloop->errorPromt(); 
                this->m_gameloop->setChoiced(false);
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
