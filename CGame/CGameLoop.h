#ifndef CGAMELOOP_H
#define CGAMELOOP_H
#include <QWidget>
#include "CDeskBox.h"
#include "CCardInfoEnd.h"
#include "CPlayer.h"
#include "CStateMachine/CStateMachine.h"
#include "CDataBase.h"

class CGameLoop: public QWidget
{
    Q_OBJECT
    
public:
    CGameLoop();
    ~CGameLoop();
    
    //StateStart
    void            startGame();                          
    void            initGame();
    void            changeEndCard(const CCardInfo &card);
    int             getPlayerScore(int current);
    void            gameRound();
                      
    //StateWait
    bool            curPlayerIsMy();
    
    //StateMy
    bool            curPlayerIsGiveUp();
    void            curPlayerChangeToGiveUp();
    void            resetGiveUp();
    
    bool            curPlayerIsChoicedCard();
    void            curPlayerChangeOutCard(const CCardInfo &card);
    void            resetChoicedCard();
    bool            myAllowOut();
    
    //StateOther                            
    bool            otherAllowOut();
    
    //StateAdd
    void            curPlayerInCard();                              
    void            playerTouchCard(int player_num);
    
    //StateSub
    void            curPlayerOutCard();
    bool            curPlayerIsWinner();
    void            doPunish();                             //执行惩罚
    void            curToNext(); 
    void            setChangeColor(ECardColor color);
    ECardColor      getChangeColor();
  
    //StateError
    void            errorPromt();
 
    //StateEnd
    void                setAllScores();
    CDataBase::DbInfo&  getDb(int row);
    CPlayer             getPlayer(int num);
    
signals:
    void            playerInCard(CCardInfo in_card, int current);
    void            playerOutCard(CCardInfo out_card, int current);
    void            endCardChanged(CCardInfo end_card);
    void            notAllowOut();
    void            gameOver();
    void            changeColor(ECardColor color);
    
private:
    //Do punish   
    void            actNextAddCard(int num);
    void            actStop();
    void            actReverse();
    void            actChangeColor(); 
    int             getNextLocation();
    void            clearPlayerBox(int num);

    
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
};


#endif // CGAMELOOP_H
