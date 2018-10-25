#include "CTFMyToAdd.h"

CTFMyToAdd::CTFMyToAdd(CJudge *judge):CAbstractTransform(judge)
{
    this->m_src = State_My;
    this->m_tar = State_Add;
}

bool CTFMyToAdd::TransForm()
{
    bool result = false;
    
    if (this->m_judge->CurPlayerGiveUp())
    {
        result = true;
        this->m_judge->CurPlayerAddCard();
    }
    
    return result;
    
}
