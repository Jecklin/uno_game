#pragma once

#include "datatypedefine.h"
#include "CBox.h"

class CCardInfo;

class CDeskBox:public CBox
{
public:
    CDeskBox();
    ~CDeskBox();
    void        InitBox();
    void        RandomBox();
    CCardInfo&  GetTopCard();
    void        RemoveBox(CDeskBox *box);


private:
    void        InitCard(ECardColor color, ECardId id, ECardAction action, int times = 2);
    void        InitCardId(ECardId id);
    void        InitCardAct(ECardId id,  ECardAction action);
    

};

