#include "CGameLoop.h"
#include "CPlayerAttribute.h"
#include "CPlayer.h"

CGameLoop::CGameLoop()
    :m_players()
    ,m_endcard()
    ,m_openBox()
    ,m_closeBox()
    ,m_judge(nullptr)
    ,m_stateMachine(nullptr)
    ,m_db(nullptr)
{
    this->m_judge         = new CJudge(this);
    this->m_stateMachine  = new CStateMachine(m_judge);
    this->m_db            = new CDataBase();

}

CGameLoop::~CGameLoop()
{
    if (this->m_stateMachine != nullptr)
    {
        delete this->m_stateMachine;
        this->m_stateMachine = nullptr;
    }

    if (this->m_db != nullptr)
    {
        delete this->m_db;
        this->m_db = nullptr;
    }
    
    if (this->m_judge != nullptr)
    {
        delete this->m_judge;
        this->m_judge = nullptr;
    }

    if (!this->m_players.empty())
    {
        delete this->m_players.at(0);
        this->m_players.removeFirst();
    }
    
}

void CGameLoop::InitGame()
{
    //Init machine
    this->m_stateMachine->InIt();
    
    //Init DataBase
    this->m_db->CreateDb();

    
    //Init players name
    if (this->m_players.empty())
    {
        CPlayer *player = new CPlayer("Lili");
        this->m_players.push_back(player);
        
        player = new CPlayer("Jack");
        this->m_players.push_back(player);
        
        player = new CPlayer("Anna");
        this->m_players.push_back(player);
        
        player = new CPlayer("Tom");
        this->m_players.push_back(player);
    }
 
    
    //Init close box    
    this->m_closeBox.InitBox();
    this->m_closeBox.RandomBox();
    
    //Init open box
    if (!m_openBox.Empty())
    {
        m_openBox.RemoveAll();
    }
    
    //Init end card
    CCardInfo topCard = m_closeBox.GetTopCard();
    this->m_openBox.AddCard(topCard);
    this->m_endcard.SetCard(topCard);
    this->m_closeBox.RemoveCard(topCard);
    this->sEndCardChanged(topCard);
    
    
    //Init judge
    this->m_judge->SroundCurStation();
    this->m_judge->SetCloseBox(this->m_closeBox);
    this->m_judge->SetOpenBox(this->m_openBox);
    this->m_judge->SetEndCard(this->m_endcard);
    this->m_judge->SetCurPlayer(this->m_players.at(m_judge->GetCurStation()));
    
    //Init one round
    QVector<CPlayer*>::ConstIterator iter = m_players.begin();
    for (iter; iter != m_players.end(); ++iter)
    {
        CPlayer *player = *iter;
        if (!player->GetBox().Empty())
        {
            player->GetBox().RemoveAll();
        }
        
    }
    
    //Do one round
    for (int i = 0; i < 7 * 4; ++i)
    {
        this->m_judge->CurPlayerAddCard();
        this->m_judge->ToNext();
    }
    
}

void CGameLoop::GameRound()
{
    do
    {
        this->m_stateMachine->ToNextState();
        
        if (this->m_stateMachine->GetCurState() == State_End)
        {
            emit sGameOver();
            break;
        }
        else if (this->m_stateMachine->GetCurState() == State_My)
        {
            break;
        }
               
        //reset choiced
        this->m_judge->SetCurPlayerGiveup(false);
        
        
    }while(true);
    
}


int CGameLoop::GetPlayerScore(CPlayer *player)
{
    return m_db->selectDb(player->GetAttribute().getName());
}



CJudge* CGameLoop::GetJudge()
{
    return this->m_judge;
}

void CGameLoop::SetAllScores()
{
    //set winner score
    int current = this->m_judge->GetCurStation();
    CPlayer *player = this->m_players.at(current);
    QString winName  = player->GetAttribute().getName();
    int     winScore = m_db->selectDb(winName) + 10;
    this->m_db->updateDb(winName, winScore);
    
    //other player sub score
    for (int i = 0; i < 4; ++i)
    {
        player          = this->m_players.at(i);
        QString name    = player->GetAttribute().getName();
        int     box     = player->GetBox().Size();
        int     score   = m_db->selectDb(name) - box;
        this->m_db->updateDb(name, score);
    }
}


CPlayer* CGameLoop::GetPlayer(int num)
{
    CPlayer *player = this->m_players.at(num);
    return player;
}

CCardInfoEnd &CGameLoop::GetEndCard()
{
    return this->m_endcard;
}

