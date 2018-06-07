#ifndef CGAMELOOP_H
#define CGAMELOOP_H
#include <QWidget>
#include "CDeskBox.h"
#include "CCardInfoEnd.h"
#include "CPlayer.h"
#include "CStateMachine/CStateMachine.h"

class CGameLoop: public QWidget
{
    Q_OBJECT
    
public:
    CGameLoop();
    ~CGameLoop();
    
    //StateStart
    void            startGame();                          
    void            initGame();                           
                     
    
    //StateWait
    bool            curPlayerIsMy();
    
    //StateMy
    bool            curPlayerIsGiveUp();
    void            curPlayerChangeToGiveUp();
    bool            myAllowOut();

    
    //StateOther                            
    bool            otherAllowOut();
    
    //StateAdd
    void            curPlayerInCard();                              
    
    //StateSub
    void            curPlayerOutCard();   
    void            doPunish();                             //执行惩罚
    bool            curPlayerIsWinner() const;
    void            curToNext(); 
    
    //StateEnd
    
    
    //StateError
    void            showNotAllow();
 

private:
    //Do punish
    void            actNextAddCard(int num);
    void            actStop();
    void            actReverse();
    void            actChangeColor(); 
    unsigned int    getNextLocation();
    void            setAllScores(); 
    
private:
    std::vector<CPlayer>                m_players;              //玩家数组
    CCardInfoEnd                        m_endcard;              //底牌
    CDeskBox                            m_open_box;             //已出牌库
    CDeskBox                            m_close_box;            //未起牌库
    int                                 m_toward;               //出牌方向标识
    int                                 m_current;              //当前出牌玩家位置
    CStateMachine                       m_state_machine;
};


#endif // CGAMELOOP_H
