#include "CWidget.h"
#include "CGameOverDialog.h"
#include "ui_CWidget.h"

#include <QFileDialog>
#include <QFile>
#include <QString>


CWidget::CWidget(QWidget *parent)
    :QWidget(parent)
    ,m_mainWidget(nullptr)
    ,m_gameLoop(nullptr)
    ,m_color_choice(false)
    ,m_size()
{    
    this->m_mainWidget = new Ui::CWidget(); 
    this->m_mainWidget->setupUi(this);
   
    this->m_gameLoop = new CGameLoop;
    
    //Game loop
    connect(m_gameLoop,SIGNAL(playerInCard(CCardInfo,int)),this,SLOT(onPlayerInCard(CCardInfo,int)));
    connect(m_gameLoop,SIGNAL(playerOutCard(CCardInfo,int)),this,SLOT(onPlayerOutCard(CCardInfo,int)));
    connect(m_gameLoop,SIGNAL(endCardChanged(CCardInfo)),this,SLOT(onEndCardChanged(CCardInfo)));
    connect(m_gameLoop,SIGNAL(gameOver()),this,SLOT(onGameOver()));
    connect(m_gameLoop,SIGNAL(notAllowOut()),this,SLOT(onErrorPromt()));
    connect(m_gameLoop,SIGNAL(changeColor(ECardColor)),this,SLOT(onChangeColor(ECardColor)));
    
    //Ui
    connect(m_mainWidget->pushButtonStart,SIGNAL(clicked(bool)),this,SLOT(onGameStart()));   
    connect(m_mainWidget->pushButtonGiveUp,SIGNAL(clicked(bool)),this,SLOT(onChoiceGiveUp()));    
    connect(this,SIGNAL(choiced()),this,SLOT(onChoiced())); 
    connect(this->m_mainWidget->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(onComboxChoice(int)));
    



}

CWidget::~CWidget()
{
    this->unInitButton();

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



void CWidget::unInitButton()
{
    QLayoutItem *child;
    //cardButton Low
    for (int i = this->m_mainWidget->layoutLow->count() - 1 ; i >= 0; --i)
    {
        child = this->m_mainWidget->layoutLow->itemAt(i);
        QPushButton *button = qobject_cast<QPushButton *>(child->widget());
        if (button != nullptr)
        {
            this->m_mainWidget->layoutLow->removeWidget(button);
            delete button;
        }
    }
    
    for (int i = this->m_mainWidget->layoutLowOutCard->count() - 1 ; i >= 0; --i)
    {
        child = this->m_mainWidget->layoutLowOutCard->itemAt(i);
        QPushButton *button = qobject_cast<QPushButton *>(child->widget());
        if (button != nullptr)
        {
            this->m_mainWidget->layoutLowOutCard->removeWidget(button);
            delete button;
        }
    }
    
    
    //cardButton Left
    for (int i = this->m_mainWidget->layoutLeft->count() - 1 ; i >= 0; --i)
    {
        child = this->m_mainWidget->layoutLeft->itemAt(i);
        QPushButton *button = qobject_cast<QPushButton *>(child->widget());
        if (button != nullptr)
        {
            this->m_mainWidget->layoutLeft->removeWidget(button);
            delete button;
        }
    }
    
    for (int i = this->m_mainWidget->layoutLeftOutCard->count() - 1 ; i >= 0; --i)
    {
        child = this->m_mainWidget->layoutLeftOutCard->itemAt(i);
        QPushButton *button = qobject_cast<QPushButton *>(child->widget());
        if (button != nullptr)
        {
            this->m_mainWidget->layoutLeftOutCard->removeWidget(button);
            delete button;
        }
    }

    
    //cardButton Top
    for (int i = this->m_mainWidget->layoutTop->count() - 1 ; i >= 0; --i)
    {
        child = this->m_mainWidget->layoutTop->itemAt(i);
        QPushButton *button = qobject_cast<QPushButton *>(child->widget());
        if (button != nullptr)
        {
            this->m_mainWidget->layoutTop->removeWidget(button);
            delete button;
        }
    }
    
    for (int i = this->m_mainWidget->layoutTopOutCard->count() - 1 ; i >= 0; --i)
    {
        child = this->m_mainWidget->layoutTopOutCard->itemAt(i);
        QPushButton *button = qobject_cast<QPushButton *>(child->widget());
        if (button != nullptr)
        {
            this->m_mainWidget->layoutTopOutCard->removeWidget(button);
            delete button;
        }
    }

    
    //cardButton Right
    for (int i = this->m_mainWidget->layoutRight->count() - 1 ; i >= 0; --i)
    {
        child = this->m_mainWidget->layoutRight->itemAt(i);
        QPushButton *button = qobject_cast<QPushButton *>(child->widget());
        if (button != nullptr)
        {
            this->m_mainWidget->layoutRight->removeWidget(button);
            delete button;
        }
    }
    
    for (int i = this->m_mainWidget->layoutRightOutCard->count() - 1 ; i >= 0; --i)
    {
        child = this->m_mainWidget->layoutRightOutCard->itemAt(i);
        QPushButton *button = qobject_cast<QPushButton *>(child->widget());
        if (button != nullptr)
        {
            this->m_mainWidget->layoutRightOutCard->removeWidget(button);
            delete button;
        }
    }


}
    
    

void CWidget::onGameStart()
{    
    //Init
    this->m_gameLoop->startGame();
    
    //enable(false)
    this->m_mainWidget->pushButtonStart->setEnabled(false);
    this->m_mainWidget->pushButtonGiveUp->setEnabled(true);
    
    //Round
    this->onChoiced();
}

void CWidget::onPlayerInCard(CCardInfo in_card, int current)
{
    QString         card_info;
    QString         card_info2;
    QString         str_num;
    card_info = this->dbColorToString(in_card.getColor()) 
              + " "
              + this->dbIdToString(in_card.getId())
              + " "
              + this->dbActionToString(in_card.getAction());
    
    card_info2 = this->dbColorToString(in_card.getColor()) 
               + "\n"
               + this->dbIdToString(in_card.getId())
               + "\n"
               + this->dbActionToString(in_card.getAction());
    
    QPushButton *button = new QPushButton(this);
    connect(button,SIGNAL(clicked(bool)),this,SLOT(onChoiceOutCard()));
    button->setProperty("cardInfo", card_info);
    
    
    //更新底部browser
    if (current == 0)
    {
        //button
        button->setText(card_info2);
        button->resize(QSize(50, 200));
        this->m_mainWidget->layoutLow->addWidget(button); 
        
        //score
        m_size[0]++;
        str_num = QString::number(m_size[0], 10);
        this->m_mainWidget->labelNumLow->setText(str_num);
        
    }

    //更新左侧browser
    else if (current == 1)
    {
        //button
        button->setText(card_info);
        button->setEnabled(false);
        this->m_mainWidget->layoutLeft->addWidget(button);
        
        //score
        m_size[1]++;
        str_num = QString::number(m_size[1], 10);
        this->m_mainWidget->labelNumLeft->setText(str_num);
          
    }

    //更新顶部browser
    else if (current == 2)
    {
        //button
        button->setText(card_info2);
        button->resize(QSize(50, 200));
        button->setEnabled(false);
        this->m_mainWidget->layoutTop->addWidget(button);
        
        //score
        m_size[2]++;
        str_num = QString::number(m_size[2], 10);
        this->m_mainWidget->labelNumTop->setText(str_num);
        
    }

    //更新右边browser
    else if (current == 3)
    {
        //button
        button->setText(card_info);
        button->setEnabled(false);
        this->m_mainWidget->layoutRight->addWidget(button);
        
        //score
        m_size[3]++;
        str_num = QString::number(m_size[3], 10);
        this->m_mainWidget->labelNumRight->setText(str_num);
        
    }
    else
    {
        ;
    } 
    
    button->show();
    button->repaint();
    
}

void CWidget::onPlayerOutCard(CCardInfo out_card, int current)
{
    QString cardInfo;
    cardInfo = this->dbColorToString(out_card.getColor())
             + " " 
             + this->dbIdToString(out_card.getId())             
             + " "
             + this->dbActionToString(out_card.getAction());
    QString str_num;
    
    if (current == 0)
    {
        //button
        for (int i = this->m_mainWidget->layoutLow->count() - 1 ; i >= 0; --i)
        {
            QLayoutItem *it = this->m_mainWidget->layoutLow->itemAt(i);
            QPushButton *button = qobject_cast<QPushButton *>(it->widget());
            if (button != nullptr)
            {
                if (button->property("cardInfo") == cardInfo)
                {
                    this->m_mainWidget->layoutLow->removeWidget(button);
                    delete button;
                    break;
                }
                else
                {
                    ;
                }
            }
        }
        
        //score
        m_size[0]--;
        str_num = QString::number(m_size[0], 10);
        this->m_mainWidget->labelNumLow->setText(str_num);
        this->m_mainWidget->labelNumLow->repaint();
    }
    else if (current == 1)
    {
        //button
        for (int i = this->m_mainWidget->layoutLeft->count() - 1 ; i >= 0; --i)
        {
            QLayoutItem *it = this->m_mainWidget->layoutLeft->itemAt(i);
            QPushButton *button = qobject_cast<QPushButton *>(it->widget());
            if (button != nullptr)
            {
                if (button->property("cardInfo") == cardInfo)
                {
                    this->m_mainWidget->layoutLeft->removeWidget(button);
                    delete button;
                    break;
                }
                else
                {
                    ;
                }
            }
        }
        
        //score
        m_size[1]--;
        str_num = QString::number(m_size[1], 10);
        this->m_mainWidget->labelNumLeft->setText(str_num);
        this->m_mainWidget->labelNumLeft->repaint();
    }
    else if (current == 2)
    {
        //button
        for (int i = this->m_mainWidget->layoutTop->count() - 1 ; i >= 0; --i)
        {
            QLayoutItem *it = this->m_mainWidget->layoutTop->itemAt(i);
            QPushButton *button = qobject_cast<QPushButton *>(it->widget());
            if (button != nullptr)
            {
                if (button->property("cardInfo") == cardInfo)
                {
                    this->m_mainWidget->layoutTop->removeWidget(button);
                    delete button;
                    break;
                }
                else
                {
                    ;
                }
            }
        }
        
        //score
        m_size[2]--;
        str_num = QString::number(m_size[2], 10);
        this->m_mainWidget->labelNumTop->setText(str_num);
        this->m_mainWidget->labelNumTop->repaint();
    }
    else if (current == 3)
    {
        //button
        for (int i = this->m_mainWidget->layoutRight->count() - 1 ; i >= 0; --i)
        {
            QLayoutItem *it = this->m_mainWidget->layoutRight->itemAt(i);
            QPushButton *button = qobject_cast<QPushButton *>(it->widget());
            if (button != nullptr)
            {
                if (button->property("cardInfo") == cardInfo)
                {
                    this->m_mainWidget->layoutRight->removeWidget(button);
                    delete button;
                    break;
                }
                else
                {
                    ;
                }
            }
        }
        
        //score
        m_size[3]--;
        str_num = QString::number(m_size[3], 10);
        this->m_mainWidget->labelNumRight->setText(str_num);
        this->m_mainWidget->labelNumRight->repaint();
    }
    else
    {
        
    }
    
    this->showOutCard(out_card, current);
}

void CWidget::onEndCardChanged(CCardInfo end_card)
{
    QString       texts;
    texts = this->dbColorToString(end_card.getColor()) + this->dbIdToString(end_card.getId());
    this->m_mainWidget->textBrowserEndCard->setText(texts);
}

void CWidget::onNotAllowOut()
{
    QString error = "Choice Error, not allow out";
    this->m_mainWidget->labelPrompt->setText(error);
}

void CWidget::onGameOver()
{

    //******************************
    CGameOverDialog dialog;
    dialog.createDb();
    
    int          scores;
    CPlayer      player;
    QString      name;
    for (int i = 0; i < 4; ++i)
    {
        player = this->m_gameLoop->getPlayer(i);
        scores = player.getPlayerScore();
        name = QString::fromStdString(player.getPlayerName());
        dialog.updateDb(name, scores);
    }
    dialog.selectDb();    
    dialog.exec();
    //******************************
    
    //enable(false)
    this->m_mainWidget->pushButtonStart->setEnabled(true);
    this->unInitButton();
    for (int i = 0; i < 4; ++i)
    {
        this->m_size[i] = 0;
    }
    
}

void CWidget::onChoiceGiveUp()
{
    this->m_gameLoop->curPlayerChangeToGiveUp();
    emit choiced();
}

void CWidget::onChoiceOutCard()
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
    
    if (cardInfo.isEmpty())
    {
        ;
    }
    else
    {
        int          first_space    = cardInfo.indexOf(" ");
        
        QString     str_color       = cardInfo.left(first_space);
        QString     str_id          = cardInfo.section(' ',1, 1).trimmed();
        QString     str_action      = cardInfo.section(' ',2, 2).trimmed();
        
        ECardColor   color          = this->dbColorToCard(str_color);
        ECardId      id             = this->dbIdToCard(str_id);
        ECardAction  action         = this->dbActionToCard(str_action);
        
        CCardInfo   card(color,id,action);
        this->m_gameLoop->curPlayerChangeOutCard(card);
        
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
    this->m_gameLoop->gameRound();
}

void CWidget::onErrorPromt()
{
    this->m_mainWidget->labelPrompt->setText(QString::fromUtf8("choiced error"));
}

void CWidget::onChangeColor(ECardColor color)
{
    
    QString       texts = QString::fromUtf8("Is color: ") + dbColorToString(color);
    this->m_mainWidget->textBrowserEndCard->append(texts);
    
}

void CWidget::onComboxChoice(int num)
{
    if (num == 0)
    {
        this->m_gameLoop->setChangeColor(ECC_Red);
    }
    else if (num == 1)
    {
        this->m_gameLoop->setChangeColor(ECC_Yellow);
    }
    else if (num == 2)
    {
        this->m_gameLoop->setChangeColor(ECC_Blue);
    }
    else if (num == 3)
    {
        this->m_gameLoop->setChangeColor(ECC_Green);
    }
    else
    {
        ;
    }
    
    this->m_color_choice = true;
}


QString CWidget::dbColorToString(ECardColor color)
{
    typedef QMap<ECardColor, QString>CardColor;
    static CardColor cardColors;
    if (cardColors.isEmpty())
    {
        cardColors.insert(ECardColor::ECC_Red, QString::fromUtf8("Red"));
        cardColors.insert(ECardColor::ECC_Yellow, QString::fromUtf8("Yellow"));
        cardColors.insert(ECardColor::ECC_Blue, QString::fromUtf8("Blue"));
        cardColors.insert(ECardColor::ECC_Green, QString::fromUtf8("Green"));
        cardColors.insert(ECardColor::ECC_Black, QString::fromUtf8("Black"));
    }
    return cardColors.value(color);
}

QString CWidget::dbIdToString(ECardId id)
{
    typedef QMap<ECardId,QString>CardId;
    static CardId cardIds;
    if (cardIds.isEmpty())
    {
        cardIds.insert(ECardId::ECI_Zero, QString::fromUtf8("0"));
        cardIds.insert(ECardId::ECI_One, QString::fromUtf8("1"));
        cardIds.insert(ECardId::ECI_Two, QString::fromUtf8("2"));
        cardIds.insert(ECardId::ECI_Three, QString::fromUtf8("3"));
        cardIds.insert(ECardId::ECI_Four, QString::fromUtf8("4"));
        cardIds.insert(ECardId::ECI_Five, QString::fromUtf8("5"));
        cardIds.insert(ECardId::ECI_Six, QString::fromUtf8("6"));
        cardIds.insert(ECardId::ECI_Seven, QString::fromUtf8("7"));
        cardIds.insert(ECardId::ECI_Eight, QString::fromUtf8("8"));
        cardIds.insert(ECardId::ECI_Nine, QString::fromUtf8("9"));
        cardIds.insert(ECardId::ECI_AddTwo, QString::fromUtf8("AddTwo"));
        cardIds.insert(ECardId::ECI_Resverse, QString::fromUtf8("Resverse"));
        cardIds.insert(ECardId::ECI_Stop, QString::fromUtf8("Stop"));
        cardIds.insert(ECardId::ECI_Black, QString::fromUtf8("Black"));
        cardIds.insert(ECardId::ECI_BlackFour, QString::fromUtf8("BlackFour"));
    }
    return cardIds.value(id);
}

QString CWidget::dbActionToString(ECardAction action)
{
    typedef QMap<ECardAction,QString>CardAction;
    static CardAction cardActions;
    if (cardActions.isEmpty())
    {
        cardActions.insert(ECardAction::ECA_None, QString::fromUtf8("None"));
        cardActions.insert(ECardAction::ECA_Reverse, QString::fromUtf8("Reverse"));
        cardActions.insert(ECardAction::ECA_Stop, QString::fromUtf8("Stop"));
        cardActions.insert(ECardAction::ECA_ChangeColor, QString::fromUtf8("ChangeColor"));
        cardActions.insert(ECardAction::ECA_ActionTwo, QString::fromUtf8("ActionTwo"));
        cardActions.insert(ECardAction::ECA_Black, QString::fromUtf8("Black"));
        cardActions.insert(ECardAction::ECA_BlackFour, QString::fromUtf8("BlackFour"));

    }
    return cardActions.value(action);
}



ECardColor CWidget::dbColorToCard(QString color)
{
    typedef QMap<QString, ECardColor>CardColor;
    static CardColor cardColors;
    if (cardColors.isEmpty())
    {
        cardColors.insert("Red", ECardColor::ECC_Red);
        cardColors.insert("Yellow", ECardColor::ECC_Yellow);
        cardColors.insert("Blue",ECardColor::ECC_Blue);
        cardColors.insert("Green",ECardColor::ECC_Green);
        cardColors.insert("Black",ECardColor::ECC_Black);
    }
    return cardColors.value(color);

}

ECardId CWidget::dbIdToCard(QString id)
{
    typedef QMap<QString, ECardId>CardId;
    static CardId cardIds;
    if (cardIds.isEmpty())
    {
        cardIds.insert("0", ECardId::ECI_Zero);
        cardIds.insert("1", ECardId::ECI_One);
        cardIds.insert("2", ECardId::ECI_Two);
        cardIds.insert("3", ECardId::ECI_Three);
        cardIds.insert("4", ECardId::ECI_Four);
        cardIds.insert("5", ECardId::ECI_Five);
        cardIds.insert("6", ECardId::ECI_Six);
        cardIds.insert("7", ECardId::ECI_Seven);
        cardIds.insert("8", ECardId::ECI_Eight);
        cardIds.insert("9", ECardId::ECI_Nine);
        cardIds.insert("AddTwo", ECardId::ECI_AddTwo);
        cardIds.insert("Resverse", ECardId::ECI_Resverse);
        cardIds.insert("Stop", ECardId::ECI_Stop);
        cardIds.insert("Black", ECardId::ECI_Black);
        cardIds.insert("BlackFour", ECardId::ECI_BlackFour);        
        
    }

    return cardIds.value(id);
}

ECardAction CWidget::dbActionToCard(QString action)
{
    typedef QMap<QString,ECardAction>CardAction;
    static CardAction cardActions;
    if (cardActions.isEmpty())
    {
        cardActions.insert("None", ECardAction::ECA_None);
        cardActions.insert("Reverse", ECardAction::ECA_Reverse);
        cardActions.insert("Stop", ECardAction::ECA_Stop);
        cardActions.insert("ChangeColor", ECardAction::ECA_ChangeColor);
        cardActions.insert("ActionTwo", ECardAction::ECA_ActionTwo);
        cardActions.insert("Black", ECardAction::ECA_Black);
        cardActions.insert("BlackFour", ECardAction::ECA_BlackFour);

    }
    return cardActions.value(action);
}

void CWidget::showPlayerScores()
{
    QString str_score;
    int     score;
    score       = this->m_gameLoop->getPlayerScore(0);
    str_score   = QString::number(score, 10);
    this->m_mainWidget->labelScoreLow->setText(str_score);
    
    score       = this->m_gameLoop->getPlayerScore(1);
    str_score   = QString::number(score, 10);
    this->m_mainWidget->labelScoreLeft->setText(str_score);
    
    score       = this->m_gameLoop->getPlayerScore(2);
    str_score   = QString::number(score, 10);
    this->m_mainWidget->labelScoreTop->setText(str_score);
    
    score       = this->m_gameLoop->getPlayerScore(3);
    str_score   = QString::number(score, 10);
    this->m_mainWidget->labelScoreRight->setText(str_score);
}

void CWidget::showOutCard(CCardInfo in_card, int current)
{
    QString         card_info;
    QString         card_info2;
    card_info = this->dbColorToString(in_card.getColor()) 
              + " "
              + this->dbIdToString(in_card.getId())
              + " "
              + this->dbActionToString(in_card.getAction());
    
    card_info2 = this->dbColorToString(in_card.getColor()) 
               + "\n"
               + this->dbIdToString(in_card.getId())
               + "\n"
               + this->dbActionToString(in_card.getAction());
    
    QPushButton *new_button = new QPushButton(this);
    new_button->setFixedHeight(100);
    new_button->setFixedWidth(100);
    new_button->setEnabled(false);
    
    //更新底部browser
    if (current == 0)
    {
        if (this->m_mainWidget->layoutLowOutCard->isEmpty())
        {
            ;
        }
        else
        {
            QLayoutItem *it = this->m_mainWidget->layoutLowOutCard->itemAt(0);
            QPushButton *button = qobject_cast<QPushButton *>(it->widget());
            if (button != nullptr)
            {
                this->m_mainWidget->layoutLowOutCard->removeWidget(button);
                delete button;
            }
            else
            {
                ;
            }
        }
        
        new_button->setText(card_info2);
        this->m_mainWidget->layoutLowOutCard->addWidget(new_button); 

    }

    //更新左侧browser
    else if (current == 1)
    {
        if (this->m_mainWidget->layoutLeftOutCard->isEmpty())
        {
            ;
        }
        else
        {
            QLayoutItem *it = this->m_mainWidget->layoutLeftOutCard->itemAt(0);
            QPushButton *button = qobject_cast<QPushButton *>(it->widget());
            if (button != nullptr)
            {
                this->m_mainWidget->layoutLeftOutCard->removeWidget(button);
                delete button;
            }
            else
            {
                ;
            }
        }
        
        new_button->setText(card_info2);
        this->m_mainWidget->layoutLeftOutCard->addWidget(new_button); 
          
    }

    //更新顶部browser
    else if (current == 2)
    {
        if (this->m_mainWidget->layoutTopOutCard->isEmpty())
        {
            ;
        }
        else
        {
            QLayoutItem *it = this->m_mainWidget->layoutTopOutCard->itemAt(0);
            QPushButton *button = qobject_cast<QPushButton *>(it->widget());
            if (button != nullptr)
            {
                this->m_mainWidget->layoutTopOutCard->removeWidget(button);
                delete button;
            }
            else
            {
                ;
            }
        }
        
        new_button->setText(card_info2);
        this->m_mainWidget->layoutTopOutCard->addWidget(new_button); 
        
    }

    //更新右边browser
    else if (current == 3)
    {
        if (this->m_mainWidget->layoutRightOutCard->isEmpty())
        {
            ;
        }
        else
        {
            QLayoutItem *it = this->m_mainWidget->layoutRightOutCard->itemAt(0);
            QPushButton *button = qobject_cast<QPushButton *>(it->widget());
            if (button != nullptr)
            {
                this->m_mainWidget->layoutRightOutCard->removeWidget(button);
                delete button;
            }
            else
            {
                ;
            }
        }
        
        new_button->setText(card_info2);
        this->m_mainWidget->layoutRightOutCard->addWidget(new_button); 
        
    }
    else
    {
        ;
    } 
    
    new_button->show();
    new_button->repaint();
    
}





