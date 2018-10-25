#include "CTFStartToWait.h"

CTFStartToWait::CTFStartToWait(CJudge *judge):CAbstractTransform(judge)
{
    this->m_src = State_Start;
    this->m_tar = State_Wait;
}

bool CTFStartToWait::TransForm()
{
    return true;
}

