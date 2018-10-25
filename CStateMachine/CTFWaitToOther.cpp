#include "CTFWaitToOther.h"

CTFWaitToOther::CTFWaitToOther(CJudge *judge):CAbstractTransform(judge)
{
    this->m_src = State_Wait;
    this->m_tar = State_Other;
}

bool CTFWaitToOther::TransForm()
{
    bool result = false;
    
    if (this->m_judge->GetCurStation() != 0)
    {
        result = true;
    }
    return result;

}
