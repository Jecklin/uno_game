#pragma once
#include <QObject>
#include <QVector>
#include "CDeskBox.h"
#include "CCardInfoEnd.h"
#include "CPlayer.h"
#include "CStateMachine/CStateMachine.h"
#include "CDataBase.h"
#include "CJudge.h"

class CGameLoop: public QObject
{
    Q_OBJECT
    
public:
    CGameLoop();
    ~CGameLoop();
    
    void            InitGame(); 
    void            GameRound();
    int             GetPlayerScore(CPlayer *player);    //db    
    CJudge*         GetJudge();
    void            SetAllScores();
    CPlayer*        GetPlayer(int num);
    CCardInfoEnd&   GetEndCard();
      
    
signals:
    void            sPlayerAddCard(CCardInfo in_card, int current);
    void            sPlayerOutCard(CCardInfo out_card, int current);
    void            sEndCardChanged(CCardInfo end_card);
    void            sEndCardChanged(ECardColor color);
    void            sErrorPromt();         
    void            sGameOver();
    void            sBlackToColor(ECardColor color);
 
private:
    QVector<CPlayer*>       m_players;              
    CCardInfoEnd            m_endcard;              
    CDeskBox                m_openBox;             
    CDeskBox                m_closeBox;  
    CJudge                  *m_judge;
    CStateMachine           *m_stateMachine;       
    CDataBase               *m_db;                 

};

