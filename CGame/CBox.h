#pragma once
#include <QList>
#include "CCardInfo.h"


class CBox
{
public:
    CBox();
    virtual ~CBox();
    CBox(CBox &other);
    CBox& operator = (CBox &other);
    
    virtual void        AddCard(const CCardInfo &card);
    virtual void        RemoveCard(const CCardInfo &card);
    virtual int         Size() const;
    virtual bool        Empty();
    virtual void        RemoveAll();
    virtual int         NumberOf(ECardColor color);
    virtual CCardInfo   At(int n); 
    
protected:
    QList<CCardInfo> m_box;
};

