#ifndef CSTATE_H
#define CSTATE_H

#include "CAbstractState.h"
#include <list>

class CAbstractTransform;

class CState:public CAbstractState
{
public:
    explicit        CState(int state);
    virtual         ~CState();
    
public:
    virtual int     getCurState() const;
    virtual int     toNextState();
    
public:
    void            addTransform(CAbstractTransform *transform);
    void            removeTransform(CAbstractTransform *transform);
    
private:
    int                             m_state;
    std::list<CAbstractTransform*>  m_transforms;
};

#endif // CSTATE_H
