#include "CTFAddToWait.h"

CTFAddToWait::CTFAddToWait(CJudge *judge):CAbstractTransform(judge)
{
    this->m_src = State_Add;
    this->m_tar = State_Wait;
}

bool CTFAddToWait::TransForm()
{
    this->m_judge->ToNext();
    return true;
}
