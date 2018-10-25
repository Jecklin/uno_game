#include "CTFMyToSub.h"

CTFMyToSub::CTFMyToSub(CJudge *judge):CAbstractTransform(judge)
{
    this->m_src = State_My;
    this->m_tar = State_Sub;
}

bool CTFMyToSub::TransForm()
{
    bool result = false;
    if (!this->m_judge->CurPlayerGiveUp())
    {
        if (this->m_judge->CurPlayerChoiced())
        {
            if (this->m_judge->CurPlayerAllowedOut())
            {
                result = true;
                this->m_judge->CurPlayerOutCard();
            }
        }
    }
    
    return result;    
}

