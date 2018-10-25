#pragma once

#include "CAbstractTransform.h"

class CTFWaitToOther : public CAbstractTransform
{
public:
    CTFWaitToOther(CJudge *judge);

    virtual bool        TransForm();
};


