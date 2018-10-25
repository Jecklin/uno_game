#include "CTFOtherToAdd.h"

CTFOtherToAdd::CTFOtherToAdd(CJudge *judge):CAbstractTransform(judge)
{
    this->m_src = State_Other;
    this->m_tar = State_Add;
}

bool CTFOtherToAdd::TransForm()
{
    bool result = false;
    if (!this->m_judge->AutoCurPlayerAllowedOut())
    {
        result = true;
        this->m_judge->CurPlayerAddCard();   
    }
    return result;

}

