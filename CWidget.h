#ifndef CWIDGET_H
#define CWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

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
    
    void    unInitButton();

signals:
    void    choiced();
    
public slots:
    void    onGameStart();
    void    onPlayerAddCard(CCardInfo in_card, int current);
    void    onPlayerOutCard(CCardInfo out_card, int current);
    void    onEndCardChanged(CCardInfo end_card);
    void    onNotAllowOut();
    void    onGameOver();
    
    void    onChoiceGiveUp();
    void    onChoiceOutCard();
    void    onChoiced();
    void    onErrorPromt();
    void    onChangeColor(ECardColor color);
    void    onComboxChoice(int num = -1);
    

private:
    void                setBackGround();
    static QString      dbColorToString(ECardColor color);
    static QString      dbIdToString(ECardId id);
    static QString      dbActionToString(ECardAction action);
    
    static ECardColor   dbColorToCard(QString color);
    static ECardId      dbIdToCard(QString id);
    static ECardAction  dbActionToCard(QString action);
    
    void                showPlayerScores();
    void                setButtonIcon(QPushButton *button, CCardInfo card, bool hide = true, bool rotat = false);
    void                addButtonToLayout(QLayout *layout, CCardInfo card, QSize size, int current = 0, bool hide = true, bool click = false);
    void                subButtonAtLayout(QLayout *layout, CCardInfo card);
    void                setBoxSizes(QLabel *label,int current);
    QString             getCardDir(const CCardInfo &card);
    
private:
    static QSize        s_button_low;
    static QSize        s_button_top;
    static QSize        s_button_left;
    static QSize        s_button_mid;
    static QSize        s_button_outCard;
    
private:
    Ui::CWidget         *m_mainWidget;
    CGameLoop           *m_gameLoop;
    bool                m_color_choice;         //选择改变的颜色

};

#endif // CWIDGET_H
