#pragma once
#include "CAbstractTransform.h"

class CTFSubToEnd : public CAbstractTransform
{
public:
    CTFSubToEnd(CJudge *judge);

    virtual bool        TransForm();
};

