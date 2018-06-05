#include "FSM.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

FSM::FSM()
    :m_states()
    ,m_curState(-1)
    ,m_box_close()
    ,m_box_open()
    ,m_endcard()
    ,m_players(4)
    ,m_winner(-1)
    ,m_toward(1)
    ,m_current(0)
    ,m_choice(-1)
    ,m_is_choiced(false)
{
    
}

FSM::~FSM()
{
    
}

bool FSM::registerState(int e, CAbState *pState)
{
    m_states[e] = pState;
    return true;
}

bool FSM::transState(int newState)
{
    m_states[m_curState]->onStateExit();
    m_states[newState]->onStateEnter();
    m_curState = newState;
    return true;
}

void FSM::InitState(int s)
{
    std::cout << "**** Begin **** Begin **** Begin **** Begin **** Begin ****" << std::endl << std::endl;
    //InitCurState
    m_curState = s;
    
    //InitPlayerName
    this->initPlayersName();

    //InitCloseBox
    this->initCloseBox();
    this->randCloseBox();

    //InitEndCard
    this->initEndCard();

    //InitBanker
    srand((unsigned int)time(nullptr));
    this->m_current = rand()%(this->m_players.size() - 1);

    //RoundOne
    this->initOneRound();

}

void FSM::tick()
{
    m_states[m_curState]->onStateTick();
}

//bool FSM::endState()
//{
//    bool result = false;
//    if (this->m_curState == State_End)
//    {
//        result = true;
//    }
//    else
//    {
//        ;
//    } 
//    return result;
//}

CPlayer FSM::getPlayer(int num)
{
    return this->m_players[num];
}

CCardInfo FSM::getEndCard()
{
    return this->m_endcard;
}

int FSM::getCurrent()
{
    return this->m_current;
}

bool FSM::hasWinner()
{
    bool has_winner = false;
    if (m_winner == -1)
    {
        ;
    }
    else
    {
        has_winner = true;
    }
    return has_winner;
}

void FSM::toNext()
{
    this->m_current = this->getNextLocation();
}

bool FSM::curIsMy()
{
    bool is_my = false;
    if (m_current == 0)
    {
        is_my = true;
    }
    else
    {
        ;
    }
    return is_my;
}

bool FSM::curStateIsMy()
{
    bool is_my_state = false;
    if (this->m_curState == State_My)
    {
        is_my_state = true;
    }
    else
    {
        ;
    }
    return is_my_state;
}

bool FSM::curStateIsError()
{
    bool is_error = false;
    if (this->m_curState == State_Error)
    {
        is_error = true;
    }
    else
    {
        ;
    }
    return is_error;
}

bool FSM::curStateIsEnd()
{
    bool is_end = false;
    if (this->m_curState == State_End)
    {
        is_end = true;
    }
    else
    {
        ;
    }
    return is_end;
}

bool FSM::curStateIsOut()
{
    bool is_out = false;
    if (this->m_curState == State_Sub)
    {
        is_out = true;
    }
    else
    {
        ;
    }
    return is_out;
    
}

bool FSM::curStateIsIn()
{
    bool is_in = false;
    if (this->m_curState == State_Add)
    {
        is_in = true;
    }
    else
    {
        ;
    }
    return is_in;
}


bool FSM::curPlayerGiveUp(int choice)
{
    bool give_up = false;
    if (choice == 111)
    {
        give_up = true;
    }
    else
    {
        ;
    }
    
    return give_up;
    
}

bool FSM::curPlayerAllowOut()
{
    bool is_allow = false;
    CPlayer *pplayer = &(this->m_players[this->m_current]);
    if (pplayer->isAllowOut(this->m_endcard))
    {
        is_allow = true;
    }
    else
    {
        ;
    }
    
    return is_allow;
}


bool FSM::cardAllowOut(const CCardInfo &card)
{
    bool is_allow = false;
    CPlayer *pplayer = &(this->m_players[this->m_current]);
    if (pplayer->isAllowOut(card, this->m_endcard))
    {
        is_allow = true;
    }
    else
    {
        ;
    }
    
    return is_allow;
}

bool FSM::curPlayerAllowOut(int number)
{
    bool is_allow = false;
    CPlayer *pplayer = &(this->m_players[this->m_current]);
    CCardInfo card_out = pplayer->getNumCard(number);
    
    if ((number < 0) || (number >= pplayer->getBoxSize()))
    {
        cout << "Out Card Error." << endl;
    }
    else
    {
        if (pplayer->isAllowOut(card_out, this->m_endcard))
        {
            is_allow = true;
        }
        else
        {
            ;
        }
    }
    
    return is_allow;
}

void FSM::curPlayerInCard()
{
    //Player touch card
    if (this->m_box_close.empty())
    {
        this->closeBoxReset();
    }
    
    //Open box resicle
    else
    {
        CPlayer *pplayer                          = &(this->m_players[this->m_current]);
        std::list<CCardInfo>::iterator iter_close = this->m_box_close.end();
        this->m_inCard                           = *(--iter_close);
        
        pplayer->playerInCard(m_inCard);
        this->m_box_close.pop_back();
    }
    
}

void FSM::curPlayerOutCard()
{
    //Player out card
    CPlayer     *pplayer = &(this->m_players[this->m_current]);
    this->m_outCard = pplayer->getOutCard();

    this->m_box_open.push_back(m_outCard);
    this->m_endcard.setCard(m_outCard);
    pplayer->playerOutCard(m_outCard);
    
    //Set winner
    if (pplayer->getBoxSize() == 0)
    {
        this->m_winner = this->m_current;
    }
    else
    {
        ;
    }
    
    //Do action card
    if (m_outCard.isFunctionCard())
    {
        if (this->m_endcard.getId() == ECI_AddTwo)
        {
            this->actInCard(2);
            this->actStop();
        }
        else if (this->m_endcard.getId() == ECI_Resverse)
        {
            this->actReverse();
        }
        else if (this->m_endcard.getId() == ECI_Stop)
        {
            this->actStop();
        }
        else if (this->m_endcard.getId() == ECI_Black)
        {
            this->actChangeColor();
            this->actStop();
        }
        else if (this->m_endcard.getId() == ECI_BlackFour)
        {
            this->actChangeColor();
            this->actInCard(4);
            this->actStop();
        }
        else
        {
            ;
        }
    }
    else
    {
        ;
    }
}

void FSM::setAllScores()
{
    CPlayer *pplayer    = nullptr;

    //other player sub score
    for (unsigned int index = 0; index < this->m_players.size(); ++index)
    {
        pplayer = &(this->m_players[index]);
        pplayer->playerSubScore();
    }

    //winner add score
    pplayer = &(this->m_players[this->m_winner]);
    pplayer->playerAddScore();

}

void FSM::setChoiceOfNum(int choice)
{
    this->m_choice = choice;
}

int FSM::getChoiceOfNum()
{
    return this->m_choice;
}

CCardInfo FSM::getOutCard() const
{
    return this->m_outCard;
}

CCardInfo FSM::getInCard() const
{
    return this->m_inCard;
}

void FSM::setOurCard(const CCardInfo &card)
{
    this->m_outCard = card;
}

void FSM::setInCard(const CCardInfo &card)
{
    this->m_inCard = card;
}

void FSM::setIsChoiced(bool choiced)
{
    this->m_is_choiced = choiced;
}

bool FSM::getIsChoiced() const
{
    return this->m_is_choiced;
}




void FSM::initPlayersName()
{
    CPlayer   *gi_player;
    gi_player = &(this->m_players[0]);
    gi_player->playerSetName("*Zero*");

    gi_player = &(this->m_players[1]);
    gi_player->playerSetName("*One*");

    gi_player = &(this->m_players[2]);
    gi_player->playerSetName("*Two*");

    gi_player = &(this->m_players[3]);
    gi_player->playerSetName("*Three*");
}

void FSM::initCloseBox()
{
    //初始化数字牌
    for (int index_eci = ECI_Zero; index_eci != ECI_Nine + 1; ++index_eci)      //id
    {
        CCardInfo index_rcard(ECC_Red, ECardId(index_eci), ECA_None);
        this->m_box_close.push_back(index_rcard);
        this->m_box_close.push_back(index_rcard);

        CCardInfo index_ycard(ECC_Yellow, ECardId(index_eci), ECA_None);
        this->m_box_close.push_back(index_ycard);
        this->m_box_close.push_back(index_ycard);

        CCardInfo index_gcard(ECC_Green, ECardId(index_eci), ECA_None);
        this->m_box_close.push_back(index_gcard);
        this->m_box_close.push_back(index_gcard);

        CCardInfo index_bcard(ECC_Blue, ECardId(index_eci), ECA_None);
        this->m_box_close.push_back(index_bcard);
        this->m_box_close.push_back(index_bcard);

    }

    //初始化 +2 功能牌
    CCardInfo index_atrcard(ECC_Red, ECI_AddTwo, ECA_ActionTwo);
    this->m_box_close.push_back(index_atrcard);
    this->m_box_close.push_back(index_atrcard);

    CCardInfo index_atycard(ECC_Yellow, ECI_AddTwo, ECA_ActionTwo);
    this->m_box_close.push_back(index_atycard);
    this->m_box_close.push_back(index_atycard);

    CCardInfo index_atgcard(ECC_Green, ECI_AddTwo, ECA_ActionTwo);
    this->m_box_close.push_back(index_atgcard);
    this->m_box_close.push_back(index_atgcard);

    CCardInfo index_atbcard(ECC_Blue, ECI_AddTwo, ECA_ActionTwo);
    this->m_box_close.push_back(index_atbcard);
    this->m_box_close.push_back(index_atbcard);

    //初始化 反转 功能牌
    CCardInfo index_rrcard(ECC_Red, ECI_Resverse, ECA_Reverse);
    this->m_box_close.push_back(index_rrcard);
    this->m_box_close.push_back(index_rrcard);

    CCardInfo index_rycard(ECC_Yellow, ECI_Resverse, ECA_Reverse);
    this->m_box_close.push_back(index_rycard);
    this->m_box_close.push_back(index_rycard);

    CCardInfo index_rgcard(ECC_Green, ECI_Resverse, ECA_Reverse);
    this->m_box_close.push_back(index_rgcard);
    this->m_box_close.push_back(index_rgcard);

    CCardInfo index_rbcard(ECC_Blue, ECI_Resverse, ECA_Reverse);
    this->m_box_close.push_back(index_rbcard);
    this->m_box_close.push_back(index_rbcard);

    //初始化 停止 功能牌
    CCardInfo index_srcard(ECC_Red, ECI_Stop, ECA_Stop);
    this->m_box_close.push_back(index_srcard);
    this->m_box_close.push_back(index_srcard);

    CCardInfo index_sycard(ECC_Yellow, ECI_Stop, ECA_Stop);
    this->m_box_close.push_back(index_sycard);
    this->m_box_close.push_back(index_sycard);

    CCardInfo index_sgcard(ECC_Green, ECI_Stop, ECA_Stop);
    this->m_box_close.push_back(index_sgcard);
    this->m_box_close.push_back(index_sgcard);

    CCardInfo index_sbcard(ECC_Blue, ECI_Stop, ECA_Stop);
    this->m_box_close.push_back(index_sbcard);
    this->m_box_close.push_back(index_sbcard);

    //初始化 黑牌 高级牌
    CCardInfo index_bcard(ECC_Black, ECI_Black, ECA_Black);
    this->m_box_close.push_back(index_bcard);
    this->m_box_close.push_back(index_bcard);
    this->m_box_close.push_back(index_bcard);
    this->m_box_close.push_back(index_bcard);

    //初始化 +4黑牌 高级牌
    CCardInfo index_bfcard(ECC_Black, ECI_BlackFour, ECA_BlackFour);
    this->m_box_close.push_back(index_bfcard);
    this->m_box_close.push_back(index_bfcard);
    this->m_box_close.push_back(index_bfcard);
    this->m_box_close.push_back(index_bfcard);
}

void FSM::randCloseBox()
{
    std::list<CCardInfo>::iterator iter_one;
    std::list<CCardInfo>::iterator iter_two;
    CCardInfo                      card_index;
    unsigned int                   sround = 0;

    srand((unsigned int)time(nullptr));
    for (unsigned int change = 0; change < 1000; ++change)  //change < this->m_box_close.size()
    {
        //move iter_one
        sround = rand() % (this->m_box_close.size() - 1);
        iter_one = this->m_box_close.begin();
        for (unsigned int i = 0; i < sround; ++i )
        {
            ++iter_one;
        }

        //move iter_two
        sround = rand() % (this->m_box_close.size() - 1);
        iter_two = this->m_box_close.end();
        --iter_two;
        for (unsigned int i = 0; i < sround; ++i )
        {
            --iter_two;
        }

        //change
        card_index = *iter_one;
        *iter_one = *iter_two;
        *iter_two = card_index;
    }
}

void FSM::initEndCard()
{
    std::list<CCardInfo>::iterator iter;
    unsigned int                   sround = 0;
    CCardInfo                      card_index;

    do
    {
        //Get srand card
        iter = this->m_box_close.begin();
        srand((unsigned int)time(nullptr));
        sround = rand() % (this->m_box_close.size() - 1);

        //Move card
        for (unsigned int move = 0; move < sround; ++ move)
        {            
            ++iter;
        }
        card_index = *iter;

        //Card is black or not
        if (card_index.getColor() == ECC_Black)
        {
            ;
        }
        else
        {
            break;
        }

    }while(true);

    //Set end card
    this->m_endcard.setCard(card_index);
}

void FSM::initOneRound()
{
    CPlayer                         *pplayer;
    CCardInfo                       card;
    std::list<CCardInfo>::iterator  iter;

    for (int round = 0; round < 7; ++round)
    {
        for (unsigned int i = 0; i < this->m_players.size(); ++i)
        {
            iter = this->m_box_close.end();
            --iter;
            pplayer = &(this->m_players[i]);
            card = *iter;

            pplayer->playerInCard(card);
            this->m_box_close.pop_back();
        }
    }
}

void FSM::actInCard(int num)
{
    int                             next          = this->getNextLocation();
    CPlayer                         *pplayer_next = &(m_players[next]);
    std::list<CCardInfo>::iterator  iter;
    CCardInfo                       card_touch;
    
    for (int touch = 0; touch < num; ++touch)
    {
        if (this->m_box_close.empty())
        {
            this->closeBoxReset();
        }
        else
        {
            ;
        }
        
        iter = this->m_box_close.end();
        --iter;
        card_touch = *iter;
        
        pplayer_next->playerInCard(card_touch);
        this->m_box_close.pop_back();
    }
}

void FSM::actStop()
{
    this->toNext();
}

void FSM::actReverse()
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
}

void FSM::actChangeColor()
{
    CPlayer *pplayer_cur = &(this->m_players[this->m_current]);
    this->m_endcard.setColor(pplayer_cur->getChangeColor());
}

int FSM::getNextLocation()
{
    int next = m_current + m_toward;
    if (next > 3)//m_players.size() - 1
    {
        next -= m_players.size();
    }
    else if (next < 0)
    {
        next += m_players.size();
    }
    else
    {
        ;
    }
    return next;
}

void FSM::closeBoxReset()
{
    std::list<CCardInfo>::iterator iter_open;
    CCardInfo                      card;
    do
    {
        iter_open = this->m_box_open.end();
        --iter_open;
        card = *iter_open;

        this->m_box_close.push_back(card);
        this->m_box_open.pop_back();

    }while(!this->m_box_open.empty());
    
    this->randCloseBox();
}

