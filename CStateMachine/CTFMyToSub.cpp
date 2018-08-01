#include "CTFMyToSub.h"

CTFMyToSub::CTFMyToSub(CGameLoop *gameloop)
    :m_src(State_My)
    ,m_tar(State_Sub)
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
    bool is_ok = false;
    
    if (!m_gameloop->curPlayerIsGiveUp())
    {
        if (m_gameloop->isChoicedCard())
        {
            if (m_gameloop->myAllowOut())
            {
                is_ok = true;
                this->m_gameloop->curPlayerOutCard();
                this->m_gameloop->resetChoicedCard();
            }
        }
    }
    

    return is_ok;
}

int CTFMyToSub::srcState() const
{
    return this->m_src;
}

int CTFMyToSub::tarState() const
{
    return this->m_tar;
}
