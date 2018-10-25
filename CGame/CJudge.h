#pragma once
#include "datatypedefine.h"

class CGameLoop;
class CDeskBox;
class CCardInfoEnd;
class CPlayer;
class CCardInfo;
class CBox;


class CJudge
{
public:
    CJudge(CGameLoop *gameLoop);
    //GameLoop
    
    void    SetCloseBox(CDeskBox &closeBox);
    void    SetOpenBox(CDeskBox &openBox);
    void    SetEndCard(CCardInfoEnd &endCard);
    void    SetCurPlayer(CPlayer *player);
    void    ToNext();
    
    void    ToAuto(bool choiceAuto);
    bool    IsAuto();
    
    int     GetCurStation(); 
    void    SroundCurStation();                 //srand first player
    
    //StateMachine
    bool    CurPlayerGiveUp();
    bool    CurPlayerChoiced();
    bool    CurPlayerAllowedOut();
    bool    AutoCurPlayerAllowedOut();
    bool    CurPlayerEmpty();
    bool    EndCardIsBlack();

    void    CurPlayerAddCard();
    void    CurPlayerOutCard();
    void    CurPlayerChangeColor();
    void    CurPlayerErrorPromt();
    void    Punish();
    
    void    SetCurPlayerChoiced(bool choiced);
    void    SetCurPlayerGiveup(bool giveup);
    void    SetCurPlayerChangedColor(ECardColor color);
    void    SetAllScores();
    

    
private:
    int     getNext();
    
    bool    IsAllowOut(CBox &box);
    bool    IsAllowOut(CCardInfo &outCard);
    
    bool    IsFunctionCard(const CCardInfo &outCard);
    bool    IsSameColor(const CCardInfo &outCard);
    bool    IsSameId(const CCardInfo &outCard);
    bool    IsBlackCard(const CCardInfo &outCard);
    
    void    ActStop();
    void    ActReverse();
    void    ActAddCard(int num);
    void    ActChangeColor();
    
private:
    int             m_curStation;
    int             m_toward;
    CPlayer         *m_curPlayer;
    CCardInfoEnd    *m_endCard;
    CDeskBox        *m_closeBox;
    CDeskBox        *m_openBox;
    bool            m_auto;
    CGameLoop       *m_gameloop;
};

