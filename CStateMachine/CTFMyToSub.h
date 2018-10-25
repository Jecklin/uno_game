#pragma once

#include "CAbstractTransform.h"

class CTFMyToSub : public CAbstractTransform
{
public:
    CTFMyToSub(CJudge *judge);

    virtual bool        TransForm();
};
