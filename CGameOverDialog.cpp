#include "CGameOverDialog.h"
#include "ui_CGameOverDialog.h"
#include <QStandardItemModel>
#include <QHeaderView>
#include <QFont>
#include <QDebug>
#include "CGame/CDataBase.h"

CGameOverDialog::CGameOverDialog(QWidget *parent):QDialog(parent)
    ,m_dialog(nullptr)
    ,m_model(nullptr)
{
    m_dialog = new Ui::CGameOverDialog();
    m_dialog->setupUi(this);
    
    initTableView();
}

CGameOverDialog::~CGameOverDialog()
{    
    if (nullptr == m_model)
    {
        ;
    }
    else
    {
        delete m_model;
        m_model = nullptr;
    }
    
    
    if (nullptr == m_dialog)
    {
        ;
    }
    else
    {
        delete m_dialog;
        m_dialog = nullptr;
    }
}

void CGameOverDialog::setTableItem(const QString &name, int score, int row)
{
    QStandardItem *itemName;
    QStandardItem *itemScore;
    QString str_score = QString::number(score, 10);
    
    itemName = new QStandardItem;
    itemName->setData(name, 0);
    itemScore = new QStandardItem;
    itemScore->setData(str_score, 0);
    
    m_model->setItem(row, 0, itemName);
    m_model->setItem(row, 1, itemScore);
    
    m_model->item(row, 1)->setTextAlignment(Qt::AlignCenter);
    m_model->item(row, 1)->setForeground(QBrush(QColor(255, 0, 0)));
    
}

void CGameOverDialog::setTableItem(const QString &name, int score)
{ 
    QStandardItem *itemName = new QStandardItem;
    itemName->setText(name);
    itemName->setTextAlignment(Qt::AlignCenter);
    
    QStandardItem *itemScore = new QStandardItem;
    itemScore->setText(QString::number(score, 10));
    itemScore->setTextAlignment(Qt::AlignCenter);
    
    QList<QStandardItem*> items;
    items << itemName << itemScore;
    
    m_model->appendRow(items);
    m_dialog->tableView->setModel(m_model);
}

void CGameOverDialog::setWinner(const QString &name)
{
    QString str = m_dialog->label->text();
    str += name;
    m_dialog->label->setText(str);
}


void CGameOverDialog::initTableView()
{
    m_model = new QStandardItemModel();
    m_dialog->tableView->setModel(m_model);
    
    m_model->setColumnCount(2);
    m_model->setHeaderData(0,Qt::Horizontal,"name");
    m_model->setHeaderData(1,Qt::Horizontal,"score");    
}










