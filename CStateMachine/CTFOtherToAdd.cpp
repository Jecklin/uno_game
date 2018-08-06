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
    if (!m_gameloop->otherAllowed())
    {
        is_ok = true;
        m_gameloop->addCard(m_gameloop->current());
    }
    
    return is_ok;
}

int CTFOtherToAdd::srcState() const
{
    return this->m_src;
}

int CTFOtherToAdd::tarState() const
{
    return this->m_tar;
}
