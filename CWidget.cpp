#include "ui_CWidget.h"
#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QLayout>

#include "CWidget.h"
#include "CGameOverDialog.h"
#include "CBeginDialog.h"
#include "CGame/CCardTranslator.h"

//设置牌固定大小
QSize CWidget::s_button_low(100, 130);
QSize CWidget::s_button_top(50, 150);
QSize CWidget::s_button_left(150, 50);
QSize CWidget::s_button_mid(100, 130);
QSize CWidget::s_button_outCard(80, 80);

CWidget::CWidget(QWidget *parent)
    :QWidget(parent)
    ,m_mainWidget(nullptr)
    ,m_gameLoop(nullptr)
    ,m_color_choice(false)
{    
    this->m_mainWidget = new Ui::CWidget(); 
    this->m_mainWidget->setupUi(this);
   
    this->m_gameLoop = new CGameLoop;
    
    //start / end
    connect(m_mainWidget->startButton,SIGNAL(clicked(bool)),this,SLOT(onStart()));   
    connect(m_gameLoop,SIGNAL(sGameOver()),this,SLOT(onOver()));
    
    //Game loop
    connect(m_gameLoop,SIGNAL(sPlayerAddCard(CCardInfo,int)),this,SLOT(onAddCard(CCardInfo,int)));
    connect(m_gameLoop,SIGNAL(sPlayerOutCard(CCardInfo,int)),this,SLOT(onOutCard(CCardInfo,int)));
    connect(m_gameLoop,SIGNAL(sEndCardChanged(CCardInfo)),this,SLOT(onEndCardChanged(CCardInfo))); 
    connect(m_gameLoop,SIGNAL(sEndCardChanged(ECardColor)),this,SLOT(onEndCardChanged(ECardColor)));
    connect(m_gameLoop,SIGNAL(sBlackToColor(ECardColor)),this,SLOT(onBlackToColor(ECardColor)));
    connect(m_gameLoop,SIGNAL(sErrorPromt()),this,SLOT(onError()));

    
    //Ui    
    connect(m_mainWidget->giveUpButton,SIGNAL(clicked(bool)),this,SLOT(onCGiveUp()));  
    connect(m_mainWidget->comboBox,SIGNAL(activated(int)),this,SLOT(onCombox(int)));
    connect(this,SIGNAL(choiced()),this,SLOT(onChoiced())); 
    
    
    //To do:插入背景图片游戏会卡，暂未解决
//    //set background picture
//    this->setBackGround();
    

    
}

CWidget::~CWidget()
{
    this->unInitButtons();

    //delete gameLoop
    if (nullptr == this->m_gameLoop)
    {
        ;
    }
    else
    {
        delete this->m_gameLoop;
        this->m_gameLoop = nullptr;
    }
    

    
    //delete mainWidget
    if (nullptr == this->m_mainWidget)
    {
        ;
    }
    else
    {
        delete this->m_mainWidget;
        this->m_mainWidget = nullptr;
    }
}


void CWidget::onStart()
{    
    //Init
    this->m_gameLoop->InitGame();
    this->initUI();
 
    //Round
    this->m_gameLoop->GameRound();
    
}

void CWidget::onAddCard(CCardInfo in_card, int current)
{
    //更新底部browser
    if (current == 0)
    {
        setSizeLabel(m_mainWidget->lowNumLabel, current);
        addButton(m_mainWidget->layoutLow, in_card, s_button_low, current, false, true);
    }

    //更新左侧browser
    else if (current == 1)
    {
        setSizeLabel(m_mainWidget->leftNumLabel, current);
        addButton(m_mainWidget->layoutLeft, in_card, s_button_left,current);     
    }

    //更新顶部browser
    else if (current == 2)
    {
        setSizeLabel(m_mainWidget->topNumLabel, current);
        addButton(m_mainWidget->layoutTop, in_card, s_button_top,current);
    }

    //更新右边browser
    else if (current == 3)
    {
        setSizeLabel(m_mainWidget->rightNumLabel, current);
        addButton(m_mainWidget->layoutRight, in_card, s_button_left,current);
    }
    else
    {
        ;
    } 
    
}

void CWidget::onOutCard(CCardInfo out_card, int current)
{    
    if (current == 0)
    {
        setSizeLabel(m_mainWidget->lowNumLabel, current);
        subButton(m_mainWidget->layoutLow, out_card);
        addButton(m_mainWidget->layoutLowOutCard, out_card, s_button_outCard,current, false);  
    }
    else if (current == 1)
    {
        setSizeLabel(m_mainWidget->leftNumLabel, current); 
        subButton(m_mainWidget->layoutLeft, out_card);
        addButton(m_mainWidget->layoutLeftOutCard, out_card, s_button_outCard, current, false);
    }
    else if (current == 2)
    {
        setSizeLabel(m_mainWidget->topNumLabel, current);
        subButton(m_mainWidget->layoutTop, out_card);
        addButton(m_mainWidget->layoutTopOutCard, out_card, s_button_outCard, current, false);
    }
    else if (current == 3)
    {
        setSizeLabel(m_mainWidget->rightNumLabel, current); 
        subButton(m_mainWidget->layoutRight, out_card);
        addButton(m_mainWidget->layoutRightOutCard, out_card, s_button_outCard, current, false);
    }
    else
    {
        
    }
    
}

void CWidget::onEndCardChanged(CCardInfo end_card)
{
    setIcon(m_mainWidget->EndCardButton, end_card, false);
}

void CWidget::onEndCardChanged(ECardColor color)
{
    CCardInfoEnd card = this->m_gameLoop->GetEndCard();
    card.SetColor(color);
    setIcon(m_mainWidget->EndCardButton, card, false);
}

void CWidget::onNotAllowOut()
{
    QString error = "Choice Error, not allow out";
    this->m_mainWidget->labelPrompt->setText(error);
}

void CWidget::onOver()
{
    CGameOverDialog dialog;
    
    //set winner
    CPlayer *winner = m_gameLoop->GetPlayer(m_gameLoop->GetJudge()->GetCurStation());
    dialog.setWinner(winner->GetAttribute().getName());
    
    //show dialog
    for (int i = 0; i < 4; ++i)
    {
        CPlayer *player = m_gameLoop->GetPlayer(i);
        QString  name   = player->GetAttribute().getName();
        int      score = m_gameLoop->GetPlayerScore(player);
        int      size = player->GetBox().Size();
        dialog.setTableItem(name, score);
        dialog.setTableItem(size, i);
    }
    
    dialog.exec();
    
    //set new round
    this->unInitUI();

    
}

void CWidget::onCGiveUp()
{
    this->m_gameLoop->GetJudge()->SetCurPlayerGiveup(true);
    emit choiced();
}

void CWidget::onCOutCard()
{
    QObject *sender = this->sender();
    QString cardInfo;
    if (nullptr == sender)
    {
        ;
    }
    else
    {
        cardInfo = sender->property("cardInfo").toString();
    }
    
    if (!cardInfo.isEmpty())
    {
        int          first_space    = cardInfo.indexOf(" ");
        
        QString     str_color       = cardInfo.left(first_space);
        QString     str_id          = cardInfo.section(' ',1, 1).trimmed();
        QString     str_action      = cardInfo.section(' ',2, 2).trimmed();
       
        
        ECardColor   color          = CCardTranslator::ToColor(str_color);
        ECardId      id             = CCardTranslator::ToID(str_id);
        ECardAction  action         = CCardTranslator::ToAction(str_action);
        
        CCardInfo   card(color,id,action);
        this->m_gameLoop->GetPlayer(this->m_gameLoop->GetJudge()->GetCurStation())->SetOutCard(card);
        this->m_gameLoop->GetJudge()->SetCurPlayerChoiced(true);
        
        if ((id == ECI_Black) || (id == ECI_BlackFour))
        {
            if (this->m_color_choice)
            {
                this->m_color_choice = false;
                emit choiced();
            }
            else
            {
                ;
            }
        }
        else
        {
            emit choiced();
        }
        
    }
    
}

void CWidget::onChoiced()
{
    this->m_mainWidget->labelPrompt->setText(QString::fromUtf8(""));
    this->m_mainWidget->EndCardlabel->setText(QString::fromUtf8(" "));
    this->m_gameLoop->GameRound();
}

void CWidget::onError()
{
    this->m_mainWidget->labelPrompt->setText(QString::fromUtf8("choiced error"));
}

void CWidget::onCombox(int num)
{
    if (num == 1)
    {
        this->m_gameLoop->GetJudge()->SetCurPlayerChangedColor(ECC_Red);
        
    }
    else if (num == 2)
    {
        this->m_gameLoop->GetJudge()->SetCurPlayerChangedColor(ECC_Yellow);
    }
    else if (num == 3)
    {
        this->m_gameLoop->GetJudge()->SetCurPlayerChangedColor(ECC_Blue);
    }
    else if (num == 4)
    {
        this->m_gameLoop->GetJudge()->SetCurPlayerChangedColor(ECC_Green);
    }
    else
    {
        ;
    }
    
    this->m_color_choice = true;
}

void CWidget::onBlackToColor(ECardColor color)
{
    QString     texts = QString::fromUtf8("Is color: ") + CCardTranslator::ToString(color);
    this->m_mainWidget->EndCardlabel->setText(texts);
}

void CWidget::initUI()
{
    //enable(false)
    this->m_mainWidget->startButton->setEnabled(false);
    this->m_mainWidget->giveUpButton->setEnabled(true);
    this->setScoreLabels();
}

void CWidget::unInitUI()
{
    this->m_mainWidget->startButton->setEnabled(true);
    this->unInitButtons();
    this->m_mainWidget->EndCardButton->setIcon(QIcon(":/new/src/icons/card-back.jpg"));
    
    m_mainWidget->leftNumLabel->setText("");
    m_mainWidget->topNumLabel->setText("");
    m_mainWidget->lowNumLabel->setText("");
    m_mainWidget->rightNumLabel->setText("");
}

void CWidget::setBackGround()
{
//    this->setAutoFillBackground(true);
    QPalette palet = this->palette();
    palet.setBrush(QPalette::Window
                   , QBrush(QPixmap(":/new/src/icons/background.jpg").scaled(this->size()
                                                                             ,Qt::IgnoreAspectRatio
                                                                             ,Qt::SmoothTransformation)));
    //平滑缩放
    this->setPalette(palet);
}

void CWidget::setScoreLabels()
{
    QString str_score;
    int     score;
    score       = this->m_gameLoop->GetPlayerScore(m_gameLoop->GetPlayer(0));
    str_score   = QString::number(score, 10);
    this->m_mainWidget->lowScoreLabel->setText(str_score);
    
    score       = this->m_gameLoop->GetPlayerScore(m_gameLoop->GetPlayer(1));
    str_score   = QString::number(score, 10);
    this->m_mainWidget->leftScoreLabel->setText(str_score);
    
    score       = this->m_gameLoop->GetPlayerScore(m_gameLoop->GetPlayer(2));
    str_score   = QString::number(score, 10);
    this->m_mainWidget->topScoreLabel->setText(str_score);
    
    score       = this->m_gameLoop->GetPlayerScore(m_gameLoop->GetPlayer(3));
    str_score   = QString::number(score, 10);
    this->m_mainWidget->rightScoreLabel->setText(str_score);
}

void CWidget::setSizeLabel(QLabel *label, int current)
{
    int score = m_gameLoop->GetPlayer(current)->GetBox().Size();
    label->setText(QString::number(score, 10));
}

void CWidget::setIcon(QPushButton *button, CCardInfo card, bool hide, bool rotat)
{
    QString pic_name;
    
    if (hide)
    {
        if (rotat)
        {
            pic_name = ":/new/src/icons/card-back-l.jpg";
        }
        else
        {
            pic_name = ":/new/src/icons/card-back.jpg";
        }
    }
    else
    {
        pic_name = getDir(card);
    }
    
    QPixmap pixmap(pic_name);
    button->setIcon(QIcon(pixmap));
    button->setIconSize(button->size());  

}


void CWidget::addButton(QLayout *layout, CCardInfo card, QSize size, int current, bool hide, bool click)
{
     QString         card_info;
     
     card_info = CCardTranslator::ToString(card.GetColor())
               + " "
               + CCardTranslator::ToString(card.GetId())
               + " "
               + CCardTranslator::ToString(card.GetAction());
     
     QPushButton *button = new QPushButton(this);
     button->setProperty("cardInfo", card_info);
     button->resize(size);
     button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
     
     //button icon
     if (current == 0)
     {
         setIcon(button, card, hide);
     }
     else if ((current == 1) || (current == 3))
     {
         setIcon(button, card, hide, true);
     }
     else if (current == 2)
     {
         setIcon(button, card, hide);
     }
     else
     {
         
     }
     
     
     //button click
     if (click)
     {
         connect(button,SIGNAL(clicked(bool)),this,SLOT(onCOutCard()));
     }
     
     
     layout->addWidget(button);
     button->show();
     button->repaint();
}

void CWidget::subButton(QLayout *layout, CCardInfo card)
{
    QString cardInfo;
    
    cardInfo = CCardTranslator::ToString(card.GetColor())
              + " "
              + CCardTranslator::ToString(card.GetId())
              + " "
              + CCardTranslator::ToString(card.GetAction());
    
    for (int i = layout->count() - 1 ; i >= 0; --i)
    {
        QLayoutItem *it = layout->itemAt(i);
        QPushButton *button = qobject_cast<QPushButton *>(it->widget());
        if (button != nullptr)
        {
            if (button->property("cardInfo") == cardInfo)
            {
//                layout->removeWidget(button);
                layout->removeItem(it);
                delete button;
                break;
            }
            else
            {
                ;
            }
        }
    }
}



QString CWidget::getDir(const CCardInfo &card)
{
    QString dir = ":/new/src/icons/";
    
    if (card.GetId() == ECI_Black)
    {
        dir.append("black");
    }
    else if (card.GetId() == ECI_BlackFour)
    {
        dir.append("black-add4");
    }
    else
    {
        if (card.GetColor() == ECC_Red)
        {
            dir.append("r-");
        }
        else if (card.GetColor() == ECC_Yellow)
        {
            dir.append("y-");
        }
        else if (card.GetColor() == ECC_Blue)
        {
            dir.append("b-");
        }
        else if (card.GetColor() == ECC_Green)
        {
            dir.append("g-");
        }
        else
        {
            ;
        }
        
        if (card.GetId() == ECI_Zero)
        {
            dir.append("n0");
        }
        else if (card.GetId() == ECI_One)
        {
            dir.append("n1");
        }
        else if (card.GetId() == ECI_Two)
        {
            dir.append("n2");
        }
        else if (card.GetId() == ECI_Three)
        {
            dir.append("n3");
        }
        else if (card.GetId() == ECI_Four)
        {
            dir.append("n4");
        }
        else if (card.GetId() == ECI_Five)
        {
            dir.append("n5");
        }
        else if (card.GetId() == ECI_Six)
        {
            dir.append("n6");
        }
        else if (card.GetId() == ECI_Seven)
        {
            dir.append("n7");
        }
        else if (card.GetId() == ECI_Eight)
        {
            dir.append("n8");
        }
        else if (card.GetId() == ECI_Nine)
        {
            dir.append("n9");
        }
        else if (card.GetId() == ECI_AddTwo)
        {
            dir.append("add2");
        }
        else if (card.GetId() == ECI_Resverse)
        {
            dir.append("rev");
        }
        else if (card.GetId() == ECI_Stop)
        {
            dir.append("stop");
        }
        else
        {
            ;
        }
    }
    
    
    dir.append(".jpg");
    return dir;
}

void CWidget::unInitButtons()
{
    unInitButton(this->m_mainWidget->layoutLow);
    unInitButton(this->m_mainWidget->layoutLowOutCard);
    
    unInitButton(this->m_mainWidget->layoutLeft);
    unInitButton(this->m_mainWidget->layoutLeftOutCard);
    
    unInitButton(this->m_mainWidget->layoutTop);
    unInitButton(this->m_mainWidget->layoutTopOutCard);
    
    unInitButton(this->m_mainWidget->layoutRight);
    unInitButton(this->m_mainWidget->layoutRightOutCard);
    
}

void CWidget::unInitButton(QLayout *layout)
{
    for (int i = layout->count() - 1; i >= 0; --i)
    {
        QLayoutItem *child = layout->itemAt(i);
        QPushButton *button = qobject_cast<QPushButton*>(child->widget());
        if (button != nullptr)
        {
            layout->removeWidget(button);
            delete button;
        }
    }
}
