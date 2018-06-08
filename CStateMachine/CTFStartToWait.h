#ifndef CTFSTARTTOWAIT_H
#define CTFSTARTTOWAIT_H

#include "CAbstractTransform.h"

class CTFStartToWait : public CAbstractTransform
{
public:
    CTFStartToWait(CGameLoop *gameloop = nullptr);
    ~CTFStartToWait();

public:
    virtual bool        transForm();
    virtual int         srcState()  const;
    virtual int         tarState()  const;
    
private:
    int                 m_src;
    int                 m_tar;
    CGameLoop           *m_gameloop;
};

#endif // CTFSTARTTOWAIT_H
