#include "CPlayerAttribute.h"

CPlayerAttribute::CPlayerAttribute()
    :m_score(0)
    ,m_id(0)
    ,m_name("")
    ,m_password("")
{
    
}

CPlayerAttribute::~CPlayerAttribute()
{
    
}

void CPlayerAttribute::setScore(int score)
{
    this->m_score = score;
}

int CPlayerAttribute::getScore()
{
    return this->m_score;
}

void CPlayerAttribute::setID(int id)
{
    this->m_id = id;
}

int CPlayerAttribute::getID()
{
    return this->m_id;
}

void CPlayerAttribute::setName(QString name)
{
    this->m_name = name;
}

QString CPlayerAttribute::getName()
{
    return this->m_name;
}

void CPlayerAttribute::setPassword(QString password)
{
    this->m_password = password;
}

QString CPlayerAttribute::getPassword()
{
    return this->m_password;
}
