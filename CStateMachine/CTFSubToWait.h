#ifndef CTFSUBTOWAIT_H
#define CTFSUBTOWAIT_H

#include "CAbstractTransform.h"

class CTFSubToWait : public CAbstractTransform
{
public:
    CTFSubToWait(CGameLoop *gameloop = nullptr);
    ~CTFSubToWait();

public:
    virtual bool        transForm();
    virtual int         srcState();
    virtual int         tarState();
    
private:
    int                 m_src;
    int                 m_tar;
    CGameLoop           *m_gameloop;
};
#endif // CTFSUBTOWAIT_H
