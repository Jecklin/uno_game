#ifndef CDESKBOX_H
#define CDESKBOX_H

#include "CCardInfo.h"
#include <list>

class CDeskBox
{
public:
    CDeskBox();
    ~CDeskBox();
    
    void        addCard(const CCardInfo &card);
    void        subCard(const CCardInfo &card);
    void        popCard();
    CCardInfo&  backCard();
    
//    CCardInfo   getRandomCard();
//    CCardInfo   getEndCard();
    void        initBox();
    void        randomBox();
    void        removeBox(CDeskBox &sou);
    bool        empty();
    void        clearBox();
    
private:
    void        cardToBox(ECardColor color, ECardId id, ECardAction action, int times = 2);
    void        cardToBoxId(ECardId id);
    void        cardToBoxAct(ECardId id,  ECardAction action);
    
private:
    std::list<CCardInfo> m_box;
};

#endif // CDESKBOX_H
