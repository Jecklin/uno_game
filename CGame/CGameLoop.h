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
    void            initGame(); 
    void            gameRound();
    void            setEndCard(const CCardInfo &card);
    void            setEndCard(ECardColor color);
    int             getPlayerScore(const CPlayer &player);
    int             current();
    int             next();

    
    //StateWait
    bool            myRound();
    void            curToNext(); 
    
    //StateMy
    bool            giveUp() const;
    void            setGiveUp(bool giveup);    
    bool            choiced() const;
    void            setChoiced(bool choiced);    
    void            setOutCard(const CCardInfo &card);
    bool            myAllowed();
    
    //StateOther                            
    bool            otherAllowed();
    
    //StateAdd
    void            addCard(int playerNum); //下面两个函数改成这一个，还没实现
    
    //StateSub
    void            curOutCard();
    bool            curPlayerEmpty();
    void            doPunish();                             //执行惩罚
    
    void            actChangeColor(); 
    void            setChangeColor(ECardColor color);
    ECardColor      getChangeColor();
  
    //StateError
    void            errorPromt();
 
    //StateEnd
    void            setAllScores();
    CPlayer         getPlayer(int num);
    int             getPlayerSize();                        //获得玩家人数
      
    
signals:
    void            sPlayerAddCard(CCardInfo in_card, int current);
    void            sPlayerOutCard(CCardInfo out_card, int current);
    void            sEndCardChanged(CCardInfo end_card);
    void            sNotAllowOut();
    void            sGameOver();
    void            sChangeColor(ECardColor color);
    
    
private:
    std::vector<CPlayer>            m_players;              //玩家数组
    CCardInfoEnd                    m_endcard;              //底牌
    CDeskBox                        m_open_box;             //已出牌库
    CDeskBox                        m_close_box;            //未起牌库
    CStateMachine                   *m_state_machine;       //状态机
    bool                            m_giveup;               //选择放弃
    bool                            m_choiced;              //选择出牌
    ECardColor                      m_change_color;         //选择要改变成的颜色
    CDataBase                       *m_db;                  //数据库
    CGameRule                       *m_rule;
};


#endif // CGAMELOOP_H
