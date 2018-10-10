#ifndef CTFWAITTOMY_H
#define CTFWAITTOMY_H

#include "CAbstractTransform.h"

class CTFWaitToMy : public CAbstractTransform
{
public:
    CTFWaitToMy(CGameLoop *gameloop = nullptr);
    ~CTFWaitToMy();

public:
    virtual bool        transForm();
    virtual int         srcState() const;
    virtual int         tarState() const;
    
private:
    int                 m_src;
    int                 m_tar;
    CGameLoop           *m_gameloop;
};

#endif // CTFWAITTOMY_H
