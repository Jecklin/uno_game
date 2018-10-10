#ifndef CTFOTHERTOSUB_H
#define CTFOTHERTOSUB_H

#include "CAbstractTransform.h"

class CTFOtherToSub : public CAbstractTransform
{
public:
    CTFOtherToSub(CGameLoop *gameloop = nullptr);
    ~CTFOtherToSub();

public:
    virtual bool        transForm();
    virtual int         srcState() const;
    virtual int         tarState() const;
    
private:
    int                 m_src;
    int                 m_tar;
    CGameLoop           *m_gameloop;
};

#endif // CTFOTHERTOSUB_H
