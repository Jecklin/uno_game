#ifndef CWIDGET_H
#define CWIDGET_H

#include <QWidget>
#include "CGameLoop.h"


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
    void choiced();

    
public slots:
    void onPlayerChange(int current); 
    void onEndCardChange();
    void onGiveUpChoice();
    void onOutCardChoice();
    void onError();
    void onGameOver();
    void onGameStart();
    void onChoice();
    void onCurPlayerFlash();
    void onCurPlayerFiashOver();

private:
    static QString dbColor(ECardColor color);
    static QString dbId(ECardId id);
    
    void upDateBrowser(int current,const QString &texts);
    void upDateLabelNum(int current,const QString &num);
    
private:
    Ui::CWidget         *m_mainWidget;
    CGameLoop           *m_gameLoop;
    int                 m_choice;
};

#endif // CWIDGET_H
