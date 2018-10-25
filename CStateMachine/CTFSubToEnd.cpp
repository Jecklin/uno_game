#include "CTFSubToEnd.h"

CTFSubToEnd::CTFSubToEnd(CJudge *judge):CAbstractTransform(judge)
{
    this->m_src = State_Sub;
    this->m_tar = State_End;
}

bool CTFSubToEnd::TransForm()
{   
    bool result = false;
    if (this->m_judge->CurPlayerEmpty())
    {
        this->m_judge->SetAllScores();
        result = true;
    }
    return result;
}
