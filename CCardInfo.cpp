#include "CCardInfo.h"

CCardInfo::CCardInfo()
    :m_color(ECC_Invalid)
    ,m_id(ECI_Invalid)
    ,m_action(ECA_Invalid)
{
    ;
}

CCardInfo::CCardInfo(ECardColor color, ECardId id, ECardAction action)
    :m_color(color)
    ,m_id(id)
    ,m_action(action)
{
    ;
}

CCardInfo::CCardInfo(const CCardInfo &other)
{
    *this = other;
}

CCardInfo::~CCardInfo()
{
    ;
}

CCardInfo &CCardInfo::operator=(const CCardInfo &other)
{
    if (this == &other)
    {
        ;
    }
    else
    {
        this->m_action = other.m_action;
        this->m_color = other.m_color;
        this->m_id = other.m_id;
    }
    return *this;
}

bool CCardInfo::operator ==(const CCardInfo &other)
{
    bool issame = false;
    if ((this->m_action == other.m_action)
            &&(this->m_color == other.m_color)
            &&(this->m_id == other.m_id))
    {
        issame = true;
    }
    else
    {
        ;
    }
    return issame;
}

ECardColor CCardInfo::GetColor() const
{
    return this->m_color;
}

ECardId CCardInfo::GetId() const
{
    return this->m_id;
}

ECardAction CCardInfo::GetAction() const
{
    return this->m_action;
}
