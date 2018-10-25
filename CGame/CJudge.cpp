#include "CJudge.h"
#include "CGameLoop.h"
#include <stdlib.h>
#include <time.h>

CJudge::CJudge(CGameLoop *gameLoop)
    :m_curStation(0)
    ,m_toward(1)
    ,m_curPlayer(nullptr)
    ,m_endCard(nullptr)
    ,m_closeBox(nullptr)
    ,m_openBox(nullptr)
    ,m_auto(false)
    ,m_gameloop(nullptr)
{
    this->m_gameloop = gameLoop;
}

void CJudge::SetCloseBox(CDeskBox &closeBox)
{
    this->m_closeBox = &closeBox;
}

void CJudge::SetOpenBox(CDeskBox &openBox)
{
    this->m_openBox = &openBox;
}

void CJudge::SetEndCard(CCardInfoEnd &endCard)
{
    this->m_endCard = &endCard;
}

void CJudge::SetCurPlayer(CPlayer *player)
{
    this->m_curPlayer = player;
}

void CJudge::ToNext()
{
    this->m_curStation = getNext();
    
    //set cur player
    this->m_curPlayer = this->m_gameloop->GetPlayer(m_curStation);
}

void CJudge::ToAuto(bool choiceAuto)
{
    this->m_auto = choiceAuto;
}

bool CJudge::IsAuto()
{
    return this->m_auto;
}

void CJudge::SroundCurStation()
{
    srand((unsigned int)time(nullptr));
    int sround = rand() % (3);
    this->m_curStation = sround;
}

int CJudge::GetCurStation()
{
    return this->m_curStation;
}


bool CJudge::CurPlayerGiveUp()
{
    return this->m_curPlayer->IsGiveUp();
}

bool CJudge::CurPlayerChoiced()
{
    return this->m_curPlayer->IsChoiced();
}

void CJudge::CurPlayerOutCard()
{
    //set cur player
    this->m_curPlayer = this->m_gameloop->GetPlayer(m_curStation);
    
    //out card
    CCardInfo card = this->m_curPlayer->GetOutCard();
    this->m_openBox->AddCard(card);
    this->m_endCard->SetCard(card);
    this->m_curPlayer->RemoveCard(card);
    
    //reset
    this->m_curPlayer->SetChoiced(false);
    
    //emit
    this->m_gameloop->sPlayerOutCard(card, m_curStation);
    this->m_gameloop->sEndCardChanged(card);
}

void CJudge::CurPlayerAddCard()
{
    //Open box resicle
    if (this->m_closeBox->Empty())
    {
        this->m_closeBox->RemoveBox(this->m_openBox);
        this->m_closeBox->RandomBox();
    }
    
    //set cur player
    this->m_curPlayer = this->m_gameloop->GetPlayer(m_curStation);
    
    //add card
    CCardInfo card = this->m_closeBox->GetTopCard();
    this->m_curPlayer->AddCard(card);
    this->m_closeBox->RemoveCard(card);
    
    //reset
    this->m_curPlayer->SetGiveUp(false);
    
    //emit
    this->m_gameloop->sPlayerAddCard(card, m_curStation);
}

void CJudge::CurPlayerChangeColor()
{
    this->ActChangeColor();
}

void CJudge::CurPlayerErrorPromt()
{
    this->m_gameloop->sErrorPromt();
}

bool CJudge::CurPlayerEmpty()
{
    return this->m_curPlayer->GetBox().Empty();
}

bool CJudge::CurPlayerAllowedOut()
{
    bool result = false;
    if (this->IsAllowOut(this->m_curPlayer->GetOutCard()))
    {
        result = true;
    }
    return result;
}

bool CJudge::AutoCurPlayerAllowedOut()
{
    bool result = false;
    if (this->IsAllowOut(this->m_curPlayer->GetBox()))
    {
        result = true;
    }
    return result;
}

bool CJudge::EndCardIsBlack()
{
    bool result = ((this->m_endCard->GetId() == ECI_Black) || (this->m_endCard->GetId() == ECI_BlackFour));
    return result;
}



void CJudge::Punish()
{
    //set cur player
    this->m_curPlayer = this->m_gameloop->GetPlayer(m_curStation);
    
    //do punish
    if (m_endCard->GetId() == ECI_AddTwo)
    {
        this->ActAddCard(2);
        this->ActStop();
    }
    else if (m_endCard->GetId() == ECI_Resverse)
    {
        this->ActReverse();
        this->ActStop();
    }
    else if (m_endCard->GetId() == ECI_Stop)
    {
        this->ActStop();
    }
    else if (m_endCard->GetId() == ECI_Black)
    {
        this->ActStop();
    }
    else if (m_endCard->GetId() == ECI_BlackFour)
    {
        this->ActAddCard(4);
        this->ActStop();
    }
}

void CJudge::SetCurPlayerChoiced(bool choiced)
{
    this->m_curPlayer->SetChoiced(choiced);
}

void CJudge::SetCurPlayerGiveup(bool giveup)
{
    this->m_curPlayer->SetGiveUp(giveup);
}

void CJudge::SetCurPlayerChangedColor(ECardColor color)
{
    this->m_curPlayer->SetChangeColor(color);
}

void CJudge::SetAllScores()
{
    this->m_gameloop->SetAllScores();
}


bool CJudge::IsAllowOut(CBox &box)
{
    //set cur player
    this->m_curPlayer = this->m_gameloop->GetPlayer(m_curStation);
    
    bool result = false;
    do
    {
        for (int i = 0; i < box.Size(); ++i)
        {
            CCardInfo card = box.At(i);
            if (this->IsSameColor(card) || this->IsSameId(card))
            {
                result = true;
                m_curPlayer->SetOutCard(card);
                
                break;
            }
        }
        
        for (int i = 0; i < box.Size(); ++i)
        {
            CCardInfo card = box.At(i);
            if (this->IsBlackCard(card))
            {
                result = true;
                m_curPlayer->SetOutCard(card);
                
                break;
            }
        }
        
    }while(false);
    
    return result;
}

bool CJudge::IsAllowOut(CCardInfo &outCard)
{
    bool result = (this->IsSameColor(outCard) || this->IsSameId(outCard) || (outCard.GetColor() == ECC_Black));
    return result;
}

int CJudge::getNext()
{
    int nextStation = m_curStation + m_toward;
    if (nextStation > 3)  //m_players.size() - 1
    {
        nextStation -= 4; //m_game->getPlayerSize()
    }
    else if (nextStation < 0)
    {
        nextStation += 4;
    }
    
    return nextStation;
}

bool CJudge::IsFunctionCard(const CCardInfo &outCard)
{
    return (outCard.GetAction() & 0xF);
}

bool CJudge::IsSameColor(const CCardInfo &outCard)
{
    bool result = false;
    if (outCard.GetColor() == m_endCard->GetColor())
    {
        result = true;
    }
    
    return result;
}

bool CJudge::IsSameId(const CCardInfo &outCard)
{
    bool result = false;
    if (outCard.GetId() == m_endCard->GetId())
    {
        result = true;
    }

    return result;
}

bool CJudge::IsBlackCard(const CCardInfo &outCard)
{
    bool result = false;
    if (outCard.GetColor() == ECC_Black)
    {
        result = true;
    }

    return result;
}

void CJudge::ActStop()
{
    this->ToNext();
}

void CJudge::ActReverse()
{
    if (this->m_toward == 1)
    {
        this->m_toward = -1;
    }
    else if (this->m_toward == -1)
    {
        this->m_toward = 1;
    }
}

void CJudge::ActAddCard(int num)
{
    for (int i = 0; i < num; ++i)
    {
        this->CurPlayerAddCard();
    }
}

void CJudge::ActChangeColor()
{
    ECardColor color;
    if (this->m_curStation == 0)
    {
       
    }
    else
    {
        this->m_curPlayer->SetChangeColor(m_curPlayer->GetMostColor());
    }
    
    color = this->m_curPlayer->GetChangeColor();
    
    this->m_endCard->SetColor(color);
    
    //emit
    this->m_gameloop->sEndCardChanged(color);
    this->m_gameloop->sBlackToColor(color);

}


