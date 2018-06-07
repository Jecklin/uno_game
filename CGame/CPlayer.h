#ifndef CPLAYER_H
#define CPLAYER_H

#include <string>
#include <list>
#include "CCardInfo.h"

class CPlayer
{
public:
    CPlayer();
    ~CPlayer();
    CPlayer(const CPlayer &other);
    CPlayer& operator =(const CPlayer &other);

public:
    typedef std::list<CCardInfo> CBox;

    //Score
    int             getPlayerScore() const;
    void            setPlayerScore(int score);

    //Name
    std::string     getPlayerName() const;
    void            setPlayerName(const std::string &name);
    
    //Box
    void            playerSubCard(const CCardInfo &card);
    void            playerAddCard(const CCardInfo &card);
    int             getBoxSize() const;
    ECardColor      getMaxColor() const;    
    
    //Judge
    bool            boxIsAllowOut(const CCardInfo &end_card);     //Other round
    bool            cardIsAllowOut(const CCardInfo &end_card);    //my round
    bool            isGiveUp() const;
    void            changeToGiveUp() const;
    
    //Out card
    CCardInfo       getOutCard() const;
    void            setOutCard(const CCardInfo &card);

private:
    int             m_score;
    std::string     m_name;
    CBox            m_box;
    bool            m_giveup;
    CCardInfo       m_outcard;
};
#endif // CPLAYER_H
