#include <iostream>
#include <QVector>

#include "CPlayer.h"
#include "CCardInfo.h"


CPlayer::CPlayer()
    :m_attribute()
    ,m_box()
    ,m_giveup(false)
    ,m_choiced(false)
    ,m_outcard()
    ,m_changeColor()
{
    ;
}

CPlayer::CPlayer(QString name)
    :m_attribute()
    ,m_box()
    ,m_giveup(false)
    ,m_choiced(false)
    ,m_outcard()
    ,m_changeColor()
{
    this->m_attribute.setName(name);
}


CPlayer::~CPlayer()
{
    ;
}

CPlayer::CPlayer(CPlayer &other)
    :m_attribute()
    ,m_box()
    ,m_giveup(false)
    ,m_choiced(false)
    ,m_outcard()
    ,m_changeColor()
{
    *this = other;
}

CPlayer& CPlayer::operator =(CPlayer &other)
{
    if (this == &other)
    {
        ;
    }
    else
    {
        this->SetAttribute(other.GetAttribute());
        this->SetBox(other.GetBox());
    }
    return *this;
}

CPlayerAttribute CPlayer::GetAttribute() const
{
    return m_attribute;
}

void CPlayer::SetAttribute(const CPlayerAttribute &attribute)
{
    this->m_attribute = attribute;
}

CBox& CPlayer::GetBox()
{
    return m_box;
}

void CPlayer::SetBox(CBox &box)
{
    this->m_box = box;
}

bool CPlayer::IsGiveUp()
{
    return this->m_giveup;
}

void CPlayer::SetGiveUp(bool giveup)
{
    this->m_giveup = giveup;
}

bool CPlayer::IsChoiced()
{
    return this->m_choiced;
}

void CPlayer::SetChoiced(bool choice)
{
    this->m_choiced = choice;
}

CCardInfo& CPlayer::GetOutCard()
{
    return this->m_outcard;
}

void CPlayer::SetOutCard(const CCardInfo &card)
{
    this->m_outcard = card;
}



ECardColor CPlayer::GetMostColor()
{
    ECardColor  mostColor;
    int blue    = this->m_box.NumberOf(ECardColor::ECC_Blue);
    int red     = this->m_box.NumberOf(ECardColor::ECC_Red);
    int yellow  = this->m_box.NumberOf(ECardColor::ECC_Yellow);
    int green   = this->m_box.NumberOf(ECardColor::ECC_Green);

    int max     = 0;
    int maxNum  = 0;
    QVector<int> colors = {blue, red, yellow, green};
    for (int i = 0; i < colors.size(); ++i)
    {
        if (max < colors[i])
        {
            max     = colors[i];
            maxNum  = i;
        }
    }
    
    if (maxNum == 0)
    {
        mostColor = ECC_Blue;
    }
    else if(maxNum == 1)
    {
        mostColor = ECC_Red;
    }
    else if (maxNum == 2)
    {
        mostColor = ECC_Yellow;
    }
    else if (maxNum == 3)
    {
        mostColor = ECC_Green;
    }

    return mostColor;
}

void CPlayer::SetChangeColor(ECardColor color)
{
    this->m_changeColor = color;
}

ECardColor CPlayer::GetChangeColor()
{
    return this->m_changeColor;
}

void CPlayer::RemoveCard(const CCardInfo &card)
{
    this->m_box.RemoveCard(card);
}

void CPlayer::AddCard(const CCardInfo &card)
{
    this->m_box.AddCard(card);
}




