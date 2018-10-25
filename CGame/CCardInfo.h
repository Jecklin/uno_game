#pragma once

#include "datatypedefine.h"

class CCardInfo
{
public:
    CCardInfo();
    virtual ~CCardInfo();

    CCardInfo(ECardColor color, ECardId id, ECardAction action);
    CCardInfo(const CCardInfo &other);

    CCardInfo& operator =   (const CCardInfo &other);
    bool       operator ==  (const CCardInfo &other) const;
    bool       operator !=  (const CCardInfo &other) const;

public:
    ECardColor   GetColor()  const;
    ECardId      GetId()     const;
    ECardAction  GetAction() const;
    
protected:
    ECardColor   m_color;
    ECardId      m_id;
    ECardAction  m_action; 
};

