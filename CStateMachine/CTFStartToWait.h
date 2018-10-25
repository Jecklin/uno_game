#pragma once

#include "CAbstractTransform.h"

class CTFStartToWait : public CAbstractTransform
{
public:
    CTFStartToWait(CJudge *judge);

    virtual bool        TransForm();
};


