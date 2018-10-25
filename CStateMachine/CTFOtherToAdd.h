#pragma once

#include "CAbstractTransform.h"

class CTFOtherToAdd : public CAbstractTransform
{
public:
    CTFOtherToAdd(CJudge *judge);

    virtual bool        TransForm();
};

