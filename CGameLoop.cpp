#include "CGameLoop.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

CGameLoop::CGameLoop()
    :m_player_count(4)
    ,m_banker_location(0)
    ,m_toward(1)
    ,m_current(0)
    ,m_box_notopen()
    ,m_box_hasopen()
    ,m_endcard()
    ,m_players()
    ,m_winner()
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
    this->SetPlayerScore();
    this->GameOver();
}
void CGameLoop::GameMenu()
{
    cout << "**********  Uno Begin  **********" << endl;
}

void CGameLoop::GameInit()
{
    cout << "**********  Game Init  **********" << endl;

    //初始化玩家名字
    this->InitPlayerName();

    //初始化未起牌库
    this->InitNopenBox();
    this->RandNopenBox();

    //设置第一张底牌
    this->InitEndCard();

    //设置第一轮出牌玩家
    this->InitBanker();

    //第一轮，玩家摸7张牌
    this->RoundOne();

}

void CGameLoop::GameLoop()
{
    cout << "**********  Game Loop  **********" << endl;
    do
    {
        CPlayer player_cur= this->m_players[this->m_current];
        //判定当前玩家是否为胜者
        if (player_cur.IsEmpty())
        {
            this->m_winner = player_cur;
            //*测试
            cout << "Here has winner :  "
                 << player_cur.GetPlayerName() << endl;
            break;
        }
        else
        {
            ;
        }

        CCardBox::IterBox it_box;
        CCardInfo out_card;
        CCardInfo index_card;
        bool allow_out = false;

        //查询当前玩家牌库
        for (it_box = player_cur.GetItBegin(); it_box != player_cur.GetItEnd(); ++it_box)
        {
            index_card = *it_box;

            if ((index_card.GetAction() & this->m_endcard.GetAction())
              ||(index_card.GetColor() & this->m_endcard.GetColor())
              ||(index_card.GetId() == this->m_endcard.GetId()))
            {
                allow_out = true;
                out_card = index_card;
                break;
            }
            else
            {
                ;
            }
        }

        //玩家有牌可出
        if (allow_out)
        {
            this->m_box_hasopen.AddCard(out_card);
            this->m_endcard = out_card;
            player_cur.RemoveCard(out_card);

            if (out_card.GetAction() & 0xF)
            {
                this->FunctionCardAction(out_card);
            }
            else
            {
                ;
            }

            //*测试
            cout << "Player out card :  "
                 << player_cur.GetPlayerName() << " ";
            this->PrintCard(out_card);
            cout << endl;

        }
        else
        {
            CCardInfo add_card;
            CCardBox::IterBox it_not_box = this->m_box_notopen.GetItBegin();
            if (this->m_box_notopen.IsEmpty())
            {
                this->RecycleOpenBox();;
            }
            add_card = *it_not_box;
            player_cur.AddCard(add_card);
            this->m_box_notopen.RemoveCard(add_card);

            //*测试
            cout << "Player in card :  "
                 << player_cur.GetPlayerName() << " ";
            this->PrintCard(add_card);
            cout << endl;
        }

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

}

void CGameLoop::SetPlayerScore()
{
    cout << "**********  Set Player Score  **********" << endl;

    CPlayer player;
    int score = 0;
    for (int index = 0; index < this->m_player_count; ++index)
    {
        player = this->m_players[index];
        score = player.GetPlayerScore() + player.GetSize();
        this->m_players[index].SetPlayerScore(score);
    }
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

void CGameLoop::InitPlayerName()
{
    cout << "**********  Init Player Name  **********" << endl;

    this->m_players[0].SetPlayerName("Jack");
    this->m_players[1].SetPlayerName("Tom");
    this->m_players[2].SetPlayerName("Lili");
    this->m_players[3].SetPlayerName("Anna");

    //*测试
    cout << "players name are:" << endl;
    for (int i = 0; i < 4; ++i)
    {
        CPlayer player = this->m_players[i];

        cout  << player.GetPlayerName() << "\t";
    }
    cout << endl;
}

void CGameLoop::InitNopenBox()
{
    cout << "**********  Init Not Open Box  **********" << endl;
    this->m_box_notopen.InitNopenBox();

    //*测试
    cout << "the not open box's cards are:" << endl;
    this->PrintBox(this->m_box_notopen);
    cout << endl;

}

void CGameLoop::RandNopenBox()
{
    cout << "**********  Rand Not Open Box  **********" << endl;

    CCardBox::IterBox it_box1 = this->m_box_notopen.GetItBegin();
    CCardBox::IterBox it_box2 = this->m_box_notopen.GetItEnd();
    CCardInfo index_card;
    int len_nbox = this->m_box_notopen.GetSize();
    int index_sround;

    srand((unsigned int)time(nullptr));
    for (int change = 0; change < len_nbox - 1; ++change)
    {
        index_sround = rand()%(len_nbox - 1);
        it_box1 = this->m_box_notopen.GetItBegin();
        it_box2 = this->m_box_notopen.GetItEnd();
        --it_box2;

        for (int i = 0; i < index_sround; ++i)
        {
            ++it_box1;
            --it_box2;
        }
        index_card = *it_box1;
        *it_box1 = *it_box2;
        *it_box2 = index_card;
    }

    //*测试
    cout << "the not open box's cards are:" << endl;
    this->PrintBox(this->m_box_notopen);
    cout << endl;
}

void CGameLoop::InitEndCard()
{
    cout << "**********  Init End Card  **********" << endl;
    CCardBox::IterBox it_box = this->m_box_notopen.GetItBegin();
    int len_nbox = this->m_box_notopen.GetSize();

    srand((unsigned int)time(nullptr));
    int index_sround = rand()%(len_nbox - 1);

    for (int i = 0; i < index_sround; ++i)
    {
        ++it_box;
    }

    this->m_endcard = *it_box;

    //*测试
    cout << "the end card is : ";
    this->PrintCard(this->m_endcard);
    cout << endl;

}

void CGameLoop::InitBanker()
{
    cout << "**********  Init Banker  **********" << endl;
    srand((unsigned int)time(nullptr));
    this->m_banker_location = rand() % 3;
    this->m_current = this->m_banker_location;

    //*测试
    CPlayer player = this->m_players[this->m_banker_location];
    cout << "the banker is: " << player.GetPlayerName() << endl;
}

void CGameLoop::RoundOne()
{
    cout << "**********  Round One  **********" << endl;

    CCardBox::IterBox it_box_not;
    CCardInfo card_cur;
    for (int round = 0; round < 7; ++round)
    {
        for (int i = 0; i < 4; ++i)
        {
            it_box_not = this->m_box_notopen.GetItBegin();
            card_cur = *it_box_not;

            this->m_players[i].AddCard(card_cur);
            this->m_box_notopen.RemoveCard(card_cur);

        }
    }

    //*测试
    cout << "After one round, player's box now : " << endl;

    for (int i = 0; i < 4; ++i)
    {
        CPlayer cplayer;
        cplayer = this->m_players[i];
        this->PrintPlayer(cplayer);
        cout << endl;
    }
    cout << endl;
}

void CGameLoop::FunctionCardAction(const CCardInfo &card)
{
    cout << "**********  Function Card Action  **********" << endl;
    ECardId index_id= card.GetId();
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
    cout << "**********  Action Card In  **********" << endl;
    int action_state = this->m_current + this->m_toward;
    CPlayer action_player = this->m_players[action_state];

    CCardInfo action_card;
    CCardBox::IterBox it_box_not = this->m_box_notopen.GetItBegin();
    for (int touch = 0; touch < num; ++touch)
    {
        if (this->m_box_notopen.IsEmpty())
        {
            this->RecycleOpenBox();
        }
        action_card = *it_box_not;
        this->m_box_notopen.RemoveCard(action_card);
        action_player.AddCard(action_card);
    }
}

void CGameLoop::ActionCardStop()
{
    cout << "**********  Action Card Stop  **********" << endl;
    m_current += m_toward;
}

void CGameLoop::ActionCardReverse()
{
    cout << "**********  Action Card Reverse  **********" << endl;
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
}

void CGameLoop::ActionCardChangeColor()
{
    cout << "**********  Action Card Change Color  **********" << endl;
    CPlayer action_player = this->m_players[this->m_current];

    CCardBox::IterBox it_box = action_player.GetItBegin();
    CCardInfo index_card;
    int len = action_player.GetSize();
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
    for (int index = 0; index < 4; ++index)
    {
        if (color[index + 1] > color[index])
        {
            max_color_num = index + 1;
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
}

void CGameLoop::RecycleOpenBox()
{
    cout << "**********  Recycle Open Box  **********" << endl;
    CCardInfo index_card;
    CCardBox::IterBox it_open;

    for (it_open = this->m_box_hasopen.GetItBegin(); it_open != this->m_box_hasopen.GetItEnd(); ++it_open)
    {
        index_card = *it_open;
        this->m_box_hasopen.RemoveCard(index_card);
        this->m_box_notopen.AddCard(index_card);
    }
    this->RandNopenBox();
}

void CGameLoop::PrintCard(CCardInfo &card)
{
    cout << (ECardAction)card.GetAction() << " "
         << (ECardColor)card.GetColor() << " "
         << (ECardId)card.GetId() << "\t";
}

void CGameLoop::PrintBox(CCardBox &box)
{
    CCardBox::IterBox it;
    CCardInfo card;
    cout << "box size: " << box.GetSize() << endl;
    for (it = box.GetItBegin(); it != box.GetItEnd(); ++it)
    {
        card = *it;
        this->PrintCard(card);
    }
}

void CGameLoop::PrintPlayer(CPlayer &player)
{
    CCardBox::IterBox it;
    CCardInfo card;
    cout << "name: " << player.GetPlayerName() << " "
         << "score:" << player.GetPlayerScore() << " "
         << "box size: " << player.GetSize() << endl;
    cout << "cards:" << endl;
    for (it = player.GetItBegin(); it != player.GetItEnd(); ++it)
    {
        card = *it;
        this->PrintCard(card);
    }
}

