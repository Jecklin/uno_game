#include "CGameRule.h"
#include "CGame/CGameLoop.h"

CGameRule::CGameRule(CGameLoop *game)
    :m_game(game)
    ,m_current(0)
    ,m_toward(1)
{
    ;
}

int CGameRule::current() const
{
    return m_current;
}

int CGameRule::next()
{
    int next = m_current + m_toward;
    if (next > m_game->getPlayerSize()-1)  //m_players.size() - 1
    {
        next -= m_game->getPlayerSize(); //m_game->getPlayerSize()
    }
    else if (next < 0)
    {
        next += m_game->getPlayerSize();
    }
    else
    {
        ;
    }
    return next;
}

void CGameRule::sroundCurrent()
{
    srand((unsigned int)time(nullptr));
    int sround = rand() % (m_game->getPlayerSize() - 1);
    m_current = sround;
}

void CGameRule::toNext()
{
    this->m_current = next();
}

void CGameRule::actNextAddCard(int num)
{
    for (int touch = 0; touch < num; ++touch)
    {
        m_game->addCard(next());
    }
}

void CGameRule::actStop()
{
    this->m_current = this->next();
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

void CGameRule::actChoiceColor()
{
    m_game->actChangeColor();
}


