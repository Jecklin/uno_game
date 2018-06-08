#include "CGameLoop.h"


#include <iostream>

CGameLoop::CGameLoop()
    :m_players()
    ,m_endcard()
    ,m_open_box()
    ,m_close_box()
    ,m_toward(1)
    ,m_current(0)
    ,m_state_machine(nullptr)
{
    this->m_state_machine = new CStateMachine(this);
}

CGameLoop::~CGameLoop()
{
    if (this->m_state_machine == nullptr)
    {
        ;
    }
    else
    {
        delete this->m_state_machine;
        this->m_state_machine = nullptr;
    }
}

void CGameLoop::startGame()
{
    //Init
    this->initGame();
    this->otherRound();
    
}

void CGameLoop::initGame()
{
    //Init players name
    CPlayer player_index;
    player_index.setPlayerName("*Lili*");
    this->m_players.push_back(player_index);
    
    player_index.setPlayerName("*Jack*");
    this->m_players.push_back(player_index);    
    
    player_index.setPlayerName("*Anna*");
    this->m_players.push_back(player_index); 
    
    player_index.setPlayerName("*Tom*");
    this->m_players.push_back(player_index);   
    
    //Init close box
    this->m_close_box.initBox();
    this->m_close_box.randomBox();
    
    //Init end card
    CCardInfo card_index = this->m_close_box.getRandomCard();
    this->m_open_box.addCard(card_index);
    
    this->changeEndCard(card_index);
    
    this->m_close_box.subCard(card_index);
    
    //Init one round
    for (int round = 0; round < ( 7 * 4 ); ++round)
    {
        this->curPlayerInCard();
        this->curToNext();
    }
    
}

void CGameLoop::changeEndCard(const CCardInfo &card)
{
    this->m_endcard.setCard(card);
    emit this->endCardChanged(card);    
}

int CGameLoop::getPlayerScore(int current)
{
    CPlayer *pplayer = &(this->m_players[current]);
    int score = pplayer->getPlayerScore();
    return score;
}

void CGameLoop::myRound()
{
    do
    {
        this->m_state_machine->toNextState();
        if (this->m_state_machine->getCurState() == State_End)
        {
            emit gameOver();
            break;
        }
        else if (this->m_state_machine->getCurState() == State_Error)
        {
            emit notAllowOut();
            break;
        }
        else if (this->m_state_machine->getCurState() == State_Wait)
        {
            this->otherRound();
            break;
        }
        else
        {
            ;
        }
        
    }while(this->m_state_machine->getCurState() == State_My);
}

void CGameLoop::otherRound()
{
    do
    {
        this->m_state_machine->toNextState();
        if (this->m_state_machine->getCurState() == State_End)
        {
            emit gameOver();
            break;
        }
        else
        {
            ;
        }
        
    }while(this->m_state_machine->getCurState() != State_My);
}


bool CGameLoop::curPlayerIsMy()
{
    bool is_my = false;
    if (this->m_current == 0)
    {
        is_my = true;
    }
    else
    {
        ;
    }
    return is_my;
}

bool CGameLoop::curPlayerIsGiveUp()
{
    bool is_giveup = false;
    CPlayer *pplayer = &(this->m_players[this->m_current]);
    if (pplayer->isGiveUp())
    {
        is_giveup = true;
    }
    else
    {
        ;
    }
    return is_giveup;
    
}

void CGameLoop::curPlayerChangeToGiveUp()
{
    CPlayer *pplayer = &(this->m_players[this->m_current]);
    pplayer->changeToGiveUp();
}

void CGameLoop::curPlayerChangeOutCard(const CCardInfo &card)
{
    CPlayer *pplayer = &(this->m_players[this->m_current]);
    pplayer->setOutCard(card);
}

bool CGameLoop::myAllowOut()
{
    bool is_allow = false;
    CPlayer *pplayer = &(this->m_players[this->m_current]);
    
    if (pplayer->cardIsAllowOut(this->m_endcard))
    {
        is_allow = true;
    }
    else
    {
        ;
    }
        
    return is_allow;
}

bool CGameLoop::otherAllowOut()
{
    bool is_allow = false;
    CPlayer *pplayer = &(this->m_players[this->m_current]);
    if (pplayer->boxIsAllowOut(this->m_endcard))
    {
        is_allow = true;
    }
    else
    {
        ;
    }
    
    return is_allow;
}

void CGameLoop::curPlayerInCard()
{
    this->playerTouchCard(this->m_current);
}

void CGameLoop::playerTouchCard(int player_num)
{
    CCardInfo card_index;
    //Player touch card
    if (this->m_close_box.isEmpty())
    {
        this->m_close_box.removeBox(this->m_open_box);
    }

    //Open box resicle
    else
    {
        card_index = this->m_close_box.getEndCard();
        CPlayer *pplayer = &(this->m_players[player_num]);
        pplayer->playerAddCard(card_index);
        this->m_close_box.subCard(card_index);
    }
    
    emit playerInCard(card_index, player_num); 
}

void CGameLoop::curPlayerOutCard()
{
    //Player out card
    CPlayer     *pplayer = &(this->m_players[this->m_current]);
    CCardInfo   out_card = pplayer->getOutCard();

    this->m_open_box.addCard(out_card);
    this->changeEndCard(out_card);
    pplayer->playerSubCard(out_card);
    
    emit playerOutCard(out_card, this->m_current);
    
}

bool CGameLoop::curPlayerIsWinner()
{
    bool is_winner = false;
    CPlayer     *pplayer = &(this->m_players[this->m_current]);
    if (pplayer->getBoxSize() == 0)
    {
        is_winner = true;
    }
    else
    {
        ;
    }
    return is_winner;
}

void CGameLoop::doPunish()
{
    CPlayer *pplayer_cur = &(this->m_players[this->m_current]);
    CCardInfo punish_card = pplayer_cur->getOutCard();
    if (punish_card.isFunctionCard())
    {
        if (punish_card.getId() == ECI_AddTwo)
        {
            this->actNextAddCard(2);
            this->actStop();
        }
        else if (punish_card.getId() == ECI_Resverse)
        {
            this->actReverse();
        }
        else if (punish_card.getId() == ECI_Stop)
        {
            this->actStop();
        }
        else if (punish_card.getId() == ECI_Black)
        {
            this->actChangeColor();
            this->actStop();
        }
        else if (punish_card.getId() == ECI_BlackFour)
        {
            this->actChangeColor();
            this->actNextAddCard(4);
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

void CGameLoop::curToNext()
{
    this->m_current = this->getNextLocation();
}

void CGameLoop::setAllScores()
{
    CPlayer *pplayer_cur = &(this->m_players[this->m_current]);
    int num = 10;
    pplayer_cur->setPlayerScore(num);
    
    //other player sub score
    for (unsigned int index = 0; index < this->m_players.size(); ++index)
    {
        pplayer_cur = &(this->m_players[index]);
        num = pplayer_cur->getBoxSize();
        pplayer_cur->setPlayerScore(-num);
    }
    

    
}

CPlayer CGameLoop::getPlayer(int num)
{
    CPlayer *pplayer = &(this->m_players[num]);
    return *pplayer;
}



void CGameLoop::actNextAddCard(int num)
{
    int next = this->getNextLocation();
    for (int touch = 0; touch < num; ++touch)
    {
        this->playerTouchCard(next);
    }
}

void CGameLoop::actStop()
{
    this->m_current = this->getNextLocation();
}

void CGameLoop::actReverse()
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

void CGameLoop::actChangeColor()
{
    CPlayer *pplayer_cur = &(this->m_players[this->m_current]);
    ECardColor max_color = pplayer_cur->getMaxColor();
    this->m_endcard.setColor(max_color);
    emit endCardChanged(this->m_endcard);
}

int CGameLoop::getNextLocation()
{
    int next = m_current + m_toward;
    if (next > 3)  //m_players.size() - 1
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




