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

CCardInfo CDeskBox::getRandomCard()
{
    std::list<CCardInfo>::iterator iter;
    unsigned int                   sround = 0;
    CCardInfo                      card_index;

    do
    {
        //Get srand card
        iter = this->m_box.begin();
        srand((unsigned int)time(nullptr));
        sround = rand() % (this->m_box.size() - 1);
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
    
    return card_index;
}

CCardInfo CDeskBox::getEndCard()
{
    std::list<CCardInfo>::iterator iter = this->m_box.end();
    --iter;
    CCardInfo card;
    card = *iter;
    return card;
}

void CDeskBox::initBox()
{
    if (this->m_box.empty())
    {
        ;
    }
    else
    {
        this->m_box.clear();
    }
  
    //初始化数字牌
    for (int index_eci = ECI_Zero; index_eci != ECI_Nine + 1; ++index_eci)      //id
    {
        CCardInfo index_rcard(ECC_Red, ECardId(index_eci), ECA_None);
        this->m_box.push_back(index_rcard);
        this->m_box.push_back(index_rcard);

        CCardInfo index_ycard(ECC_Yellow, ECardId(index_eci), ECA_None);
        this->m_box.push_back(index_ycard);
        this->m_box.push_back(index_ycard);

        CCardInfo index_gcard(ECC_Green, ECardId(index_eci), ECA_None);
        this->m_box.push_back(index_gcard);
        this->m_box.push_back(index_gcard);

        CCardInfo index_bcard(ECC_Blue, ECardId(index_eci), ECA_None);
        this->m_box.push_back(index_bcard);
        this->m_box.push_back(index_bcard);

    }

    //初始化 +2 功能牌
    CCardInfo index_atrcard(ECC_Red, ECI_AddTwo, ECA_ActionTwo);
    this->m_box.push_back(index_atrcard);
    this->m_box.push_back(index_atrcard);

    CCardInfo index_atycard(ECC_Yellow, ECI_AddTwo, ECA_ActionTwo);
    this->m_box.push_back(index_atycard);
    this->m_box.push_back(index_atycard);

    CCardInfo index_atgcard(ECC_Green, ECI_AddTwo, ECA_ActionTwo);
    this->m_box.push_back(index_atgcard);
    this->m_box.push_back(index_atgcard);

    CCardInfo index_atbcard(ECC_Blue, ECI_AddTwo, ECA_ActionTwo);
    this->m_box.push_back(index_atbcard);
    this->m_box.push_back(index_atbcard);

    //初始化 反转 功能牌
    CCardInfo index_rrcard(ECC_Red, ECI_Resverse, ECA_Reverse);
    this->m_box.push_back(index_rrcard);
    this->m_box.push_back(index_rrcard);

    CCardInfo index_rycard(ECC_Yellow, ECI_Resverse, ECA_Reverse);
    this->m_box.push_back(index_rycard);
    this->m_box.push_back(index_rycard);

    CCardInfo index_rgcard(ECC_Green, ECI_Resverse, ECA_Reverse);
    this->m_box.push_back(index_rgcard);
    this->m_box.push_back(index_rgcard);

    CCardInfo index_rbcard(ECC_Blue, ECI_Resverse, ECA_Reverse);
    this->m_box.push_back(index_rbcard);
    this->m_box.push_back(index_rbcard);

    //初始化 停止 功能牌
    CCardInfo index_srcard(ECC_Red, ECI_Stop, ECA_Stop);
    this->m_box.push_back(index_srcard);
    this->m_box.push_back(index_srcard);

    CCardInfo index_sycard(ECC_Yellow, ECI_Stop, ECA_Stop);
    this->m_box.push_back(index_sycard);
    this->m_box.push_back(index_sycard);

    CCardInfo index_sgcard(ECC_Green, ECI_Stop, ECA_Stop);
    this->m_box.push_back(index_sgcard);
    this->m_box.push_back(index_sgcard);

    CCardInfo index_sbcard(ECC_Blue, ECI_Stop, ECA_Stop);
    this->m_box.push_back(index_sbcard);
    this->m_box.push_back(index_sbcard);

    //初始化 黑牌 高级牌
    CCardInfo index_bcard(ECC_Black, ECI_Black, ECA_Black);
    this->m_box.push_back(index_bcard);
    this->m_box.push_back(index_bcard);
    this->m_box.push_back(index_bcard);
    this->m_box.push_back(index_bcard);

    //初始化 +4黑牌 高级牌
    CCardInfo index_bfcard(ECC_Black, ECI_BlackFour, ECA_BlackFour);
    this->m_box.push_back(index_bfcard);
    this->m_box.push_back(index_bfcard);
    this->m_box.push_back(index_bfcard);
    this->m_box.push_back(index_bfcard);
}

void CDeskBox::randomBox()
{
    std::list<CCardInfo>::iterator iter_one;
    std::list<CCardInfo>::iterator iter_two;
    CCardInfo                      card_index;
    unsigned int                   sround = 0;

    srand((unsigned int)time(nullptr));
    for (unsigned int change = 0; change < 1000; ++change)  //change < this->m_box.size()
    {
        //move iter_one
        sround = rand() % (this->m_box.size() - 1);
        iter_one = this->m_box.begin();
        for (unsigned int i = 0; i < sround; ++i )
        {
            ++iter_one;
        }

        //move iter_two
        sround = rand() % (this->m_box.size() - 1);
        iter_two = this->m_box.end();
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

void CDeskBox::removeBox(CDeskBox &sou)
{
    CCardInfo   card;
    do
    {
        card = sou.getEndCard();
        this->m_box.push_back(card);
        sou.subCard(card);
  

    }while(!sou.isEmpty());
    
    this->randomBox();
}

bool CDeskBox::isEmpty()
{
    return this->m_box.empty();
}
