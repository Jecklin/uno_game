#ifndef CGAMELOOP_H
#define CGAMELOOP_H
#include <QWidget>
#include "FSM.h"
#include "CAbState.h"

class CGameLoop: public QWidget
{
    Q_OBJECT
    
public:
    CGameLoop();
    ~CGameLoop();
    
    void            gameRound(bool is_my);
    bool            curIsMy();
    CPlayer         getPlayer(int num);
    CCardInfo       getEndCard();
    int             getCurrent();
    void            setChoice(int choice);
    int             getChoice();
  
signals:
    void            playerChanged(int current);
    void            endCardChanged();
    void            error();
    void            gameOver();
    void            curPlayerFlash();
    void            curPlayerFlashOver();
    
private:
    void            inItFSM();

private:    
    FSM             *m_fsm;
    CAbState        *m_stateWait;
    CAbState        *m_stateStart;
    CAbState        *m_stateMy;
    CAbState        *m_stateOther;
    CAbState        *m_stateAdd;
    CAbState        *m_stateSub;
    CAbState        *m_stateEnd;
    CAbState        *m_stateError;
};
#endif // CGAMELOOP_H
