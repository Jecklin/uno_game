#ifndef CTFOTHERTOADD_H
#define CTFOTHERTOADD_H

#include "CAbstractTransform.h"

class CTFOtherToAdd : public CAbstractTransform
{
public:
    CTFOtherToAdd(CGameLoop *gameloop = nullptr);
    ~CTFOtherToAdd();

public:
    virtual bool        transForm();
    virtual int         srcState();
    virtual int         tarState();
    
private:
    int                 m_src;
    int                 m_tar;
    CGameLoop           *m_gameloop;
};
#endif // CTFOTHERTOADD_H