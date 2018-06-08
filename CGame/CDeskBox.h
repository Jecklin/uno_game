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
    CCardInfo   getRandomCard();
    CCardInfo   getEndCard();
    void        initBox();
    void        randomBox();
    void        removeBox(CDeskBox &sou);
    bool        isEmpty();
    
private:
    std::list<CCardInfo> m_box;
};

#endif // CDESKBOX_H
