#ifndef FSM_H
#define FSM_H
#include <unordered_map>
#include <functional>
#include <unistd.h>

#include "CAbState.h"
#include "CPlayer.h"
#include "CCardInfoEnd.h"
#include <vector>


class CAbState;

class FSM
{
public:
    FSM();
    ~FSM();
    
public: //Game loop
    void        InitState(int s);
    bool        registerState(int e, CAbState *pState);
    bool        transState(int newState);
    void        tick();
<<<<<<< Updated upstream
//    bool        endState();
=======
    bool        curStateIsMy();
    bool        curStateIsError();
    bool        curStateIsEnd();
    bool        curStateIsOut();
    bool        curStateIsIn();
    void        setChoiceOfNum(int choice);
    int         getChoiceOfNum();
    
    CCardInfo   getOutCard() const;
    CCardInfo   getInCard() const;
    void        setOurCard(const CCardInfo &card);
    void        setInCard(const CCardInfo &card);
    
    void        setIsChoiced(bool choiced);
    bool        getIsChoiced() const;

>>>>>>> Stashed changes
    
public: //UI
    CPlayer     getPlayer(int num);
    CCardInfo   getEndCard();
    int         getCurrent();
<<<<<<< Updated upstream
=======
        
//State
    void        curAdd();                           //CStateWait
    bool        curIsMy();                          //CStateStart
    bool        curPlayerGiveUp(int choice);        //CStateMy
    bool        curPlayerAllowOut(int number);      //CStateMy
    bool        curPlayerAllowOut();                //CStateOther
    bool        cardAllowOut(const CCardInfo &card);
    void        curPlayerInCard();                  //CStateAdd
    void        curPlayerOutCard();                 //CStateSub
    bool        hasWinner();                        //CStateSub
    void        setAllScores();                     //CStateEnd
>>>>>>> Stashed changes
    
public: //State
    bool        hasWinner();
    void        toNext();
    bool        curIsMy(); 
    bool        curStateIsMy();
    bool        curStateIsError();
    bool        curStateIsEnd();
    bool        curPlayerGiveUp(int choice);
    bool        curPlayerAllowOut();
    bool        curPlayerAllowOut(int number);
    void        curPlayerInCard();
    void        curPlayerOutCard();
    void        setAllScores();
    void        setChoice(int choice);
    int         getChoice();

 
public:    
    const int   State_Wait    = 1;
    const int   State_Start   = 2;
    const int   State_My      = 3;
    const int   State_Other   = 4;
    const int   State_Add     = 5;
    const int   State_Sub     = 6;
    const int   State_End     = 7;
    const int   State_Error   = 8;
    
private:
    //Init
    void        initPlayersName();
    void        initCloseBox();
    void        randCloseBox();
    void        initEndCard();
    void        initOneRound();
    
    //Card action
    void        actInCard(int num);
    void        actStop();
    void        actReverse();
    void        actChangeColor();
    
    int         getNextLocation();
    void        closeBoxReset();
    
private:
    std::unordered_map<int, CAbState*>  m_states;                       //游戏状态
    int                                 m_curState;                     //当前状态
    std::list<CCardInfo>                m_box_close;                    //未起牌库
    std::list<CCardInfo>                m_box_open;                     //已出牌库
    CCardInfoEnd                        m_endcard;                      //底牌
    std::vector<CPlayer>                m_players;                      //玩家数组
    int                                 m_winner;                       //赢家位置标识
    int                                 m_toward;                       //出牌方向标识
    int                                 m_current;                      //当前出牌玩家位置
    int                                 m_choice;
<<<<<<< Updated upstream
=======
    CCardInfo                           m_outCard;
    CCardInfo                           m_inCard;
    bool                                m_is_choiced;
>>>>>>> Stashed changes
};

#endif // FSM_H




