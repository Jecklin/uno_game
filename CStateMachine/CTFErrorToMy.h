#ifndef CTFERRORTOMy_H
#define CTFERRORTOMy_H

#include "CAbstractTransform.h"

class CTFErrorToMy : public CAbstractTransform
{
public:
    CTFErrorToMy(CGameLoop *gameloop = nullptr);
    ~CTFErrorToMy();

public:
    virtual bool        transForm();
    virtual int         srcState();
    virtual int         tarState();
    
private:
    int                 m_src;
    int                 m_tar;
    CGameLoop           *m_gameloop;
};
#endif // CTFERRORTOMy_H
