#ifndef CSTATEMACHINE_H
#define CSTATEMACHINE_H

#include "CState.h"
#include "CAbstractState.h"
#include <map>

class CGameLoop;

class CStateMachine:public CAbstractState
{
public:
    explicit                    CStateMachine(CGameLoop *loop);
    virtual                     ~CStateMachine();
    
public:
    virtual int                 getCurState() const;
    virtual int                 toNextState();
    
public:
    void                        initMachine();
    void                        unInit();
    
    
private:
    typedef std::map<int, CState*> StateMap;
    
    CGameLoop                    *m_gameloop;
    StateMap                     m_states;
    CState                       *m_curstate;    
};

#endif // CSTATEMACHINE_H
