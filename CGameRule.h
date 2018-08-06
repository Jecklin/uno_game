#ifndef CGAMERULE_H
#define CGAMERULE_H

class CGameLoop;

class CGameRule
{
public:
    CGameRule(CGameLoop *game);
    
public:
    int             current() const;         //获得当前位置
    int             next();
    
    void            sroundCurrent();            //随机首个玩家
    void            toNext();                   //下一位置
    
    void            actNextAddCard(int num);
    void            actStop();
    void            actReverse();
    void            actChoiceColor(); 

       
    
private:
    CGameLoop       *m_game;
    int             m_current;
    int             m_toward;
};

#endif // CGAMERULE_H
