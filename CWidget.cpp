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
    ,m_choice(-1)
{
    this->m_mainWidget = new Ui::CWidget();
    this->m_mainWidget->setupUi(this);
   
    this->m_gameLoop = new CGameLoop;
  
    //Game loop
    connect(m_gameLoop,SIGNAL(playerChanged()),this,SLOT(onPlayerChange()));    
    connect(m_gameLoop,SIGNAL(endCardChanged()),this,SLOT(onEndCardChange()));
    connect(m_gameLoop,SIGNAL(scoreChanged()),this,SLOT(onScoreChange()));
    connect(m_gameLoop,SIGNAL(firstRound()),this,SLOT(onFirstRound()));
    connect(m_gameLoop,SIGNAL(myRound()),this,SLOT(onMyRound()));    
    connect(m_gameLoop,SIGNAL(error()),this,SLOT(onError()));
    
    connect(m_gameLoop,SIGNAL(outCard(const CCardInfo &card)),this,SLOT(onOutCard(const CCardInfo &card)));
    connect(m_gameLoop,SIGNAL(inCard()),this,SLOT(onInCard()));
    
    //Ui
    connect(m_mainWidget->pushButtonStart,SIGNAL(clicked(bool)),this,SLOT(onGameStart()));
    connect(m_mainWidget->pushButtonGiveUp,SIGNAL(clicked(bool)),this,SLOT(onGiveUp()));
    connect(m_mainWidget->pushButtonOutCard,SIGNAL(clicked(bool)),this,SLOT(onOutCard()));

    
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
    
<<<<<<< Updated upstream
    if (nullptr == this->m_topListWidget)
    {
        ;
    }
    else
    {
        delete this->m_topListWidget;
        this->m_topListWidget = nullptr;
=======
    //delete cardButton
    QLayoutItem *child;
    while ((child = this->m_mainWidget->layoutLow->takeAt(0)) != 0) 
    {
        delete child;
>>>>>>> Stashed changes
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


void CWidget::showListWidgets()
{ 
    QString texts;
    QString scores;
    CPlayer player;
    QString name;

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
    
    this->m_topListWidget = new Ui::CTopList();
    this->m_topListWidget->textBrowser->setText(texts);
    this->m_topListWidget->setupUi(this);

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

<<<<<<< Updated upstream
void CWidget::onPlayerChange()
=======
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

void CWidget::upDateBrowser(int current,const QString &texts)
>>>>>>> Stashed changes
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

void CWidget::onFirstRound()
{
    CPlayer         cur_player;
    CCardInfo       card;
    QString         num[4];
    QString         texts[4];
   
    for (int i = 0; i < 4; ++i)
    {
        cur_player = this->m_gameLoop->getPlayer(i);
        num[i] = QString::number(cur_player.getBoxSize(), 10);
        for (int j = 0; j < cur_player.getBoxSize(); ++j)
        {
            card = cur_player.getNumCard(i);
            texts[i] += this->dbColor(card.getColor()) + this->dbId(card.getId()) + "\n";
        }
        
    }
    
    // 更新 browser
    this->m_mainWidget->labelNumLow->setText(num[0]);
    this->m_mainWidget->textBrowserLow->setText(texts[0]);
    
    this->m_mainWidget->labelNumLeft->setText(num[1]);
    this->m_mainWidget->textBrowserLeft->setText(texts[1]);
    
    this->m_mainWidget->labelNumTop->setText(num[2]);
    this->m_mainWidget->textBrowserTop->setText(texts[2]);
    
    this->m_mainWidget->labelNumRight->setText(num[3]);
    this->m_mainWidget->textBrowserRight->setText(texts[3]);

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
    this->showListWidgets();
}

void CWidget::onGameStart()
{    
    this->m_gameLoop->gameStart();
}

void CWidget::onOutCard(const CCardInfo &card)
{
    CPlayer cur_player;
    int current = this->m_gameLoop->getCurrent();
    QString num;
    //get current player info
    cur_player  = this->m_gameLoop->getPlayer(current);
    
    //num label
    num = QString::number(cur_player.getBoxSize(), 10);
    this->upDateLabelNum(current, num);
    
    QString cardInfo;
    
    for (int i = this->m_mainWidget->layoutLow->count() - 1 ; i >= 0; --i)
    {
        QLayoutItem *it = this->m_mainWidget->layoutLow->itemAt(i);
        QPushButton *button = qobject_cast<QPushButton *>(it->widget());
        if (button != nullptr)
        {
            cardInfo = this->dbColor(card.getColor())
                     + " " + this->dbId(card.getId());
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
        
}

void CWidget::onSetOutCard()
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
        //这里获得那张牌被选择了
        QString color = cardInfo.section(' ', 0, 0);
        QString id    = cardInfo.section(' ', 1, 1);
        CCardInfo card(color, id, );
        this->m_gameLoop->setOutCard(card);
        this->m_gameLoop->setIsChoiced(true);
        
    }
}

void CWidget::onInCard()
{    
    CPlayer         cur_player;
    QString         num;
    QString         cardInfo;

    //get current player info
    cur_player  = this->m_gameLoop->getPlayer(current);
    
    //num label
    num = QString::number(cur_player.getBoxSize(), 10);
    this->upDateLabelNum(current, num);
    
    //add card button
    cardInfo = this->dbColor(this->m_gameLoop->getInCard().getColor())
             + " " + this->dbId(this->m_gameLoop->getInCard().getId());
    
    QPushButton *button = new QPushButton;
    button->setProperty("cardInfo", cardInfo);
    button->resize(QSize(100, 300));
    this->m_mainWidget->layoutLow->addWidget(button);
    button->show();
    
    
}






