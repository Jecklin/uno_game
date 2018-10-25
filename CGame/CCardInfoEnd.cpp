#include "CCardInfoEnd.h"

CCardInfoEnd::CCardInfoEnd()
{
    ;
}

CCardInfoEnd::~CCardInfoEnd()
{
    ;
}

void CCardInfoEnd::SetCard(const CCardInfo &card)
{
    this->m_action = card.GetAction();
    this->m_color = card.GetColor();
    this->m_id = card.GetId();
}

void CCardInfoEnd::SetColor(const ECardColor color)
{
    this->m_color = color;
}

