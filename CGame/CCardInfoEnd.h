#pragma once

#include "CCardInfo.h"

class CCardInfoEnd:public CCardInfo
{
public:
    CCardInfoEnd();
    ~CCardInfoEnd();

public:
    void SetColor(const ECardColor color);
    void SetCard(const CCardInfo &card);
    
};


