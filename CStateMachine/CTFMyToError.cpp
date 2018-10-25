#include "CTFMyToError.h"

CTFMyToError::CTFMyToError(CJudge *judge):CAbstractTransform(judge)
{
    this->m_src = State_My;
    this->m_tar = State_Error;
}

bool CTFMyToError::TransForm()
{
    bool result = false;
    if (!this->m_judge->CurPlayerGiveUp())
    {
        if (this->m_judge->CurPlayerChoiced())
        {
            if (!this->m_judge->CurPlayerAllowedOut())
            {
                //reset choiced
                result = true;
                this->m_judge->SetCurPlayerChoiced(false);
                
                //emit
                this->m_judge->CurPlayerErrorPromt();
            }

        }
    }
    return result;
}
