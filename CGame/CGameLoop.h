#ifndef CGAMELOOP_H
#define CGAMELOOP_H
#include <QWidget>
#include "CDeskBox.h"
#include "CCardInfoEnd.h"
#include "CPlayer.h"
#include "CStateMachine/CStateMachine.h"
#include "CDataBase.h"
#include "CGameRule.h"

class CGameLoop: public QWidget
{
    Q_OBJECT
    
public:
    CGameLoop();
    ~CGameLoop();
    
    //StateStart
    void            startGame();                          
    void            initGame();
    void            setEndCard(const CCardInfo &card);
    void            setEndCard(ECardColor color);
    int             getPlayerScore(const QString &name);
    void            gameRound();
                      
    //StateWait
    bool            curPlayerIsMy();
    
    //StateMy
    bool            curPlayerIsGiveUp();
    void            setGiveUp();
    void            resetGiveUp();
    
    bool            isChoicedCard();
    void            setOutCard(const CCardInfo &card);
    void            resetChoicedCard();
    bool            myAllowOut();
    
    //StateOther                            
    bool            otherAllowOut();
    
    //StateAdd
    void            curPlayerAddCard();                              
    void            playerAddCard(int player_num);
    
    //StateSub
    void            curPlayerOutCard();
    bool            curPlayerEmpty();
    void            doPunish();                             //执行惩罚
    void            curToNext(); 
    void            setChangeColor(ECardColor color);
    ECardColor      getChangeColor();
  
    //StateError
    void            errorPromt();
 
    //StateEnd
    void                setAllScores();
    CPlayer             getPlayer(int num);
    CPlayer             getWinner();
    CDataBase*          getDb();
    int                 getPlayerSize();
    
    
signals:
    void            sPlayerAddCard(CCardInfo in_card, int current);
    void            sPlayerOutCard(CCardInfo out_card, int current);
    void            sEndCardChanged(CCardInfo end_card);
    void            sNotAllowOut();
    void            sGameOver();
    void            sChangeColor(ECardColor color);
    
private:
    //Do punish   
    void            actNextAddCard(int num);
    void            actStop();
    void            actReverse();
    void            actChangeColor(); 
    int             getNextLocation();


    
private:
    std::vector<CPlayer>            m_players;              //玩家数组
    CCardInfoEnd                    m_endcard;              //底牌
    CDeskBox                        m_open_box;             //已出牌库
    CDeskBox                        m_close_box;            //未起牌库
    int                             m_toward;               //出牌方向标识
    int                             m_current;              //当前出牌玩家位置
    CStateMachine                   *m_state_machine;       //状态机
    bool                            m_is_giveup;            //选择放弃
    bool                            m_is_choiced_card;      //选择出牌
    ECardColor                      m_change_color;         //选择要改变成的颜色
    CDataBase                       *m_db;                  //数据库
    CGameRule                       *m_rule;
};


#endif // CGAMELOOP_H
