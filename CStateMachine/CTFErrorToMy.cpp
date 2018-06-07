#include "CTFErrorToMy.h"

CTFErrorToMy::CTFErrorToMy(CGameLoop *gameloop)
    :m_src(State_Error)
    ,m_tar(State_My)
    ,m_gameloop(gameloop)
{
    
}

CTFErrorToMy::~CTFErrorToMy()
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

bool CTFErrorToMy::transForm()
{
    this->m_gameloop->showNotAllow();
    return true;
}

int CTFErrorToMy::srcState()
{
    return this->m_src;
}

int CTFErrorToMy::tarState()
{
    return this->m_tar;
}
