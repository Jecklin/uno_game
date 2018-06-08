#ifndef CTFSUBTOEND_H
#define CTFSUBTOEND_H

#include "CAbstractTransform.h"

class CTFSubToEnd : public CAbstractTransform
{
public:
    CTFSubToEnd(CGameLoop *gameloop = nullptr);
    ~CTFSubToEnd();

public:
    virtual bool        transForm();
    virtual int         srcState() const;
    virtual int         tarState() const;
    
private:
    int                 m_src;
    int                 m_tar;
    CGameLoop           *m_gameloop;
};
#endif // CTFSUBTOEND_H
