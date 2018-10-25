#include "CBox.h"


CBox::CBox()
{
    
}

CBox::~CBox()
{
    
}

CBox::CBox(CBox &other)
{
    *this = other;
}

CBox &CBox::operator =(CBox &other)
{
    if (this != &other)
    {
        this->RemoveAll();
        int size = other.Size();
        for (int i = 0; i < size; ++i)
        {
            this->AddCard(other.At(i));
        }
    }

    return *this;
}

void CBox::AddCard(const CCardInfo &card)
{
    this->m_box.append(card);
}

void CBox::RemoveCard(const CCardInfo &card)
{
    int i = this->m_box.indexOf(card);
    if (i != -1)
    {
        this->m_box.removeAt(i);
    }
}

int CBox::Size() const
{
    return this->m_box.size();
}

bool CBox::Empty()
{
    return this->m_box.empty();
}

void CBox::RemoveAll()
{
    while(!m_box.empty())
    {
        m_box.erase(m_box.begin());
    }
}

int CBox::NumberOf(ECardColor color)
{
    int result = 0;
    QList<CCardInfo>::const_iterator iter = this->m_box.begin();
    while(iter != m_box.end())
    {
        if ((*iter).GetColor() == color)
        {
            result += 1;
        }
        ++iter;
    }
    return result;
}

CCardInfo CBox::At(int n)
{
    CCardInfo card = this->m_box.at(n);
    return card;
}
