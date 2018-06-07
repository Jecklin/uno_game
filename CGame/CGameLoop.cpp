#include "CGameLoop.h"


#include <iostream>

CGameLoop::CGameLoop()
    :m_players()
    ,m_endcard()
    ,m_open_box()
    ,m_close_box()
    ,m_toward(1)
    ,m_current(0)
    ,m_state_machine(*this)
{
    
}

CGameLoop::~CGameLoop()
{
    delete this->m_fsm;
    delete this->m_stateWait;
    delete this->m_stateStart;
    delete this->m_stateMy;
    delete this->m_stateOther;
    delete this->m_stateAdd;
    delete this->m_stateSub;
    delete this->m_stateEnd;
    delete this->m_stateError;
  
    this->m_fsm         = nullptr;
    this->m_stateWait   = nullptr;
    this->m_stateStart  = nullptr;
    this->m_stateMy     = nullptr;
    this->m_stateOther  = nullptr;    
    this->m_stateAdd    = nullptr;
    this->m_stateSub    = nullptr;
    this->m_stateEnd    = nullptr;
    this->m_stateError  = nullptr;

}

void CGameLoop::startGame()
{
    do
    {
        this->m_state_machine.toNextState();
        
    }while(!this->m_state_machine.isEndState());
    
}

void CGameLoop::initGame()
{
    CPlayer   *gi_player;
    CCardInfo card_index;
    
    //Init players name
    gi_player = &(this->m_players[0]);
    gi_player->setPlayerName("*Lili*");

    gi_player = &(this->m_players[1]);
    gi_player->setPlayerName("*Jack*");

    gi_player = &(this->m_players[2]);
    gi_player->setPlayerName("*Anna*");

    gi_player = &(this->m_players[3]);
    gi_player->setPlayerName("*Tom*");
    
    //Init close box
    this->m_close_box.initBox();
    this->m_close_box.randomBox();
    
    //Init end card
    card_index = this->m_close_box.getRandomCard();
    this->m_endcard.setCard(card_index);
    this->m_close_box.subCard(card_index);
    
    //Init one round
    for (int round = 0; round < 7; ++round)
    {
        for (unsigned int i = 0; i < this->m_players.size(); ++i)
        {
            gi_player = &(this->m_players[i]);
            card_index = this->m_close_box.getEndCard();
            gi_player->playerAddCard(card_index);
            this->m_close_box.subCard(card_index);
        }
    }
    
    //Init state machine
    this->m_state_machine.init();
        
}


void CGameLoop::doPunish(const CCardInfo &punish_card)
{
    if (punish_card.isFunctionCard())
    {
        if (punish_card.getId() == ECI_AddTwo)
        {
            this->actInCard(2);
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

void CGameLoop::changeToward() const
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

void CGameLoop::curToNext()
{
    this->m_current = this->getNextLocation();
}

bool CGameLoop::curPlayerAllowOut(const CCardInfo &out_card)
{
    bool is_allow = false;
    CPlayer *pplayer = &(this->m_players[this->m_current]);
    
    if (pplayer->isAllowOut(out_card, this->m_endcard))
    {
        is_allow = true;
    }
    else
    {
        ;
    }
        
    return is_allow;
}

bool CGameLoop::curPlayerAllowOut()
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

void CGameLoop::curPlayerInCard()
{
    //Player touch card
    if (this->m_close_box.isEmpty())
    {
        this->m_close_box.removeBox(this->m_open_box);
    }
    
    //Open box resicle
    else
    {
        CCardInfo card_index = this->m_close_box.getEndCard();
        CPlayer *pplayer = &(this->m_players[this->m_current]);
        pplayer->playerAddCard(card_index);
        this->m_close_box.subCard(card_index);
    }
    
}

void CGameLoop::curPlayerOutCard()
{
    //Player out card
    CPlayer     *pplayer = &(this->m_players[this->m_current]);
    CCardInfo   out_card = pplayer->getOutCard();

    this->m_box_open.push_back(out_card);
    this->m_endcard.setCard(out_card);
    pplayer->playerSubCard(out_card);
    
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
}

void CGameLoop::actNextAddCard(int num)
{
    int                             next          = this->getNextLocation();
    CPlayer                         *pplayer_next = &(m_players[next]);
    CCardInfo                       card_index;
    
    for (int touch = 0; touch < num; ++touch)
    {
        if (this->m_close_box.isEmpty())
        {
            this->m_close_box.removeBox(this->m_open_box);
        }
        else
        {
            ;
        }
        
        card_index = this->m_close_box.getEndCard();
        pplayer_next->playerAddCard(card_index);
        this->m_close_box.subCard(card_index);
    }
}

void CGameLoop::actStop()
{
    this->m_current = this->getNextLocation();
}

void CGameLoop::actReverse()
{
    this->changeToward();
}

void CGameLoop::actChangeColor()
{
    CPlayer *pplayer_cur = &(this->m_players[this->m_current]);
    this->m_endcard.setColor(pplayer_cur->getMaxColor());
}

unsigned int CGameLoop::getNextLocation()
{
    unsigned int next = m_current + m_toward;
    if (next > m_players.size() - 1)
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

void CGameLoop::setAllScores()
{
    CPlayer *pplayer    = nullptr;
    int     num         = 0;

    //other player sub score
    for (unsigned int index = 0; index < this->m_players.size(); ++index)
    {
        pplayer = &(this->m_players[index]);
        num = pplayer->getBoxSize();
        pplayer->setPlayerScore(num);
    }

//    //winner add score
//    pplayer = &(this->m_players[this->m_winner]);
//    pplayer->playerAddScore();
}

void CGameLoop::startGame()
{
    this->initGame();
    this->m_fsm->tick();
}

void CGameLoop::initGame()
{
    CPlayer   *gi_player;
    CCardInfo card_index;
    
    //Init players name
    gi_player = &(this->m_players[0]);
    gi_player->setPlayerName("*Lili*");

    gi_player = &(this->m_players[1]);
    gi_player->setPlayerName("*Jack*");

    gi_player = &(this->m_players[2]);
    gi_player->setPlayerName("*Anna*");

    gi_player = &(this->m_players[3]);
    gi_player->setPlayerName("*Tom*");
    
    //Init close box
    this->m_close_box.initBox();
    this->m_close_box.randomBox();
    
    //Init end card
    card_index = this->m_close_box.getRandomCard();
    this->m_endcard.setCard(card_index);
    this->m_close_box.subCard(card_index);
    
    //Init one round
    for (int round = 0; round < 7; ++round)
    {
        for (unsigned int i = 0; i < this->m_players.size(); ++i)
        {
            gi_player = &(this->m_players[i]);
            card_index = this->m_close_box.getEndCard();
            gi_player->playerAddCard(card_index);
            this->m_close_box.subCard(card_index);
        }
    }
        
}


void CGameLoop::doPunish()
{
    CPlayer *pplayer_cur = &(this->m_players[this->m_current]);
    CCardInfo punish_card = pplayer_cur->getOutCard();
    if (punish_card.isFunctionCard())
    {
        if (punish_card.getId() == ECI_AddTwo)
        {
            this->actInCard(2);
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


bool CGameLoop::curPlayerIsWinner() const
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

void CGameLoop::curToNext()
{
    this->m_current = this->getNextLocation();
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

void CGameLoop::showNotAllow()
{
    ;
}


bool CGameLoop::otherAllowOut()
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

void CGameLoop::curPlayerInCard()
{
    //Player touch card
    if (this->m_close_box.isEmpty())
    {
        this->m_close_box.removeBox(this->m_open_box);
    }
    
    //Open box resicle
    else
    {
        CCardInfo card_index = this->m_close_box.getEndCard();
        CPlayer *pplayer = &(this->m_players[this->m_current]);
        pplayer->playerAddCard(card_index);
        this->m_close_box.subCard(card_index);
    }
    
}

void CGameLoop::curPlayerOutCard()
{
    //Player out card
    CPlayer     *pplayer = &(this->m_players[this->m_current]);
    CCardInfo   out_card = pplayer->getOutCard();

    this->m_box_open.push_back(out_card);
    this->m_endcard.setCard(out_card);
    pplayer->playerSubCard(out_card);
    
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
}

void CGameLoop::actNextAddCard(int num)
{
    int                             next          = this->getNextLocation();
    CPlayer                         *pplayer_next = &(m_players[next]);
    CCardInfo                       card_index;
    
    for (int touch = 0; touch < num; ++touch)
    {
        if (this->m_close_box.isEmpty())
        {
            this->m_close_box.removeBox(this->m_open_box);
        }
        else
        {
            ;
        }
        
        card_index = this->m_close_box.getEndCard();
        pplayer_next->playerAddCard(card_index);
        this->m_close_box.subCard(card_index);
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
    this->m_endcard.setColor(pplayer_cur->getMaxColor());
}

unsigned int CGameLoop::getNextLocation()
{
    unsigned int next = m_current + m_toward;
    if (next > m_players.size() - 1)
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

void CGameLoop::setAllScores()
{
    CPlayer *pplayer    = nullptr;
    int     num         = 0;

    //other player sub score
    for (unsigned int index = 0; index < this->m_players.size(); ++index)
    {
        pplayer = &(this->m_players[index]);
        num = pplayer->getBoxSize();
        pplayer->setPlayerScore(num);
    }

//    //winner add score
//    pplayer = &(this->m_players[this->m_winner]);
//    pplayer->playerAddScore();
}

void CGameLoop::gameRound(bool is_my)
{
    
    do
    {
        this->m_fsm->tick();
        
        if (this->m_fsm->curStateIsMy())
        {
            this->m_fsm->tick();
            
            if (this->m_fsm->curStateIsError())
            {
                emit error();
                break;
            }
            else if (this->m_fsm->curStateIsIn())
            {
                emit inCard();
                break;
            }
            else if (this->m_fsm->curStateIsOut())
            {
                emit outCard(this->m_fsm->getOutCard());
                break;
            }
            else if (this->m_fsm->curStateIsEnd())
            {
                emit gameOver();
                break;
            }
            else
            {
                ;
            }
            
            emit playerChanged(this->m_fsm->getCurrent());
            emit endCardChanged();
    
            
        }while(this->m_fsm->curStateIsMy());
        
        emit curPlayerFlash();
        
    }
    
    //Other round
    else
    {

        do
        {
            ;
        }
        if (this->m_fsm->curStateIsError())
        {
            emit error();
        }
        

        emit playerChanged();
        emit endCardChanged();
        emit scoreChanged();  
//        sleep(5);
        
    }while(!this->m_fsm->curStateIsEnd());

    emit gameOver();
}

CPlayer CGameLoop::getPlayer(int num)
{
    return this->m_fsm->getPlayer(num);
}

CCardInfo CGameLoop::getEndCard()
{
    return this->m_fsm->getEndCard();
}

int CGameLoop::getCurrent()
{
    return this->m_fsm->getCurrent();
}

void CGameLoop::setChoice(int choice)
{
    this->m_fsm->setChoiceOfNum(choice);
}

int CGameLoop::getChoice()
{
    return this->m_fsm->getChoiceOfNum();
}

CCardInfo CGameLoop::getOutCard() const
{
    return this->m_fsm->getOutCard();
}

CCardInfo CGameLoop::getInCard() const
{
    return this->m_fsm->getInCard();
}

void CGameLoop::setOutCard(const CCardInfo &card)
{
    this->m_fsm->setOurCard(card);
}

void CGameLoop::setInCard(const CCardInfo &card)
{
    this->m_fsm->setInCard(card);
}

void CGameLoop::setIsChoiced(bool choiced)
{
    this->m_fsm->setIsChoiced(choiced);
}


void CGameLoop::inItFSM()
{
    this->m_fsm->registerState(m_fsm->State_Wait, this->m_stateWait);
    this->m_fsm->registerState(m_fsm->State_Start, this->m_stateStart);
    this->m_fsm->registerState(m_fsm->State_My, this->m_stateMy);
    this->m_fsm->registerState(m_fsm->State_Other, this->m_stateOther);
    this->m_fsm->registerState(m_fsm->State_Add, this->m_stateAdd);
    this->m_fsm->registerState(m_fsm->State_Sub, this->m_stateSub);
    this->m_fsm->registerState(m_fsm->State_End, this->m_stateEnd);
    this->m_fsm->registerState(m_fsm->State_Error, this->m_stateError);
    
    //Init State = wait;
    this->m_fsm->initFSM(m_fsm->State_Wait);

    
}




