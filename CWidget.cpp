#include "CWidget.h"
#include "COverDialog.h"
#include "ui_CWidget.h"

#include <QFileDialog>
#include <QFile>
#include <QString>

CWidget::CWidget(QWidget *parent)
    :QWidget(parent)
    ,m_mainWidget(nullptr)
    ,m_gameLoop(nullptr)
    ,m_choice(-1)
{
    this->m_mainWidget = new Ui::CWidget();
    this->m_mainWidget->setupUi(this);
   
    this->m_gameLoop = new CGameLoop;
  
    //Game loop
    connect(m_gameLoop,SIGNAL(playerChanged(int)),this,SLOT(onPlayerChange(int)));    
    connect(m_gameLoop,SIGNAL(endCardChanged()),this,SLOT(onEndCardChange()));
    connect(m_gameLoop,SIGNAL(error()),this,SLOT(onError()));
    connect(m_gameLoop,SIGNAL(gameOver()),this,SLOT(onGameOver()));
    connect(m_gameLoop,SIGNAL(curPlayerFlash()),this,SLOT(onCurPlayerFlash()));
    connect(m_gameLoop,SIGNAL(curPlayerFlashOver()),this,SLOT(onCurPlayerFiashOver()));
    
    //Ui
    connect(m_mainWidget->pushButtonStart,SIGNAL(clicked(bool)),this,SLOT(onGameStart()));
    connect(m_mainWidget->pushButtonGiveUp,SIGNAL(clicked(bool)),this,SLOT(onGiveUpChoice()));
    connect(m_mainWidget->pushButtonOutCard,SIGNAL(clicked(bool)),this,SLOT(onOutCardChoice()));
    connect(this,SIGNAL(choiced()),this,SLOT(onChoice()));
    
}

CWidget::~CWidget()
{
    if (nullptr == this->m_gameLoop)
    {
        ;
    }
    else
    {
        delete this->m_gameLoop;
        this->m_gameLoop = nullptr;
    }

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


QString CWidget::dbColor(ECardColor color)
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

QString CWidget::dbId(ECardId id)
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

void CWidget::upDateBrowser(int current,const QString &texts)
{
    //更新底部browser
    if (current == 0)
    {
        this->m_mainWidget->textBrowserLow->setText(texts);
        this->m_mainWidget->textBrowserLow->repaint();
    }

    //更新左侧browser
    else if (current == 1)
    {
        this->m_mainWidget->textBrowserLeft->setText(texts);
        this->m_mainWidget->textBrowserLeft->repaint();
    }

    //更新顶部browser
    else if (current == 2)
    {
        this->m_mainWidget->textBrowserTop->setText(texts);
        this->m_mainWidget->textBrowserTop->repaint();
    }

    //更新右边browser
    else if (current == 3)
    {
        this->m_mainWidget->textBrowserRight->setText(texts);
        this->m_mainWidget->textBrowserRight->repaint();
    }
    else
    {
        ;
    }
}

void CWidget::upDateLabelNum(int current, const QString &num)
{
    //更新底部labelNum
    if (current == 0)
    {
        this->m_mainWidget->labelNumLow->setText(num);
        this->m_mainWidget->labelNumLow->repaint();
    }

    //更新左侧labelNum
    else if (current == 1)
    {
        this->m_mainWidget->labelNumLeft->setText(num);
        this->m_mainWidget->labelNumLeft->repaint();
    }

    //更新顶部labelNum
    else if (current == 2)
    {
        this->m_mainWidget->labelNumTop->setText(num);
        this->m_mainWidget->labelNumTop->repaint();
    }

    //更新右边labelNum
    else if (current == 3)
    {
        this->m_mainWidget->labelNumRight->setText(num);
        this->m_mainWidget->labelNumRight->repaint();
    }
    else
    {
        ;
    }
}

void CWidget::onPlayerChange(int current)
{
    CPlayer         cur_player;
    CCardInfo       card;
    QString         num;
    QString         texts;
    QString         index;

    //get current player info
    cur_player  = this->m_gameLoop->getPlayer(current);
    
    //label
    num = QString::number(cur_player.getBoxSize(), 10);

    //browser
    for (int i = 0; i < cur_player.getBoxSize(); ++i)
    {
        index = QString::number(i, 10);
        card = cur_player.getNumCard(i);
        texts += index +" : " + this->dbColor(card.getColor()) + this->dbId(card.getId()) + "\n";
    }
    
    this->upDateBrowser(current, texts);
    this->upDateLabelNum(current, num);
    
}

void CWidget::onEndCardChange()
{
    QString       texts;
    CCardInfo     card = this->m_gameLoop->getEndCard();
    texts = this->dbColor(card.getColor()) + this->dbId(card.getId());
    this->m_mainWidget->textBrowserEndCard->setText(texts);
    this->m_mainWidget->textBrowserEndCard->repaint();
}

void CWidget::onGiveUpChoice()
{
    this->m_choice = 111;
    this->m_gameLoop->setChoice(this->m_choice);
    emit choiced();
}

void CWidget::onOutCardChoice()
{
    QString texts;
    texts   = this->m_mainWidget->lineEditChoice->text();
    this->m_choice  = texts.toInt();
    this->m_gameLoop->setChoice(this->m_choice);
    emit choiced();
}

void CWidget::onError()
{
    QString error = "Choice Error";
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
        scores = QString::number(player.playerGetScore(),10);
        name = QString::fromStdString(player.playerGetName());
        texts += name + ": " + scores + "\n";
    }
    
    COverDialog over_dialog;
    over_dialog.setBrowser(texts);
    over_dialog.exec();  

}

void CWidget::onGameStart()
{    
    //update show
    for (int i = 0; i < 4; ++i)
    {
        this->onPlayerChange(i);
    }
    this->onEndCardChange();   
    
    //start
    this->m_gameLoop->gameRound(this->m_gameLoop->curIsMy());
}

void CWidget::onChoice()
{
    //Into my round
    bool is_my_round = true;
    this->m_gameLoop->gameRound(is_my_round);
    
    //Into other round
    this->m_gameLoop->gameRound(!is_my_round);
    
}

void CWidget::onCurPlayerFlash()
{
    QString texts = "My Round";
    if (this->m_gameLoop->getCurrent() == 0)
    {
        this->m_mainWidget->labelOutCardLow->setText(texts);
    }
    else if (this->m_gameLoop->getCurrent() == 1)
    {
        this->m_mainWidget->labelOutCardLeft->setText(texts);
    }
    else if (this->m_gameLoop->getCurrent() == 2)
    {
        this->m_mainWidget->labelOutCardTop->setText(texts);
    }
    else if (this->m_gameLoop->getCurrent() == 3)
    {
        this->m_mainWidget->labelOutCardRight->setText(texts);
    }
    else
    {
        ;
    }
    
    
}

void CWidget::onCurPlayerFiashOver()
{
    QString texts = " ";
    if (this->m_gameLoop->getCurrent() == 0)
    {
        this->m_mainWidget->labelOutCardLow->setText(texts);
    }
    else if (this->m_gameLoop->getCurrent() == 1)
    {
        this->m_mainWidget->labelOutCardLeft->setText(texts);
    }
    else if (this->m_gameLoop->getCurrent() == 2)
    {
        this->m_mainWidget->labelOutCardTop->setText(texts);
    }
    else if (this->m_gameLoop->getCurrent() == 3)
    {
        this->m_mainWidget->labelOutCardRight->setText(texts);
    }
    else
    {
        ;
    }
}






