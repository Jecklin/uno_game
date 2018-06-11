#ifndef CWIDGET_H
#define CWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "CGame/CGameLoop.h"

namespace Ui {
class CWidget;
}

class CWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CWidget(QWidget *parent = nullptr);
    ~CWidget();

signals:
    void    choiced();
    
public slots:
    void    onGameStart();
    void    onPlayerInCard(CCardInfo in_card, int current);
    void    onPlayerOutCard(CCardInfo out_card, int current);
    void    onEndCardChanged(CCardInfo end_card);
    void    onNotAllowOut();
    void    onGameOver();
    
    void    onChoiceGiveUp();
    void    onChoiceOutCard();
    void    onChoiced();
    void    onErrorPromt();
    

private:
    static QString      dbColorToString(ECardColor color);
    static QString      dbIdToString(ECardId id);
    static QString      dbActionToString(ECardAction action);
    
    static ECardColor   dbColorToCard(QString color);
    static ECardId      dbIdToCard(QString id);
    static ECardAction  dbActionToCard(QString action);
    
    void                showPlayerScores();
    
private:
    Ui::CWidget         *m_mainWidget;
    CGameLoop           *m_gameLoop;
    bool                m_choice;
    int                 m_size[4];
};

#endif // CWIDGET_H
