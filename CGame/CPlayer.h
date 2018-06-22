#ifndef CPLAYER_H
#define CPLAYER_H

#include <QString>
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
    QString         getPlayerName() const;
    void            setPlayerName(const QString &name);
    
    //Box
    void            playerSubCard(const CCardInfo &card);
    void            playerAddCard(const CCardInfo &card);
    int             getBoxSize() const;
    ECardColor      getChangeColor() const;
    void            clearBox();
    
    //Judge
    bool            boxIsAllowOut(const CCardInfo &end_card);     //Other round
    bool            cardIsAllowOut(const CCardInfo &end_card);    //my round
    bool            isGiveUp() const;
    void            changeToGiveUp();
    
    //Out card
    CCardInfo       getOutCard() const;
    void            setOutCard(const CCardInfo &card);

private:
    int             m_score;
    QString         m_name;
    CBox            m_box;
    bool            m_giveup;
    CCardInfo       m_outcard;
};
#endif // CPLAYER_H
