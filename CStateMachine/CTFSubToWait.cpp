#include "CTFSubToWait.h"

CTFSubToWait::CTFSubToWait(CJudge *judge):CAbstractTransform(judge)
{
    this->m_src = State_Sub;
    this->m_tar = State_Wait;
}


bool CTFSubToWait::TransForm()
{    
    bool result = false;
    if (!this->m_judge->CurPlayerEmpty())
    {
        result = true;
        if (this->m_judge->EndCardIsBlack())
        {
            this->m_judge->CurPlayerChangeColor();
            
        }
        
        this->m_judge->ToNext();
        this->m_judge->Punish();
    }
    return result;

}
