#pragma once
#include <QString>

class CPlayerAttribute
{
public:
    CPlayerAttribute();
    ~CPlayerAttribute();
    
    void    setScore(int score);
    int     getScore();
    
    void    setID(int id);
    int     getID();
    
    void    setName(QString name);
    QString getName();
    
    void    setPassword(QString password);
    QString getPassword();
    
private:
    int      m_score;
    int      m_id;
    QString  m_name;
    QString  m_password;
};
