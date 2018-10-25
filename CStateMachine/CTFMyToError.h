#pragma once

#include "CAbstractTransform.h"

class CTFMyToError : public CAbstractTransform
{
public:
    CTFMyToError(CJudge *judge);

    virtual bool        TransForm();
};

