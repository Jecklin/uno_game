#include "CCardInfo.h"

CCardInfo::CCardInfo()
    :m_color(ECC_Invalid)
    ,m_id(ECI_Invalid)
    ,m_action(ECA_Invalid)
{

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
    if (this != &other)
    {
        this->m_action = other.GetAction();
        this->m_color = other.GetColor();
        this->m_id = other.GetId();
    }

    return *this;
}

bool CCardInfo::operator ==(const CCardInfo &other) const
{
    bool issame = false;
    if ((this->m_action == other.GetAction())
            &&(this->m_color == other.GetColor())
            &&(this->m_id == other.GetId()))
    {
        issame = true;
    }

    return issame;
}

bool CCardInfo::operator !=(const CCardInfo &other) const
{
    bool issame = true;
    if ((this->m_action == other.GetAction())
            &&(this->m_color == other.GetColor())
            &&(this->m_id == other.GetId()))
    {
        issame = false;
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
