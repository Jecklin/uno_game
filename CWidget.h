#ifndef CWIDGET_H
#define CWIDGET_H

#include <QWidget>
#include "CGameLoop.h"

namespace Ui {
class CWidget;
class CTopList;
}

class CWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CWidget(QWidget *parent = nullptr);
    ~CWidget();
    
public slots:
    void onPlayerChange(); 
    void onEndCardChange();
    void onScoreChange();
    void onFirstRound();
    void onMyRound();
    void onGiveUp();
    void onOutCard();
    void onError();
    void onGameOver();
    void onGameStart();

private:
    static QString dbColor(ECardColor color);
    static QString dbId(ECardId id);

    void showListWidgets();
    
private:
    Ui::CWidget         *m_mainWidget;
    Ui::CTopList        *m_topListWidget;
    CGameLoop           *m_gameLoop;
    int                 m_choice;
};

#endif // CWIDGET_H
