#pragma once

#include <QString>
#include <list>
#include "datatypedefine.h"
#include "CPlayerAttribute.h"
#include "CBox.h"

class CCardInfo;



class CPlayer
{
public:
    CPlayer();
    CPlayer(QString name);
    ~CPlayer();
    CPlayer(CPlayer &other);
    CPlayer& operator =(CPlayer &other);

public:
    CPlayerAttribute    GetAttribute() const; 
    void                SetAttribute(const CPlayerAttribute &attribute);
    
    CBox&               GetBox();
    void                SetBox(CBox &box);
    
    bool                IsGiveUp();
    void                SetGiveUp(bool giveup);
    
    bool                IsChoiced();
    void                SetChoiced(bool choice);
    
    void                AddCard(const CCardInfo &card);
    void                RemoveCard(const CCardInfo &card);
    
    CCardInfo&          GetOutCard();
    void                SetOutCard(const CCardInfo &card);

    ECardColor          GetMostColor();
    void                SetChangeColor(ECardColor color);
    ECardColor          GetChangeColor();
    
    



private:
    CPlayerAttribute    m_attribute;
    CBox                m_box;
    bool                m_giveup;
    bool                m_choiced;
    CCardInfo           m_outcard;
    ECardColor          m_changeColor;
};
