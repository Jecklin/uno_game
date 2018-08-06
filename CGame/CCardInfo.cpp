#include "CCardInfo.h"
#include <QMap>


CCardInfo::CCardInfo()
    :m_color(ECC_Invalid)
    ,m_id(ECI_Invalid)
    ,m_action(ECA_Invalid)
{
    ;
}

CCardInfo::CCardInfo(ECardColor color, ECardId id, ECardAction action)
    :m_color(color)
    ,m_id(id)
    ,m_action(action)
{
    ;
}

CCardInfo::CCardInfo(const CCardInfo &other)
{
    *this = other;
}

CCardInfo::~CCardInfo()
{
    ;
}

CCardInfo &CCardInfo::operator=(const CCardInfo &other)
{
    if (this == &other)
    {
        ;
    }
    else
    {
        this->m_action = other.m_action;
        this->m_color = other.m_color;
        this->m_id = other.m_id;
    }
    return *this;
}

bool CCardInfo::operator ==(const CCardInfo &other) const
{
    bool issame = false;
    if ((this->m_action == other.m_action)
            &&(this->m_color == other.m_color)
            &&(this->m_id == other.m_id))
    {
        issame = true;
    }
    else
    {
        ;
    }
    return issame;
}

bool CCardInfo::isFunctionCard()
{
    return (this->getAction() & 0xF);
}

bool CCardInfo::isSameColor(const CCardInfo &card)
{
    bool is_same = false;
    if (this->m_color == card.getColor())
    {
        is_same = true;
    }
    else
    {
        ;
    }
    return is_same;
}

bool CCardInfo::isSameId(const CCardInfo &card)
{
    bool is_same = false;
    if (this->m_id == card.getId())
    {
        is_same = true;
    }
    else
    {
        ;
    }
    return is_same;
}

bool CCardInfo::isSimilarColor(const CCardInfo &card)
{
    bool is_similar = false;
    if (this->m_color & card.getColor())
    {
        is_similar = true;
    }
    else
    {
        ;
    }
    return is_similar;
}

QString CCardInfo::toString(ECardColor color)
{
    typedef QMap<ECardColor, QString>CardColor;
    static CardColor cardColors;
    if (cardColors.isEmpty())
    {
        cardColors.insert(ECardColor::ECC_Red, QString::fromUtf8("Red"));
        cardColors.insert(ECardColor::ECC_Yellow, QString::fromUtf8("Yellow"));
        cardColors.insert(ECardColor::ECC_Blue, QString::fromUtf8("Blue"));
        cardColors.insert(ECardColor::ECC_Green, QString::fromUtf8("Green"));
        cardColors.insert(ECardColor::ECC_Black, QString::fromUtf8("Black"));
    }
    return cardColors.value(color);
}

QString CCardInfo::toString(ECardId id)
{
    typedef QMap<ECardId,QString>CardId;
    static CardId cardIds;
    if (cardIds.isEmpty())
    {
        cardIds.insert(ECardId::ECI_Zero, QString::fromUtf8("0"));
        cardIds.insert(ECardId::ECI_One, QString::fromUtf8("1"));
        cardIds.insert(ECardId::ECI_Two, QString::fromUtf8("2"));
        cardIds.insert(ECardId::ECI_Three, QString::fromUtf8("3"));
        cardIds.insert(ECardId::ECI_Four, QString::fromUtf8("4"));
        cardIds.insert(ECardId::ECI_Five, QString::fromUtf8("5"));
        cardIds.insert(ECardId::ECI_Six, QString::fromUtf8("6"));
        cardIds.insert(ECardId::ECI_Seven, QString::fromUtf8("7"));
        cardIds.insert(ECardId::ECI_Eight, QString::fromUtf8("8"));
        cardIds.insert(ECardId::ECI_Nine, QString::fromUtf8("9"));
        cardIds.insert(ECardId::ECI_AddTwo, QString::fromUtf8("+2"));           //"AddTwo"
        cardIds.insert(ECardId::ECI_Resverse, QString::fromUtf8("Reverse"));
        cardIds.insert(ECardId::ECI_Stop, QString::fromUtf8("Stop"));
        cardIds.insert(ECardId::ECI_Black, QString::fromUtf8("Black"));
        cardIds.insert(ECardId::ECI_BlackFour, QString::fromUtf8("Black+4")); //"BlackFour"
    }
    return cardIds.value(id);
}

QString CCardInfo::toString(ECardAction action)
{
    typedef QMap<ECardAction,QString>CardAction;
    static CardAction cardActions;
    if (cardActions.isEmpty())
    {
        cardActions.insert(ECardAction::ECA_None, QString::fromUtf8("None"));                  
        cardActions.insert(ECardAction::ECA_Reverse, QString::fromUtf8("Reverse"));           
        cardActions.insert(ECardAction::ECA_Stop, QString::fromUtf8("Stop"));                 
        cardActions.insert(ECardAction::ECA_ChangeColor, QString::fromUtf8("Color"));         //"ChangeColor"
        cardActions.insert(ECardAction::ECA_ActionTwo, QString::fromUtf8("+2"));             //"ActionTwo"
        cardActions.insert(ECardAction::ECA_Black, QString::fromUtf8("Black"));
        cardActions.insert(ECardAction::ECA_BlackFour, QString::fromUtf8("Black+4"));          //"BlackFour"

    }
    return cardActions.value(action);
}

ECardColor CCardInfo::toColor(QString color)
{
    typedef QMap<QString, ECardColor>CardColor;
    static CardColor cardColors;
    if (cardColors.isEmpty())
    {
        cardColors.insert("Red", ECardColor::ECC_Red);
        cardColors.insert("Yellow", ECardColor::ECC_Yellow);
        cardColors.insert("Blue",ECardColor::ECC_Blue);
        cardColors.insert("Green",ECardColor::ECC_Green);
        cardColors.insert("Black",ECardColor::ECC_Black);
    }
    return cardColors.value(color);
}

ECardId CCardInfo::toID(QString id)
{
    typedef QMap<QString, ECardId>CardId;
    static CardId cardIds;
    if (cardIds.isEmpty())
    {
        cardIds.insert("0", ECardId::ECI_Zero);
        cardIds.insert("1", ECardId::ECI_One);
        cardIds.insert("2", ECardId::ECI_Two);
        cardIds.insert("3", ECardId::ECI_Three);
        cardIds.insert("4", ECardId::ECI_Four);
        cardIds.insert("5", ECardId::ECI_Five);
        cardIds.insert("6", ECardId::ECI_Six);
        cardIds.insert("7", ECardId::ECI_Seven);
        cardIds.insert("8", ECardId::ECI_Eight);
        cardIds.insert("9", ECardId::ECI_Nine);
        cardIds.insert("+2", ECardId::ECI_AddTwo);
        cardIds.insert("Reverse", ECardId::ECI_Resverse);
        cardIds.insert("Stop", ECardId::ECI_Stop);
        cardIds.insert("Black", ECardId::ECI_Black);
        cardIds.insert("Black+4", ECardId::ECI_BlackFour);        
        
    }

    return cardIds.value(id);
}

ECardAction CCardInfo::toAction(QString action)
{
    typedef QMap<QString,ECardAction>CardAction;
    static CardAction cardActions;
    if (cardActions.isEmpty())
    {
        cardActions.insert("None", ECardAction::ECA_None);
        cardActions.insert("Reverse", ECardAction::ECA_Reverse);
        cardActions.insert("Stop", ECardAction::ECA_Stop);
        cardActions.insert("Color", ECardAction::ECA_ChangeColor);
        cardActions.insert("+2", ECardAction::ECA_ActionTwo);
        cardActions.insert("Black", ECardAction::ECA_Black);
        cardActions.insert("Black+4", ECardAction::ECA_BlackFour);

    }
    return cardActions.value(action);
}



ECardColor CCardInfo::getColor() const
{
    return this->m_color;
}

ECardId CCardInfo::getId() const
{
    return this->m_id;
}

ECardAction CCardInfo::getAction() const
{
    return this->m_action;
}
