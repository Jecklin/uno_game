#ifndef CTFADDTOWAIT_H
#define CTFADDTOWAIT_H

#include "CAbstractTransform.h"

class CTFAddToWait : public CAbstractTransform
{
public:
    CTFAddToWait(CGameLoop *gameloop = nullptr);
    ~CTFAddToWait();

public:
    virtual bool        transForm();
    virtual int         srcState() const;
    virtual int         tarState() const;
    
private:
    int                 m_src;
    int                 m_tar;
    CGameLoop           *m_gameloop;
};
#endif // CTFADDTOWAIT_H
