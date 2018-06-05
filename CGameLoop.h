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
    void            gameStart();
    CPlayer         getPlayer(int num);
    CCardInfo       getEndCard();
    int             getCurrent();
    void            setChoice(int choice);
    int             getChoice();
    
<<<<<<< Updated upstream
    
=======
    CCardInfo       getOutCard() const;
    CCardInfo       getInCard() const;
    void            setOutCard(const CCardInfo &card);
    void            setInCard(const CCardInfo &card);
    void            setIsChoiced(bool choiced);
  
>>>>>>> Stashed changes
signals:
    void            playerChanged();
    void            endCardChanged();
    void            scoreChanged();
    void            firstRound();
    void            myRound();
    void            error();
    void            gameOver();
<<<<<<< Updated upstream
=======
    void            curPlayerFlash();
    void            curPlayerFlashOver();
    
    //push button action
    void            outCard(const CCardInfo &card);
    void            inCard();
    
private:
    void            inItFSM();
>>>>>>> Stashed changes

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
