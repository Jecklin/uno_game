#pragma once

#include "CAbstractState.h"
#include <QList>

class CAbstractTransform;

class CState:public CAbstractState
{
public:
    CState(int state);
    virtual  ~CState();

    virtual int     GetCurState() const;
    virtual int     ToNextState();

    void            AddTransform(CAbstractTransform *transform);
    void            RemoveTransform(CAbstractTransform *transform);
    
private:
    int                             m_state;
    QList<CAbstractTransform*>      m_transforms;
};


