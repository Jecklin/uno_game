#include "CGameLoop.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "CTest.h"
using namespace std;

CGameLoop::CGameLoop()
    :m_player_count(4)
    ,m_toward(1)
    ,m_current(0)
    ,m_box_notopen()
    ,m_box_hasopen()
    ,m_endcard()
    ,m_players()
    ,m_winner()
    ,m_banker()
{
    ;
}

CGameLoop::~CGameLoop()
{
    ;
}
void CGameLoop::GameStart()
{
    this->GameMenu();
    this->GameInit();
    this->GameLoop();
    this->GameOver();
}
void CGameLoop::GameMenu()
{
    cout << "**********  Uno Begin  **********" << endl;
}

void CGameLoop::GameInit()
{
    cout << "**********  Game Init  **********" << endl;
    CCardBox::IterBox it_nbox;
    CCardInfo card_index;
    int len_nbox = 0;

    //InitPlayerName
    this->m_players[0].SetPlayerName("*Zero*");
    this->m_players[1].SetPlayerName("*One*");
    this->m_players[2].SetPlayerName("*Two*");
    this->m_players[3].SetPlayerName("*Three*");

    //InitNopenBox
    this->m_box_notopen.InitNopenBox();
    this->m_box_notopen.RandNopenBox();

    //InitEndCard
    it_nbox = this->m_box_notopen.GetItBegin();
    len_nbox = this->m_box_notopen.GetSize();

    srand((unsigned int)time(nullptr));
    int index_sround = rand()%(len_nbox - 1);

    for (int i = 0; i < index_sround; ++i)
    {
        ++it_nbox;
    }
    card_index = *it_nbox;

    this->m_endcard.SetAction(card_index.GetAction());
    this->m_endcard.SetColor(card_index.GetColor());
    this->m_endcard.SetId(card_index.GetId());

    //InitBanker
    srand((unsigned int)time(nullptr));
    this->m_current = rand() % 3;
    this->m_banker = this->m_players[this->m_current];

    //RoundOne
    for (int round = 0; round < 7; ++round)
    {
        for (int i = 0; i < 4; ++i)
        {
            it_nbox = this->m_box_notopen.GetItBegin();
            card_index = *it_nbox;

            this->m_players[i].AddCard(card_index);
            this->m_box_notopen.RemoveCard(card_index);

        }
    }

    //*测试  ******************************************//
    CTest test;
    cout << "end card: ";
    test.PrintCard(this->m_endcard);
    cout << endl;

    cout << "banker: " << this->m_banker.GetPlayerName() << endl;

    for (int i = 0; i < 4; ++i)
    {
        CPlayer player;
        player = this->m_players[i];
        test.PrintPlayer(player);
    }
    //*************************************************//
}

void CGameLoop::GameLoop()
{
    cout << "**********  Game Loop  **********" << endl;
    CPlayer *pplayer = nullptr;
    CCardBox::IterBox it_box;
    CCardInfo out_card;
    CCardInfo index_card;
    bool allow_out = false;
    bool allow_add = true;
    do
    {
        pplayer = &this->m_players[this->m_current];
        //判定当前玩家是否为胜者
        if (pplayer->IsEmpty())
        {
            this->m_winner = *pplayer;
            break;
        }
        else
        {
            ;
        }

        //查询当前玩家牌库
        for (it_box = pplayer->GetItBegin(); it_box != pplayer->GetItEnd(); ++it_box)
        {
            index_card = *it_box;

            if ((index_card.GetAction() & this->m_endcard.GetAction())
              ||(index_card.GetColor() & this->m_endcard.GetColor())
              ||(index_card.GetId() == this->m_endcard.GetId()))
            {
                allow_out = true;
                allow_add = false;
                out_card = index_card;
                break;
            }
            else
            {
                ;
            }
        }

        //玩家出牌
        if (allow_out)
        {
            //已出牌库加牌
            this->m_box_hasopen.AddCard(out_card);

            //变换底牌
            this->m_endcard.SetAction(out_card.GetAction());
            this->m_endcard.SetColor(out_card.GetColor());
            this->m_endcard.SetId(out_card.GetId());

            //玩家牌库减牌
            pplayer->RemoveCard(out_card);

            if (out_card.GetAction() & 0xF)
            {
                this->FunctionCardAction(out_card);
            }
            else
            {
                ;
            }
            allow_out = false;
            allow_add = true;
        }

        //玩家摸牌
        else if (allow_add)
        {
            CCardInfo add_card;
            CCardBox::IterBox it_not_box = this->m_box_notopen.GetItBegin();
            if (this->m_box_notopen.IsEmpty())
            {
                this->RecycleOpenBox();;
            }
            add_card = *it_not_box;
            pplayer->AddCard(add_card);
            this->m_box_notopen.RemoveCard(add_card);

            allow_out = false;
            allow_add = true;
        }
        else
        {
            ;
        }

        //设置下一玩家
        this->m_current += this->m_toward;

        if (this->m_current > this->m_player_count - 1)
        {
            this->m_current -= this->m_player_count;
        }
        else if (this->m_current < 0)
        {
            this->m_current += this->m_player_count;
        }
        else
        {
            ;
        }

    }while(true);

    //统计玩家分数
    int score = 0;
    for (int index = 0; index < this->m_player_count; ++index)
    {
        pplayer = &this->m_players[index];
        score = pplayer->GetPlayerScore() - pplayer->GetSize();
        pplayer->SetPlayerScore(score);
    }
    this->m_winner.SetPlayerScore(this->m_winner.GetPlayerScore() + 10);

}

void CGameLoop::GameOver()
{
    cout << "**********  Game Over  **********" << endl;
    cout << "The winner is:" << this->m_winner.GetPlayerName() << endl;
    cout << "The players's scores are: " << endl;
    for (int index = 0; index < this->m_player_count; ++index)
    {
        CPlayer player = this->m_players[index];
        cout << player.GetPlayerName() << " : " << player.GetPlayerScore() << endl;
    }
}

void CGameLoop::FunctionCardAction(const CCardInfo &card)
{
    ECardId index_id = card.GetId();
    if (index_id == ECI_AddTwo)
    {
        this->ActionCardIn(2);
        this->ActionCardStop();
    }
    else if (index_id == ECI_Resverse)
    {
        this->ActionCardReverse();
    }
    else if (index_id == ECI_Stop)
    {
        this->ActionCardStop();
    }
    else if (index_id == ECI_Black)
    {
        this->ActionCardChangeColor();
        this->ActionCardStop();
    }
    else if (index_id == ECI_BlackFour)
    {
        this->ActionCardChangeColor();
        this->ActionCardIn(4);
        this->ActionCardStop();
    }
    else
    {
        ;
    }
}

void CGameLoop::ActionCardIn(int num)
{
    int action_state = this->m_current + this->m_toward;
    CPlayer *pplayer_act = &this->m_players[action_state];
    CCardInfo action_card;
    CCardBox::IterBox it_box_not;
    for (int touch = 0; touch < num; ++touch)
    {
        if (this->m_box_notopen.IsEmpty())
        {
            this->RecycleOpenBox();
        }
        it_box_not = this->m_box_notopen.GetItBegin();
        action_card = *it_box_not;
        this->m_box_notopen.RemoveCard(action_card);
        pplayer_act->AddCard(action_card);
    }
    cout << "** Action ** --- Add Card" << num << " times" << endl;
}

void CGameLoop::ActionCardStop()
{
    m_current += m_toward;
    cout << "** Action ** --- Stop" << endl;
}

void CGameLoop::ActionCardReverse()
{
    if (this->m_toward == 1)
    {
        this->m_toward = -1;
    }
    else if (this->m_toward == -1)
    {
        this->m_toward = 1;
    }
    else
    {
        ;
    }
    cout << "** Action ** --- Reverse" << endl;
}

void CGameLoop::ActionCardChangeColor()
{
    CPlayer *pplayer_act = &this->m_players[this->m_current];
    CCardBox::IterBox it_box = pplayer_act->GetItBegin();
    CCardInfo index_card;
    int len = pplayer_act->GetSize();
    int color[4] = {0}; //red,yellow,blue,green

    for (int index = 0; index < len; ++index)
    {
        index_card = *it_box;
        if (index_card.GetColor() == ECC_Red)
        {
            ++color[0];
        }
        else if (index_card.GetColor() == ECC_Yellow)
        {
            ++color[1];
        }
        else if (index_card.GetColor() == ECC_Blue)
        {
            ++color[2];
        }
        else if (index_card.GetColor() == ECC_Green)
        {
            ++color[3];
        }
        ++it_box;
    }

    int max_color_num = 0;
    for (int index = 1; index < 4; ++index)
    {
        if (color[index] > color[index - 1])
        {
            max_color_num = index;
        }
    }

    if (max_color_num == 0)
    {
        this->m_endcard.SetColor(ECC_Red);
    }
    else if(max_color_num == 1)
    {
        this->m_endcard.SetColor(ECC_Yellow);
    }
    else if (max_color_num == 2)
    {
        this->m_endcard.SetColor(ECC_Blue);
    }
    else if (max_color_num == 3)
    {
        this->m_endcard.SetColor(ECC_Green);
    }
    else
    {
        ;
    }

    cout << "** Action ** --- Change Color " << endl;
}

void CGameLoop::RecycleOpenBox()
{
    cout << "**********  Recycle Open Box  **********" << endl;
    CCardInfo index_card;
    CCardBox::IterBox it_open;

    for (it_open = this->m_box_hasopen.GetItBegin(); it_open != this->m_box_hasopen.GetItEnd(); ++it_open)
    {
        index_card = *it_open;
        this->m_box_notopen.AddCard(index_card);
        this->m_box_hasopen.RemoveCard(index_card);
    }
    this->m_box_notopen.RandNopenBox();
}

