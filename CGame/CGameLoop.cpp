#include "CGameLoop.h"

CGameLoop::CGameLoop()
    :m_players()
    ,m_endcard()
    ,m_open_box()
    ,m_close_box()
    ,m_state_machine(nullptr)
    ,m_giveup(false)
    ,m_choiced(false)
    ,m_change_color()
    ,m_db(nullptr)
    ,m_rule(nullptr)
{
    this->m_state_machine = new CStateMachine(this);
    this->m_db            = new CDataBase();
    this->m_rule          = new CGameRule(this);
}

CGameLoop::~CGameLoop()
{
    if (this->m_state_machine != nullptr)
    {
        delete this->m_state_machine;
        this->m_state_machine = nullptr;
    }

    
    if (this->m_db != nullptr)
    {
        delete this->m_db;
        this->m_db = nullptr;
    }
    
    if (this->m_rule != nullptr)
    {
        delete this->m_rule;
        this->m_rule = nullptr;
    }

}

void CGameLoop::initGame()
{
    //Init machine
    this->m_state_machine->inIt();
    
    //Init DataBase
    this->m_db->createDb();

    
    //Init players name
    if (this->m_players.empty())
    {
        CPlayer player_index;
        player_index.setName("Lili");
        this->m_players.push_back(player_index);
        
        player_index.setName("Jack");
        this->m_players.push_back(player_index);    
        
        player_index.setName("Anna");
        this->m_players.push_back(player_index); 
        
        player_index.setName("Tom");
        this->m_players.push_back(player_index);  
    }
 
    
    //Init close box    
    this->m_close_box.initBox();
    this->m_close_box.randomBox();
    
    //Init open box
    this->m_open_box.clearBox();
    
    //Init end card
    CCardInfo card_index = this->m_close_box.backCard();
    this->m_open_box.addCard(card_index);   
    this->setEndCard(card_index);
    this->m_close_box.popCard();
    
    //Init current
    m_rule->sroundCurrent();
    
    //Init one round
    for (int num = 0; num < 4; ++num)
    {
        m_players.at(num).clearBox();
    }
    
    //Do one round
    for (int round = 0; round < ( 7 * 4 ); ++round)
    {
        addCard(current());
        m_rule->toNext();
    }

    
}

void CGameLoop::gameRound()
{
    do
    {
        this->m_state_machine->toNextState();
        
        if (this->m_state_machine->getCurState() == State_End)
        {
            emit sGameOver();
            break;
        }
        else if (this->m_state_machine->getCurState() == State_My)
        {
            break;
        }
               
        //reset choiced
        this->setGiveUp(false);
        
        
    }while(true);
    
}

void CGameLoop::setEndCard(const CCardInfo &card)
{
    this->m_endcard.setCard(card);
    emit this->sEndCardChanged(card);    
}

void CGameLoop::setEndCard(ECardColor color)
{
    CPlayer *player = &(m_players[current()]);
    this->m_change_color = player->getChangeColor();    
    this->m_endcard.setColor(color);
    
    emit sEndCardChanged(this->m_endcard);
    emit sChangeColor(color);
    
}

int CGameLoop::getPlayerScore(const CPlayer &player)
{
    return this->m_db->selectDb(player.getName());
}

int CGameLoop::current()
{
    return m_rule->current();
}

int CGameLoop::next()
{
    return m_rule->next();
}

bool CGameLoop::myRound()
{
    bool is_my = false;
    if (m_rule->current() == 0)
    {
        is_my = true;
    }
    else
    {
        ;
    }
    return is_my;
}

void CGameLoop::curToNext()
{
    m_rule->toNext();
}

bool CGameLoop::giveUp() const
{
    return this->m_giveup;
    
}

void CGameLoop::setGiveUp(bool giveup)
{
    m_giveup = giveup;
}

bool CGameLoop::choiced() const
{
    return this->m_choiced;
}

void CGameLoop::setChoiced(bool choiced)
{
    this->m_choiced = choiced;
}

void CGameLoop::setOutCard(const CCardInfo &card)
{
    CPlayer *player = &(m_players[current()]);
    player->setOutCard(card);
    setChoiced(true);
}


bool CGameLoop::myAllowed()
{
    bool is_allow = false; 
    CPlayer *player = &(m_players[current()]);
    if (player->cardAllow(m_endcard))
    {
        is_allow = true;
    }
    else
    {
        ;
    }
        
    return is_allow;
}

bool CGameLoop::otherAllowed()
{
    bool is_allow = false;
    CPlayer *player = &(m_players[current()]);
    if (player->boxAllow(m_endcard))
    {
        is_allow = true;
    }
    else
    {
        ;
    }
    
    return is_allow;
}

void CGameLoop::addCard(int playerNum)
{
    //Open box resicle
    if (this->m_close_box.empty())
    {
        this->m_close_box.removeBox(this->m_open_box);
    }
    
    //Player touch card
    CCardInfo card = this->m_close_box.backCard();
    CPlayer *player = &(m_players[playerNum]);
    player->addCard(card);
    this->m_close_box.popCard();   
    
    emit sPlayerAddCard(card, playerNum); 
}

void CGameLoop::curOutCard()
{
    //Player out card
    CPlayer *player = &(m_players[current()]);
    CCardInfo card = player->getOutCard();
    m_open_box.addCard(card);
    setEndCard(card);
    player->removeCard(card);
    
    emit sPlayerOutCard(card, current());
    
}

bool CGameLoop::curPlayerEmpty()
{
    bool empty = false;
    CPlayer *player = &(m_players[current()]);
    if (player->getBoxSize() == 0)
    {
        empty = true;
        
    }

    return empty;
}

void CGameLoop::doPunish()
{
    CPlayer *player = &(m_players[current()]);
    CCardInfo card = player->getOutCard();
    if (card.isFunctionCard())
    {
        if (card.getId() == ECI_AddTwo)
        {
            m_rule->actNextAddCard(2);
            m_rule->actStop();
        }
        else if (card.getId() == ECI_Resverse)
        {
            m_rule->actReverse();
        }
        else if (card.getId() == ECI_Stop)
        {
            m_rule->actStop();
        }
        else if (card.getId() == ECI_Black)
        {
            m_rule->actChoiceColor();
            m_rule->actStop();
        }
        else if (card.getId() == ECI_BlackFour)
        {
            m_rule->actChoiceColor();
            m_rule->actNextAddCard(4);
            m_rule->actStop();
        }
        else
        {
            ;
        }    
        
    }
    
}

void CGameLoop::actChangeColor()
{
    if (m_rule->current() == 0)
    {
        ;
    }
    else
    {
        CPlayer *player = &(m_players[current()]);
        m_change_color = player->getChangeColor();
    }
    
    this->m_endcard.setColor(m_change_color);
    
    emit sEndCardChanged(this->m_endcard);
    emit sChangeColor(m_change_color);
}



void CGameLoop::setChangeColor(ECardColor color)
{
    this->m_change_color = color;
}

ECardColor CGameLoop::getChangeColor()
{
    return this->m_change_color;
}

void CGameLoop::errorPromt()
{
    emit sNotAllowOut();
}

void CGameLoop::setAllScores()
{
    //set winner score
    CPlayer *player = &(m_players[current()]);
    QString win_name  = player->getName();
    int     win_score = m_db->selectDb(win_name) + 10;
    
    this->m_db->updateDb(win_name, win_score);
    
    //other player sub score
    for (unsigned int index = 0; index < this->m_players.size(); ++index)
    {
        QString name  = m_players.at(index).getName();
        int     box   = m_players.at(index).getBoxSize();
        int     score = m_db->selectDb(name) - box;
        
        this->m_db->updateDb(name, score);

    }  
}


CPlayer CGameLoop::getPlayer(int num)
{
    CPlayer *pplayer = &(this->m_players[num]);
    return *pplayer;
}

int CGameLoop::getPlayerSize()
{
    return this->m_players.size();
}



