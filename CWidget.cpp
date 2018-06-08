#include "CWidget.h"
#include "CGameOverDialog.h"
#include "ui_CWidget.h"
#include "ui_CTopList.h"

#include <QFileDialog>
#include <QFile>
#include <QString>

CWidget::CWidget(QWidget *parent)
    :QWidget(parent)
    ,m_mainWidget(nullptr)
    ,m_gameLoop(nullptr)
    ,m_choice(false)
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
    
    //Ui
    connect(m_mainWidget->pushButtonStart,SIGNAL(clicked(bool)),this,SLOT(onGameStart()));   
    connect(m_mainWidget->pushButtonGiveUp,SIGNAL(clicked(bool)),this,SLOT(onChoiceGiveUp()));    
    connect(this,SIGNAL(choiced()),this,SLOT(onChoiced())); 
    
}

CWidget::~CWidget()
{
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
    
    
    //delete cardButton
    QLayoutItem *child;
    while ((child = this->m_mainWidget->layoutLow->takeAt(0)) != 0) 
    {
        delete child;
        
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
    
    

void CWidget::onGameStart()
{    
    this->m_gameLoop->startGame();
}

void CWidget::onPlayerInCard(CCardInfo in_card, int current)
{
    QString         card_info;
    QString         str_num;
    card_info = this->dbColorToString(in_card.getColor()) 
              + " "
              + this->dbIdToString(in_card.getId())
              + " "
              + this->dbActionToString(in_card.getAction());
    
    QPushButton *button = new QPushButton;
    connect(button,SIGNAL(clicked(bool)),this,SLOT(onChoiceOutCard(in_card)));
    button->setProperty("cardInfo", card_info);
    button->setText(card_info);
    button->resize(QSize(100, 300));
    
    //更新底部browser
    if (current == 0)
    {
        m_size[0]++;
        str_num = QString::number(m_size[0], 10);
        this->m_mainWidget->labelNumLow->setText(str_num);
        this->m_mainWidget->layoutLow->addWidget(button);   
    }

    //更新左侧browser
    else if (current == 1)
    {
        m_size[1]++;
        str_num = QString::number(m_size[1], 10);
        this->m_mainWidget->labelNumLeft->setText(str_num);
        this->m_mainWidget->layoutLeft->addWidget(button);  
    }

    //更新顶部browser
    else if (current == 2)
    {
        m_size[2]++;
        str_num = QString::number(m_size[2], 10);
        this->m_mainWidget->labelNumTop->setText(str_num);
        this->m_mainWidget->layoutTop->addWidget(button);
    }

    //更新右边browser
    else if (current == 3)
    {
        m_size[3]++;
        str_num = QString::number(m_size[3], 10);
        this->m_mainWidget->labelNumRight->setText(str_num);
        this->m_mainWidget->layoutRight->addWidget(button);
    }
    else
    {
        ;
    } 
    
    button->show();
    
}

void CWidget::onPlayerOutCard(CCardInfo out_card, int current)
{
    QString cardInfo = this->dbColorToString(out_card.getColor())
                     + " " 
                     + this->dbIdToString(out_card.getId())             
                     + " "
                     + this->dbActionToString(out_card.getAction());
    QString str_num;
    
    if (current == 0)
    {
        for (int i = this->m_mainWidget->layoutLow->count() - 1 ; i >= 0; --i)
        {
            QLayoutItem *it = this->m_mainWidget->layoutLow->itemAt(i);
            QPushButton *button = qobject_cast<QPushButton *>(it->widget());
            if (button != nullptr)
            {
                if (button->property("cardInfo") == cardInfo)
                {
                    this->m_mainWidget->layoutLow->removeWidget(button);
                    break;
                }
                else
                {
                    ;
                }
            }
        }
        
        m_size[0]--;
        str_num = QString::number(m_size[0], 10);
        this->m_mainWidget->labelNumLow->setText(str_num);
    }
    else if (current == 1)
    {
        for (int i = this->m_mainWidget->layoutLeft->count() - 1 ; i >= 0; --i)
        {
            QLayoutItem *it = this->m_mainWidget->layoutLeft->itemAt(i);
            QPushButton *button = qobject_cast<QPushButton *>(it->widget());
            if (button != nullptr)
            {
                if (button->property("cardInfo") == cardInfo)
                {
                    this->m_mainWidget->layoutLeft->removeWidget(button);
                    break;
                }
                else
                {
                    ;
                }
            }
        }
        
        m_size[1]--;
        str_num = QString::number(m_size[1], 10);
        this->m_mainWidget->labelNumLeft->setText(str_num);
    }
    else if (current == 2)
    {
        for (int i = this->m_mainWidget->layoutTop->count() - 1 ; i >= 0; --i)
        {
            QLayoutItem *it = this->m_mainWidget->layoutTop->itemAt(i);
            QPushButton *button = qobject_cast<QPushButton *>(it->widget());
            if (button != nullptr)
            {
                if (button->property("cardInfo") == cardInfo)
                {
                    this->m_mainWidget->layoutTop->removeWidget(button);
                    break;
                }
                else
                {
                    ;
                }
            }
        }
        
        m_size[2]--;
        str_num = QString::number(m_size[2], 10);
        this->m_mainWidget->labelNumTop->setText(str_num);
    }
    else if (current == 3)
    {
        for (int i = this->m_mainWidget->layoutRight->count() - 1 ; i >= 0; --i)
        {
            QLayoutItem *it = this->m_mainWidget->layoutRight->itemAt(i);
            QPushButton *button = qobject_cast<QPushButton *>(it->widget());
            if (button != nullptr)
            {
                if (button->property("cardInfo") == cardInfo)
                {
                    this->m_mainWidget->layoutRight->removeWidget(button);
                    break;
                }
                else
                {
                    ;
                }
            }
        }
        
        m_size[3]--;
        str_num = QString::number(m_size[3], 10);
        this->m_mainWidget->labelNumRight->setText(str_num);
    }
    else
    {
        
    }
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
    QString      texts;
    QString      scores;
    CPlayer      player;
    QString      name;
    
    texts = QString::fromUtf8("*****  Game Over  ****\n");
    for (int i = 0; i < 4; ++i)
    {
        player = this->m_gameLoop->getPlayer(i);
        scores = QString::number(player.getPlayerScore(),10);
        name = QString::fromStdString(player.getPlayerName());
        texts += name + ": " + scores + "\n";
    }
    
    CGameOverDialog dialog;
    dialog.setTextBrowser(texts);
    dialog.exec();
    
}

void CWidget::onChoiceGiveUp()
{
    this->m_gameLoop->curPlayerChangeToGiveUp();
    emit choiced();
}

void CWidget::onChoiceOutCard(CCardInfo card)
{
    this->m_gameLoop->curPlayerChangeOutCard(card);
    emit choiced();
}

void CWidget::onChoiced()
{
    this->m_gameLoop->myRound();
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





