#ifndef CDESKBOX_H
#define CDESKBOX_H

#include "CCardInfo.h"
#include <list>

class CDeskBox
{
public:
    CDeskBox();
    ~CDeskBox();
    
    void        addCard(const CCardInfo &card) const;
    void        subCard(const CCardInfo &card) const;
    CCardInfo   getRandomCard();
    CCardInfo   getEndCard();
    void        initBox() const;
    void        randomBox() const;
    void        removeBox(const CDeskBox &sou);
    bool        isEmpty();
    
private:
    std::list<CCardInfo> m_box;
};

#endif // CDESKBOX_H
