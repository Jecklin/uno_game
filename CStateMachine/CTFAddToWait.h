#pragma once

#include "CAbstractTransform.h"

class CTFAddToWait : public CAbstractTransform
{
public:
    CTFAddToWait(CJudge *judge);

    virtual bool        TransForm();    
};

