#ifndef CGAMELOOP_H
#define CGAMELOOP_H

#include "datatypedefine.h"
#include "CPlayer.h"

class CGameLoop
{
public:
    CGameLoop();
    ~CGameLoop();
    void GameStart();

private:
    void GameMenu();
    void GameInit();
    void GameLoop();
    void GameOver();

    void InitPlayerName();
    void InitNopenBox();
    void RandNopenBox();
    void InitEndCard();
    void InitBanker();
    void RoundOne();

    void FunctionCardAction(const CCardInfo &card);
    void SetPlayerScore();

    void ActionCardIn(int num);
    void ActionCardStop();
    void ActionCardReverse();
    void ActionCardChangeColor();
    void RecycleOpenBox();

private:
    int          m_player_count;                 //玩家人数
    int          m_banker_location;              //庄家位置
    int          m_toward;                       //出牌方向标识
    int          m_current;                      //当前出牌玩家位置
    CCardBox     m_box_notopen;                  //未起牌库
    CCardBox     m_box_hasopen;                  //已出牌库
    CCardInfo    m_endcard;                      //底牌
    CPlayer      m_players[4];                   //玩家数组
    CPlayer      m_winner;                       //赢家

};

#endif // CGAMELOOP_H
