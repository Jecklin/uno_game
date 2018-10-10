#ifndef CTFMYTOADD_H
#define CTFMYTOADD_H

#include "CAbstractTransform.h"

class CTFMyToAdd : public CAbstractTransform
{
public:
    CTFMyToAdd(CGameLoop *gameloop = nullptr);
    ~CTFMyToAdd();

public:
    virtual bool        transForm();
    virtual int         srcState() const;
    virtual int         tarState() const;
    
private:
    int                 m_src;
    int                 m_tar;
    CGameLoop           *m_gameloop;
};

#endif // CTFMYTOADD_H
