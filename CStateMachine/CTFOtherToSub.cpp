#include "CTFOtherToSub.h"

CTFOtherToSub::CTFOtherToSub(CGameLoop *gameloop)
    :m_src(State_Other)
    ,m_tar(State_Sub)
    ,m_gameloop(gameloop)
{
    
}

CTFOtherToSub::~CTFOtherToSub()
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

bool CTFOtherToSub::transForm()
{
    bool is_ok = false;
    if (m_gameloop->otherAllowed())
    {
        is_ok = true;
        this->m_gameloop->curOutCard();
    }

    return is_ok;
}

int CTFOtherToSub::srcState() const
{
    return this->m_src;
}

int CTFOtherToSub::tarState() const
{
    return this->m_tar;
}
