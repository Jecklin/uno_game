#include "CWidget.h"
#include "ui_CWidget.h"
#include "ui_CTopList.h"

#include <QFileDialog>
#include <QFile>
#include <QString>

CWidget::CWidget(QWidget *parent)
    :QWidget(parent)
    ,m_mainWidget(nullptr)
    ,m_topListWidget(nullptr)
    ,m_gameLoop(nullptr)
{
    this->m_mainWidget = new Ui::CWidget();
    this->m_mainWidget->setupUi(this);
    this->m_gameLoop = new CGameLoop;

    //Game loop
    connect(m_gameLoop,SIGNAL(playerChanged()),this,SLOT(onPlayerChange()));    
    connect(m_gameLoop,SIGNAL(endCardChanged()),this,SLOT(onEndCardChange()));
    connect(m_gameLoop,SIGNAL(scoreChanged()),this,SLOT(onScoreChange()));
    connect(m_gameLoop,SIGNAL(myRound()),this,SLOT(onMyRound()));    
    connect(m_gameLoop,SIGNAL(error()),this,SLOT(onError()));
    
    //Ui
    connect(m_mainWidget->pushButtonGiveUp,SIGNAL(clicked(bool)),this,SLOT(onGiveUp()));
    connect(m_mainWidget->pushButtonOutCard,SIGNAL(clicked(bool)),this,SLOT(onOutCard()));

    

    //Init
    this->m_gameLoop->gameStart();
    
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
        this->destroyListWidgets();
        delete this->m_mainWidget;
        this->m_mainWidget = nullptr;
    }

}

void CWidget::createListWidgets()
{
    if (nullptr == this->m_topListWidget)
    {
        QWidget *buff = new QWidget(this);
        this->m_topListWidget = new Ui::CTopList();
        this->m_topListWidget->setupUi(buff);
    }
    else
    {
        ;
    }
    
    QString texts;
    QString scores;
    CPlayer player;
    QString name;
    //QString qstr2 = QString::fromStdString(s);
    for (int i = 0; i < 4; ++i)
    {
        player = this->m_gameLoop->getPlayer(i);
        scores = QString::number(player.playerGetScore(),10);
        name = QString::fromStdString(player.playerGetName());
        texts += name;
        texts += ": ";
        texts += scores;
        texts += "\n";
    }
    
    this->m_topListWidget->textBrowser->setText(texts);

}

void CWidget::destroyListWidgets()
{
    if (nullptr == this->m_topListWidget)
    {
        ;
    }
    else
    {
        delete this->m_topListWidget;
        this->m_topListWidget = nullptr;
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

void CWidget::onPlayerChange()
{
    CPlayer         cur_player;
    CCardInfo       card;
    QString         num;
    QString         texts;

    //获取当前玩家信息
    int current = this->m_gameLoop->getCurrent();
    cur_player  = this->m_gameLoop->getPlayer(current);

    num = QString::number(cur_player.getBoxSize(), 10);

    for (int i = 0; i < cur_player.getBoxSize(); ++i)
    {
        card = cur_player.getNumCard(i);
        texts += this->dbColor(card.getColor()) + this->dbId(card.getId()) + "\n";
    }

    //更新底部browser
    if (current == 0)
    {
        this->m_mainWidget->labelNumLow->setText(num);
        this->m_mainWidget->textBrowserLow->setText(texts);
    }

    //更新左侧browser
    else if (current == 1)
    {
        this->m_mainWidget->labelNumLeft->setText(num);
        this->m_mainWidget->textBrowserLeft->setText(texts);
    }

    //更新顶部browser
    else if (current == 2)
    {
        this->m_mainWidget->labelNumTop->setText(num);
        this->m_mainWidget->textBrowserTop->setText(texts);
    }

    //更新右边browser
    else if (current == 3)
    {
        this->m_mainWidget->labelNumRight->setText(num);
        this->m_mainWidget->textBrowserRight->setText(texts);
    }
    else
    {
        ;
    }
}

void CWidget::onEndCardChange()
{
    QString       texts;
    CCardInfo     card = this->m_gameLoop->getEndCard();
    texts = this->dbColor(card.getColor()) + this->dbId(card.getId());
    this->m_mainWidget->textBrowserEndCard->setText(texts);
}

void CWidget::onScoreChange()
{
    QString       score;
    CPlayer       player = this->m_gameLoop->getPlayer(0);
    score = QString::number(player.playerGetScore(),10);
    this->m_mainWidget->labelScoreLow->setText(score);

    player = this->m_gameLoop->getPlayer(1);
    score = QString::number(player.playerGetScore(),10);
    this->m_mainWidget->labelScoreLeft->setText(score);

    player = this->m_gameLoop->getPlayer(2);
    score = QString::number(player.playerGetScore(),10);
    this->m_mainWidget->labelScoreTop->setText(score);

    player = this->m_gameLoop->getPlayer(3);
    score = QString::number(player.playerGetScore(),10);
    this->m_mainWidget->labelScoreRight->setText(score);
    
}

void CWidget::onMyRound()
{
    this->m_gameLoop->setChoice(this->m_choice);
}

void CWidget::onGiveUp()
{
    this->m_choice = 111;
}

void CWidget::onOutCard()
{
    QString texts;
    texts   = this->m_mainWidget->lineEditChoice->text();
    this->m_choice  = texts.toInt();
}

void CWidget::onError()
{
    QString error = "Choice Error";
    this->m_mainWidget->labelPrompt->setText(error);
}

void CWidget::onGameOver()
{
    this->createListWidgets();
}






