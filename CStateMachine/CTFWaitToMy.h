#pragma once

#include "CAbstractTransform.h"

class CTFWaitToMy : public CAbstractTransform
{
public:
    CTFWaitToMy(CJudge *judge);

    virtual bool        TransForm();
};


