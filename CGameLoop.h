#ifndef CGAMELOOP_H
#define CGAMELOOP_H
#include <QWidget>
#include "FSM.h"
#include "CAbState.h"
#include "CDeskBox.h"
#include "CCardInfoEnd.h"
#include "CPlayer.h"

class CGameLoop: public QWidget
{
    Q_OBJECT
    
public:
    CGameLoop();
    ~CGameLoop();
    
    //StateWait
    void            startGame();                          
    void            initGame();                           
    void            curToNext();                      
    
    //StateStart
    bool            curPlayerIsMy();
    
    //StateMy
    bool            curPlayerIsGiveUp();
    void            curPlayerChangeToGiveUp();
    bool            curPlayerAllowOut(const CCardInfo &out_card);     
    
    //StateOther
    bool            curPlayerAllowOut();                              
    
    //StateAdd
    void            curPlayerInCard();                              
    
    //StateSub
    void            curPlayerOutCard();   
    void            doPunish(const CCardInfo &punish_card); //执行惩罚
    void            changeToward() const;                   //改变出牌方向
    
    
    //StateEnd
    
    
    //StateError
    
 

private:
    //Do punish
    void            actNextAddCard(int num);
    void            actStop();
    void            actReverse();
    void            actChangeColor(); 
    unsigned int    getNextLocation();
    void            setAllScores(); 
    

    
//private:
//    void            inItFSM();

private:
    std::vector<CPlayer>                m_players;              //玩家数组
    CCardInfoEnd                        m_endcard;              //底牌
    CDeskBox                            m_open_box;             //已出牌库
    CDeskBox                            m_close_box;            //未起牌库
    int                                 m_toward;               //出牌方向标识
    int                                 m_current;              //当前出牌玩家位置

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

//signals:
//    void            playerChanged(int current);
//    void            endCardChanged();
//    void            error();
//    void            gameOver();
//    void            curPlayerFlash();
//    void            curPlayerFlashOver();









#endif // CGAMELOOP_H
