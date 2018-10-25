﻿#include "CTFOtherToSub.h"

CTFOtherToSub::CTFOtherToSub(CJudge *judge):CAbstractTransform(judge)
{
    this->m_src = State_Other;
    this->m_tar = State_Sub;
}

bool CTFOtherToSub::TransForm()
{
    bool result = false;
    if (this->m_judge->AutoCurPlayerAllowedOut())
    {
        result = true;
        this->m_judge->CurPlayerOutCard();
    }
    return result;

}
