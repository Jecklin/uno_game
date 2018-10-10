#include "CDeskBox.h"
#include <cstdlib>
#include <time.h>

CDeskBox::CDeskBox()
    :m_box()
{
    
}

CDeskBox::~CDeskBox()
{
    
}

void CDeskBox::addCard(const CCardInfo &card)
{
    this->m_box.push_back(card);
}

void CDeskBox::subCard(const CCardInfo &card)
{
    std::list<CCardInfo>::iterator iter;
    CCardInfo card_index;
    for (iter = this->m_box.begin(); iter != this->m_box.end(); ++iter)
    {
        card_index = *iter;
        if (card == card_index)
        {
            this->m_box.erase(iter);
            break;
        }
        else
        {
            ;
        }
    }
}

void CDeskBox::popCard()
{
    m_box.pop_back();
}

CCardInfo& CDeskBox::backCard()
{
    return m_box.back();
}


void CDeskBox::initBox()
{
    //每回合重置牌库
    if (!this->m_box.empty())
    {
        this->clearBox();
    }
  
    //初始化 数字牌： 0-9,4种颜色各2张
    cardToBoxId(ECI_Zero);
    cardToBoxId(ECI_One);
    cardToBoxId(ECI_Two);
    cardToBoxId(ECI_Three);
    cardToBoxId(ECI_Four);
    cardToBoxId(ECI_Five);
    cardToBoxId(ECI_Six);
    cardToBoxId(ECI_Seven);
    cardToBoxId(ECI_Eight);
    cardToBoxId(ECI_Nine);
    
    //初始化 功能牌
    cardToBoxAct(ECI_AddTwo, ECA_ActionTwo);                //+2
    cardToBoxAct(ECI_Resverse, ECA_Reverse);                //反转
    cardToBoxAct(ECI_Stop, ECA_Stop);                       //停止
    
    cardToBox(ECC_Black, ECI_Black, ECA_Black, 4);          //黑牌
    cardToBox(ECC_Black, ECI_BlackFour, ECA_BlackFour, 4);  //+4黑牌

}

void CDeskBox::randomBox()
{
    std::list<CCardInfo>::iterator iter_move;
    std::list<CCardInfo>::iterator iter_end = m_box.end();
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

void CDeskBox::removeBox(CDeskBox &sou)
{

    while(!sou.empty())
    {
        m_box.push_back(sou.backCard());
        sou.popCard();
    }
    
    this->randomBox();
}

bool CDeskBox::empty()
{
    return this->m_box.empty();
}

void CDeskBox::clearBox()
{
    if (!this->m_box.empty())
    {
        m_box.erase(m_box.begin());
    }
    
}

void CDeskBox::cardToBox(ECardColor color, ECardId id, ECardAction action, int times)
{
    CCardInfo card(color, id, action);
    
    for (int i = 0; i < times; ++i)
    {
        this->m_box.push_back(card);
    }
    
}

void CDeskBox::cardToBoxId(ECardId id)
{
    cardToBox(ECC_Red, id, ECA_None);
    cardToBox(ECC_Yellow, id, ECA_None);
    cardToBox(ECC_Green, id, ECA_None);
    cardToBox(ECC_Blue, id, ECA_None);
}

void CDeskBox::cardToBoxAct(ECardId id, ECardAction action)
{
    cardToBox(ECC_Red, id, action);
    cardToBox(ECC_Yellow, id, action);
    cardToBox(ECC_Green, id, action);
    cardToBox(ECC_Blue, id, action);
}
