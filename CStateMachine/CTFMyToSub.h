#ifndef CTFMYTOSUB_H
#define CTFMYTOSUB_H

#include "CAbstractTransform.h"

class CTFMyToSub : public CAbstractTransform
{
public:
    CTFMyToSub(CGameLoop *gameloop = nullptr);
    ~CTFMyToSub();

public:
    virtual bool        transForm();
    virtual int         srcState();
    virtual int         tarState();
    
private:
    int                 m_src;
    int                 m_tar;
    CGameLoop           *m_gameloop;
};
#endif // CTFMYTOSUB_H