#ifndef CTFMYTOERROR_H
#define CTFMYTOERROR_H

#include "CAbstractTransform.h"

class CTFMyToError : public CAbstractTransform
{
public:
    CTFMyToError(CGameLoop *gameloop = nullptr);
    ~CTFMyToError();

public:
    virtual bool        transForm();
    virtual int         srcState() const;
    virtual int         tarState() const;
    
private:
    int                 m_src;
    int                 m_tar;
    CGameLoop           *m_gameloop;
};
#endif // CTFMYTOERROR_H
