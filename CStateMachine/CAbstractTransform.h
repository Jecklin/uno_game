#pragma once
#include "CGame/CJudge.h"
#include "CGame/datatypedefine.h"

class CAbstractTransform
{
public:
    CAbstractTransform(CJudge *judge):m_judge(judge){}
    virtual ~CAbstractTransform()
    {
        if (this->m_judge != nullptr)
        {
            this->m_judge = nullptr;
        }
    }
    
    
    virtual bool TransForm()      = 0;
    virtual int  SrcState() const
    {
        return m_src;
    }
    virtual int  TarState() const
    {
        return m_tar;
    } 
    
protected:
    int         m_src;
    int         m_tar;
    CJudge      *m_judge;
};

