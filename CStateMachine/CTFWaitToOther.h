#ifndef CTFWAITTOOTHER_H
#define CTFWAITTOOTHER_H

#include "CAbstractTransform.h"

class CTFWaitToOther : public CAbstractTransform
{
public:
    CTFWaitToOther(CGameLoop *gameloop = nullptr);
    ~CTFWaitToOther();

public:
    virtual bool        transForm();
    virtual int         srcState();
    virtual int         tarState();
    
private:
    int                 m_src;
    int                 m_tar;
    CGameLoop           *m_gameloop;
};

#endif // CTFWAITTOOTHER_H
