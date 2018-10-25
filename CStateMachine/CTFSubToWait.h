#pragma once

#include "CAbstractTransform.h"

class CTFSubToWait : public CAbstractTransform
{
public:
    CTFSubToWait(CJudge *judge);

    virtual bool        TransForm();
};

