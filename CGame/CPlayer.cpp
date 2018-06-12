#include "CPlayer.h"
#include <iostream>

CPlayer::CPlayer()
    :m_score()
    ,m_name()
    ,m_box()
    ,m_giveup(false)
    ,m_outcard()
{
    ;
}

CPlayer::~CPlayer()
{
    ;
}

CPlayer::CPlayer(const CPlayer &other)
    :m_score()
    ,m_name()
    ,m_box()
    ,m_giveup(false)
{
    *this = other;
}

CPlayer &CPlayer::operator =(const CPlayer &other)
{
    if (this == &other)
    {
        ;
    }
    else
    {
        this->m_score = other.m_score;
        this->m_name = other.m_name;
        this->m_box = other.m_box;
    }
    return *this;
}

//Score
int CPlayer::getPlayerScore() const
{
    return this->m_score;
}

void CPlayer::setPlayerScore(int score)
{
    this->m_score += score;
}


//Name
std::string CPlayer::getPlayerName() const
{
    return this->m_name;
}

void CPlayer::setPlayerName(const std::string &name)
{
    this->m_name = name;
}

//Box
void CPlayer::playerSubCard(const CCardInfo &card)
{
    std::list<CCardInfo>::iterator iter;
    CCardInfo card_index;
    for (iter = this->m_box.begin(); iter != this->m_box.end(); ++iter)
    {
        card_index = *iter;
        if (card == card_index)
        {
            this->m_outcard = card_index;
            this->m_box.erase(iter);
            break;
        }
        else
        {
            ;
        }
    }

}

void CPlayer::playerAddCard(const CCardInfo &card)
{
    this->m_box.push_back(card);
}

int CPlayer::getBoxSize() const
{
    return this->m_box.size();
}

ECardColor CPlayer::getChangeColor() const
{
    std::list<CCardInfo>::const_iterator    iter;
    CCardInfo                               index_card;
    ECardColor                              return_color;

    int         sum_red    = 0;
    int         sum_yellow = 0;
    int         sum_blue   = 0;
    int         sum_green  = 0;

    for (iter = this->m_box.begin(); iter != this->m_box.end(); ++iter)
    {
        index_card = *iter;
        if (index_card.getColor() == ECC_Red)
        {
            ++sum_red;
        }
        else if (index_card.getColor() == ECC_Yellow)
        {
            ++sum_yellow;
        }
        else if (index_card.getColor() == ECC_Blue)
        {
            ++sum_blue;
        }
        else if (index_card.getColor() == ECC_Green)
        {
            ++sum_green;
        }
    }

    int max_color_name = 0;
    int max_sum = sum_red;
    int color[4] = {sum_red, sum_yellow, sum_blue, sum_green};

    for (int index = 1; index < 4; ++index)
    {
        if (color[index] > max_sum)
        {
            max_color_name = index;
            max_sum = color[index];
        }
    }

    if (max_color_name == 0)
    {
        return_color = ECC_Red;
    }
    else if(max_color_name == 1)
    {
        return_color = ECC_Yellow;
    }
    else if (max_color_name == 2)
    {
        return_color = ECC_Blue;
    }
    else if (max_color_name == 3)
    {
        return_color = ECC_Green;
    }
    else
    {
        ;
    }
    return return_color;
}

void CPlayer::clearBox()
{
    if (this->m_box.empty())
    {
        ;
    }
    else
    {
        this->m_box.clear();  
    }
    
}

bool CPlayer::boxIsAllowOut(const CCardInfo &end_card)
{
    bool                            is_allow = false;
    CCardInfo                       card_index;
    std::list<CCardInfo>::iterator  iter;

    //end card is black
    if ((end_card.getId() == ECI_Black) || (end_card.getId() == ECI_BlackFour))
    {
        for (iter = this->m_box.begin(); iter != this->m_box.end(); ++iter)
        {
            card_index = *iter;
            if (card_index.isSameColor(end_card))
            {
                is_allow = true;
                this->m_outcard = card_index;
            }
            else
            {
                ;
            }

        }
    }

    //end card is normal
    else
    {
        for (iter = this->m_box.begin(); iter != this->m_box.end(); ++iter)
        {
            card_index = *iter;
            if ((card_index.isSameId(end_card)) || (card_index.isSimilarColor(end_card)))
            {
                is_allow = true;
                this->m_outcard = card_index;
            }
            else
            {
                ;
            }
        }
    }
    return is_allow;
}

bool CPlayer::cardIsAllowOut(const CCardInfo &end_card)
{
    bool is_allow = false;
    //end card is black
    if ((end_card.getId() == ECI_Black) || (end_card.getId() == ECI_BlackFour))
    {
        if (this->m_outcard.isSimilarColor(end_card))
        {
            is_allow = true;
        }
        else
        {
            ;
        }
    }

    //end card is normal
    else
    {
        if ((this->m_outcard.isSameId(end_card)) || (this->m_outcard.isSimilarColor(end_card)))
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


bool CPlayer::isGiveUp() const
{
    return this->m_giveup;
}

void CPlayer::changeToGiveUp()
{
    this->m_giveup = true;
}

CCardInfo CPlayer::getOutCard() const
{
    return this->m_outcard;
}

void CPlayer::setOutCard(const CCardInfo &card)
{
    this->m_outcard = card;
}


//CCardInfo CPlayer::getSimilarCard(const CCardInfo &card)
//{
//    CCardInfo card_index;
//    CCardInfo card_return;
//    std::list<CCardInfo>::iterator iter;

//    //end card is black
//    if ((card.getId() == ECI_Black) || (card.getId() == ECI_BlackFour))
//    {
//        for (iter = this->m_box.begin(); iter != this->m_box.end(); ++iter)
//        {
//            card_index = *iter;
//            if (card_index.getColor() & card.getColor())
//            {
//                card_return = card_index;
//            }
//            else
//            {
//                ;
//            }

//        }
//    }

//    //end card is normal
//    else
//    {
//        for (iter = this->m_box.begin(); iter != this->m_box.end(); ++iter)
//        {
//            card_index = *iter;
//            if ((card_index.getId() == card.getId()) || (card_index.getColor() & card.getColor()))
//            {
//                card_return = card_index;
//            }
//            else
//            {
//                ;
//            }
//        }
//    }
//    return card_return;

//}





//void CPlayer::printPlayer()
//{
//    std::list<CCardInfo>::iterator iter;
//    CCardInfo card;
//    int i = 0;

//    std::cout << "Name: " << this->playerGetName() << " ";
//    std::cout << "Score: " << this->playerGetScore() << " ";
//    std::cout << "Box: " << "(" << this->getBoxSize() << "): " << std::endl;
//    for (iter = this->m_box.begin(); iter != this->m_box.end(); ++iter)
//    {
//        std::cout << i << " : ";
//        card = *iter;
//        this->printCard(card);
//        ++i;
//    }
//    std::cout << std::endl << std::endl;

//}

//void CPlayer::printCard(const CCardInfo &card)
//{
//    if (card.getColor() == ECC_Red)
//    {
//        std::cout << "R";
//    }
//    else if (card.getColor() == ECC_Yellow)
//    {
//        std::cout << "Y";
//    }
//    else if (card.getColor() == ECC_Blue)
//    {
//        std::cout << "B";
//    }
//    else if (card.getColor() == ECC_Green)
//    {
//        std::cout << "G";
//    }
//    else if (card.getColor() == ECC_Black)
//    {
//        std::cout << "BLACK";
//    }


//    std::cout << " ";


//    if (card.getId() == ECI_Zero)
//    {
//        std::cout << "0";
//    }
//    else if (card.getId() == ECI_One)
//    {
//        std::cout << "1";
//    }
//    else if (card.getId() == ECI_Two)
//    {
//        std::cout << "2";
//    }
//    else if (card.getId() == ECI_Three)
//    {
//        std::cout << "3";
//    }
//    else if (card.getId() == ECI_Four)
//    {
//        std::cout << "4";
//    }
//    else if (card.getId() == ECI_Five)
//    {
//        std::cout << "5";
//    }
//    else if (card.getId() == ECI_Six)
//    {
//        std::cout << "6";
//    }
//    else if (card.getId() == ECI_Seven)
//    {
//        std::cout << "7";
//    }
//    else if (card.getId() == ECI_Eight)
//    {
//        std::cout << "8";
//    }
//    else if (card.getId() == ECI_Nine)
//    {
//        std::cout << "9";
//    }
//    else if (card.getId() == ECI_AddTwo)
//    {
//        std::cout << "+2";
//    }
//    else if (card.getId() == ECI_Resverse)
//    {
//        std::cout << "reverse";
//    }
//    else if (card.getId() == ECI_Stop)
//    {
//        std::cout << "stop";
//    }
//    else if (card.getId() == ECI_Black)
//    {
//        std::cout << "black";
//    }
//    else if (card.getId() == ECI_BlackFour)
//    {
//        std::cout << "black+4";
//    }
//    else
//    {
//        ;
//    }

//    std::cout << "   ";
//}

//std::string CPlayer::getPlayerInfo()
//{
//    std::string playerInfo;
//    std::list<CCardInfo>::iterator iter;
//    CCardInfo card;
//    int i = 0;
    
//    playerInfo = "Name: " + this->playerGetName() + " "
//               + "Score: " + this->playerGetScore() + " "
//               + "Box: " + "(" + this->getBoxSize() + "): \n";


//    for (iter = this->m_box.begin(); iter != this->m_box.end(); ++iter)
//    {
//        std::cout << i << " : ";
//        card = *iter;
//        this->printCard(card);
//        ++i;
//    }
//    std::cout << std::endl << std::endl;
//}

//std::string CPlayer::getCardInfo(const CCardInfo &card)
//{
//    std::string cardInfo;
//    if (card.getColor() == ECC_Red)
//    {
//        cardInfo = "R";
//    }
//    else if (card.getColor() == ECC_Yellow)
//    {
//        cardInfo = "Y";
//    }
//    else if (card.getColor() == ECC_Blue)
//    {
//        cardInfo = "B";
//    }
//    else if (card.getColor() == ECC_Green)
//    {
//        cardInfo = "G";
//    }
//    else if (card.getColor() == ECC_Black)
//    {
//        cardInfo = "BLACK";
//    }

//    cardInfo += " ";

//    if (card.getId() == ECI_Zero)
//    {
//        cardInfo +=  "0";
//    }
//    else if (card.getId() == ECI_One)
//    {
//        cardInfo +=  "1";
//    }
//    else if (card.getId() == ECI_Two)
//    {
//        cardInfo +=  "2";
//    }
//    else if (card.getId() == ECI_Three)
//    {
//        cardInfo +=  "3";
//    }
//    else if (card.getId() == ECI_Four)
//    {
//        cardInfo +=  "4";
//    }
//    else if (card.getId() == ECI_Five)
//    {
//        cardInfo +=  "5";
//    }
//    else if (card.getId() == ECI_Six)
//    {
//        cardInfo +=  "6";
//    }
//    else if (card.getId() == ECI_Seven)
//    {
//        cardInfo +=  "7";
//    }
//    else if (card.getId() == ECI_Eight)
//    {
//        cardInfo +=  "8";
//    }
//    else if (card.getId() == ECI_Nine)
//    {
//        cardInfo +=  "9";
//    }
//    else if (card.getId() == ECI_AddTwo)
//    {
//        cardInfo +=  "+2";
//    }
//    else if (card.getId() == ECI_Resverse)
//    {
//        cardInfo +=  "reverse";
//    }
//    else if (card.getId() == ECI_Stop)
//    {
//        cardInfo +=  "stop";
//    }
//    else if (card.getId() == ECI_Black)
//    {
//        cardInfo +=  "black";
//    }
//    else if (card.getId() == ECI_BlackFour)
//    {
//        cardInfo +=  "black+4";
//    }
//    else
//    {
//        ;
//    }

//    cardInfo +=   "   ";
//}
