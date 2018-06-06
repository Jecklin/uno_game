#ifndef CSTATEMACHINE_H
#define CSTATEMACHINE_H

#include "CAbstractState.h"
#include <list>

class CGameLoop;
class CState;

class CStateMachine:public CAbstractState
{
public:
    explicit                CStateMachine(CGameLoop *loop);
    virtual                 ~CStateMachine();
    
public:
    virtual int             getCurState() const;
    virtual int             toNextState();
    
public:
    void                    init();
    void                    unInit();
    
private:
    std::list<CState>       m_states;
    CGameLoop               *m_gameloop;
    int                      m_cur_state;
};

#endif // CSTATEMACHINE_H
