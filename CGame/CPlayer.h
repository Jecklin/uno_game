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
    int             getScore() const;
    void            setScore(int score);

    //Name
    QString         getName() const;
    void            setName(const QString &name);
    
    //Box
    void            removeCard(const CCardInfo &card);
    void            addCard(const CCardInfo &card);
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
