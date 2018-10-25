#pragma once

#include "CAbstractTransform.h"

class CTFOtherToSub : public CAbstractTransform
{
public:
    CTFOtherToSub(CJudge *judge);

    virtual bool        TransForm();
};

