#ifndef CCARDINFO_H
#define CCARDINFO_H


#include "datatypedefine.h"

class CCardInfo
{
public:
    CCardInfo();
    CCardInfo(ECardColor color, ECardId id, ECardAction action);
    ~CCardInfo();

    CCardInfo(const CCardInfo &other);
    CCardInfo& operator=(const CCardInfo &other);
    bool operator ==(const CCardInfo &other);

public:
    ECardColor GetColor() const;
    ECardId GetId() const;
    ECardAction GetAction() const;

    void SetColor(ECardColor color);
    void SetId(ECardId id);
    void SetAction(ECardAction action);

public:
    bool IsSimilar(const CCardInfo &cardinfo);

protected:
    ECardColor   m_color;
    ECardId      m_id;
    ECardAction  m_action;
};
#endif // CCARDINFO_H
