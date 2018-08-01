#ifndef CGAMERULE_H
#define CGAMERULE_H

class CGameLoop;

class CGameRule
{
public:
    CGameRule(CGameLoop *game);
    
public:
    int             getCurrent() const;         //获得当前位置
    void            toNext();                   //下一位置
    
    void            actNextAddCard(int num);
    void            actStop();
    void            actReverse();
    void            actChangeColor(); 
    
private:
    int             getNextLocation();
       
    
private:
    CGameLoop       *m_game;
    int             m_current;
    int             m_toward;
};

#endif // CGAMERULE_H
