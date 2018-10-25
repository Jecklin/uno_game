#pragma once

#include "CAbstractTransform.h"

class CTFMyToAdd : public CAbstractTransform
{
public:
    CTFMyToAdd(CJudge *judge);

    virtual bool        TransForm();    
};


