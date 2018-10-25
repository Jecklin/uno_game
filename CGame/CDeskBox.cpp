#include "CDeskBox.h"
#include "CCardInfo.h"
#include <QList>
#include <cstdlib>
#include <time.h>

CDeskBox::CDeskBox()
{
    
}

CDeskBox::~CDeskBox()
{
    
}




void CDeskBox::InitBox()
{
    //每回合重置牌库
    if (!this->m_box.empty())
    {
        this->RemoveAll();
    }
  
    //初始化 数字牌： 0-9,4种颜色各2张
    InitCardId(ECI_Zero);
    InitCardId(ECI_One);
    InitCardId(ECI_Two);
    InitCardId(ECI_Three);
    InitCardId(ECI_Four);
    InitCardId(ECI_Five);
    InitCardId(ECI_Six);
    InitCardId(ECI_Seven);
    InitCardId(ECI_Eight);
    InitCardId(ECI_Nine);
    
    //初始化 功能牌
    InitCardAct(ECI_AddTwo, ECA_ActionTwo);                //+2
    InitCardAct(ECI_Resverse, ECA_Reverse);                //反转
    InitCardAct(ECI_Stop, ECA_Stop);                       //停止
    
    InitCard(ECC_Black, ECI_Black, ECA_Black, 4);          //黑牌
    InitCard(ECC_Black, ECI_BlackFour, ECA_BlackFour, 4);  //+4黑牌

}

void CDeskBox::RandomBox()
{
    QList<CCardInfo>::iterator iter_move;
    QList<CCardInfo>::iterator iter_end = m_box.end();
    --iter_end;
    unsigned int                   sround = 0;

    srand((unsigned int)time(nullptr));
    for (unsigned int change = 0; change < 10000; ++change) 
    {
        //move iter_one
        sround = rand() % (this->m_box.size() - 1);
        iter_move = this->m_box.begin();
        for (unsigned int i = 0; i < sround; ++i )
        {
            ++iter_move;
        }
        
        //change
        CCardInfo card = m_box.back();
        *iter_end = *iter_move;
        *iter_move = card;

    }
}

CCardInfo& CDeskBox::GetTopCard()
{
    return this->m_box.back();
}

void CDeskBox::RemoveBox(CDeskBox *box)
{
    CCardInfo card = box->GetTopCard();
    this->AddCard(card);
    box->RemoveCard(card);
}

void CDeskBox::InitCard(ECardColor color, ECardId id, ECardAction action, int times)
{
    CCardInfo card(color, id, action);
    
    for (int i = 0; i < times; ++i)
    {
        this->m_box.push_back(card);
    }
    
}

void CDeskBox::InitCardId(ECardId id)
{
    InitCard(ECC_Red, id, ECA_None);
    InitCard(ECC_Yellow, id, ECA_None);
    InitCard(ECC_Green, id, ECA_None);
    InitCard(ECC_Blue, id, ECA_None);
}

void CDeskBox::InitCardAct(ECardId id, ECardAction action)
{
    InitCard(ECC_Red, id, action);
    InitCard(ECC_Yellow, id, action);
    InitCard(ECC_Green, id, action);
    InitCard(ECC_Blue, id, action);
}
