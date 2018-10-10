#include "CTFMyToAdd.h"

CTFMyToAdd::CTFMyToAdd(CGameLoop *gameloop)
    :m_src(State_My)
    ,m_tar(State_Add)
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
    bool is_ok = false;
    if (this->m_gameloop->giveUp())
    {
        is_ok = true;
        m_gameloop->addCard(m_gameloop->current());
    }
    else
    {
        ;
    }
    return is_ok;
}

int CTFMyToAdd::srcState() const
{
    return this->m_src;
}

int CTFMyToAdd::tarState() const
{
    return this->m_tar;
}
