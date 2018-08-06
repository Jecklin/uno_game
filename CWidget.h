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

signals:
    void            choiced();
    
public slots:
    void            onStart();
    void            onAddCard(CCardInfo in_card, int current);
    void            onOutCard(CCardInfo out_card, int current);
    void            onEndCardChanged(CCardInfo end_card);
    void            onNotAllowOut();
    void            onOver();
    
    void            onCGiveUp();
    void            onCOutCard();
    void            onChoiced();
    void            onError();
    void            onChangeColor(ECardColor color);
    void            onCombox(int num = -1);
    

private:
    void            initUI();
    void            unInitUI();
    void            setBackGround();
    void            setScoreLabels();
    void            setSizeLabel(QLabel *label,int current);
    
    void            setIcon(QPushButton *button, CCardInfo card, bool hide = true, bool rotat = false);
    void            addButton(QLayout *layout, CCardInfo card, QSize size, int current = 0, bool hide = true, bool click = false);
    void            subButton(QLayout *layout, CCardInfo card);

    QString         getDir(const CCardInfo &card);    
    void            unInitButtons();
    void            unInitButton(QLayout *layout);
    
private:
    static QSize    s_button_low;
    static QSize    s_button_top;
    static QSize    s_button_left;
    static QSize    s_button_mid;
    static QSize    s_button_outCard;
    
private:
    Ui::CWidget     *m_mainWidget;
    CGameLoop       *m_gameLoop;
    bool            m_color_choice;         //选择改变的颜色

};

#endif // CWIDGET_H
