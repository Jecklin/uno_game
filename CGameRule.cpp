#include "CGameRule.h"
#include "CGame/CGameLoop.h"

CGameRule::CGameRule(CGameLoop *game)
    :m_game(game)
    ,m_current(0)
    ,m_toward(1)
{
    ;
}

int CGameRule::getCurrent() const
{
    return m_current;
}

void CGameRule::toNext()
{
    this->m_current = getNextLocation();
}

void CGameRule::actNextAddCard(int num)
{
    int next = this->getNextLocation();
    for (int touch = 0; touch < num; ++touch)
    {
        m_game->playerAddCard(next);
    }
}

void CGameRule::actStop()
{
    this->m_current = this->getNextLocation();
}

void CGameRule::actReverse()
{
    if (this->m_toward == 1)
    {
        this->m_toward = -1;
    }
    else if (this->m_toward == -1)
    {
        this->m_toward = 1;
    }
    else
    {
        ;
    }
}

void CGameRule::actChangeColor()
{
    
}

int CGameRule::getNextLocation()
{
//    int next = m_current + m_toward;
//    if (next > 3)  //m_players.size() - 1
//    {
//        next -= m_players.size();
//    }
//    else if (next < 0)
//    {
//        next += m_players.size();
//    }
//    else
//    {
//        ;
//    }
//    return next;
}
