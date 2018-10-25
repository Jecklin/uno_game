#pragma once

#include "CState.h"
#include "CAbstractState.h"
#include "CGame/CJudge.h"
#include <QMap>


class CStateMachine:public CAbstractState
{
public:
    CStateMachine(CJudge *judge);
    virtual   ~CStateMachine();
    void               InIt();

    virtual int        GetCurState() const;
    virtual int        ToNextState();
           
private:
    typedef QMap<int, CState*> StateMap;
    
    CJudge             *m_judge;
    StateMap            m_states;
    CState             *m_curstate;    
};

