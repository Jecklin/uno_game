#ifndef CCARDINFO_H
#define CCARDINFO_H

#include "datatypedefine.h"
#include <QString>

class CCardInfo
{
public:
    CCardInfo();
    virtual ~CCardInfo();

    CCardInfo(ECardColor color, ECardId id, ECardAction action);
    CCardInfo(const CCardInfo &other);

    CCardInfo& operator =   (const CCardInfo &other);
    bool       operator ==  (const CCardInfo &other) const;

public:
    ECardColor   getColor()  const;
    ECardId      getId()     const;
    ECardAction  getAction() const;
    
    bool         isFunctionCard();
    bool         isSameColor(const CCardInfo &card);
    bool         isSameId(const CCardInfo &card);
    bool         isSimilarColor(const CCardInfo &card);
    
    static QString      toString(ECardColor color);
    static QString      toString(ECardId id);
    static QString      toString(ECardAction action);
    
    static ECardColor   toColor(QString color);
    static ECardId      toID(QString id);
    static ECardAction  toAction(QString action);

protected:
    ECardColor   m_color;
    ECardId      m_id;
    ECardAction  m_action;
};

#endif // CCARDINFO_H
