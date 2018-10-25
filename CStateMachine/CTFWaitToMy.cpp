#include "CTFWaitToMy.h"

CTFWaitToMy::CTFWaitToMy(CJudge *judge):CAbstractTransform(judge)
{
    this->m_src = State_Wait;
    this->m_tar = State_My;
}

bool CTFWaitToMy::TransForm()
{
    bool result = false;
    
    if (this->m_judge->GetCurStation() == 0)
    {
        result = true;
    }
    return result;
}
