#include "CGameOverDialog.h"
#include "ui_CGameOverDialog.h"
#include <QStandardItemModel>
#include <QHeaderView>
#include <QFont>
#include <QDebug>

CGameOverDialog::CGameOverDialog(QWidget *parent) :
    QDialog(parent),
    m_dialog(new Ui::CGameOverDialog)
{
    m_dialog->setupUi(this);
    
    this->initTableView();
}

void CGameOverDialog::initTableView()
{
    this->m_data_model = new QStandardItemModel();
    this->m_dialog->tableView->setModel(m_data_model);
    
    m_data_model->setColumnCount(2);
    m_data_model->setHeaderData(0, Qt::Horizontal, "name");
    m_data_model->setHeaderData(1, Qt::Horizontal, "score");
}

CGameOverDialog::~CGameOverDialog()
{
    if (this->m_data_model == nullptr)
    {
        ;
    }
    else
    {
        delete this->m_data_model;
        this->m_data_model = nullptr;
    }
    
    if (this->m_dialog == nullptr)
    {
        ;
    }
    else
    {
        delete this->m_dialog;
        this->m_dialog = nullptr;
    }
    
}


bool CGameOverDialog::createDb()
{
    bool success = false;
    this->m_db = QSqlDatabase::addDatabase("QSQLITE");
    this->m_db.setDatabaseName("DbPlayerScores.db");
    if (!m_db.open())
    {
        QMessageBox::critical(nullptr
                              ,QObject::tr("Cannot open database")
                              ,QObject::tr("error")
                              ,QMessageBox::Cancel);
        
    }
    else
    {
        QSqlQuery query;
        if (m_db.contains())
        {
            query.exec("drop table person");
        }
        else
        {
            ;
        }
     
        query.exec("create table person("
                   "name varchar(20),"
                   "score int)");
        query.exec("insert into person values('Lili', 0)");
        query.exec("insert into person values('Jack', 0)");
        query.exec("insert into person values('Anna', 0)");
        query.exec("insert into person values('Tom', 0)");
                

        success = true;
    }
    
    this->m_db.close();
    
    return success;
}

bool CGameOverDialog::updateDb(const QString &name, int score)
{
    bool success = false;
    this->m_db = QSqlDatabase::addDatabase("QSQLITE");
    this->m_db.setDatabaseName("DbPlayerScores.db");
    if (!m_db.open())
    {
        QMessageBox::critical(nullptr
                              ,QObject::tr("Cannot open database")
                              ,QObject::tr("error")
                              ,QMessageBox::Cancel);
    }
    else
    {
        
        QSqlQuery query;
        
        if ("Lili" == name)
        {
            int index = query.exec("select score from person where name = 'Lili'");
            index += score;
            query.prepare("update person set score = (:da) where name = 'Lili'");
            query.bindValue(":da",index);
            query.exec();
        }
        else if ("Jack" == name)
        {
            int index = query.exec("select score from person where name = 'Jack'");
            index += score;
            query.prepare("update person set score = (:da) where name = 'Jack'");
            query.bindValue(":da",index);
            query.exec();
        }
        else if ("Anna" == name)
        {
            int index = query.exec("select score from person where name = 'Anna'");
            index += score;
            query.prepare("update person set score = (:da) where name = 'Anna'");
            query.bindValue(":da",index);
            query.exec();
        }
        else if ("Tom" == name)
        {
            int index = query.exec("select score from person where name = 'Tom'");
            index += score;
            query.prepare("update person set score = (:da) where name = 'Tom'");
            query.bindValue(":da",index);
            query.exec();
        }
        else
        {
            ;
        }

        success = true;
    }
    
    this->m_db.close();
    
    return success;
}

bool CGameOverDialog::selectDb()
{
    this->m_db = QSqlDatabase::addDatabase("QSQLITE");
    this->m_db.setDatabaseName("DbPlayerScores.db");
    if (!m_db.open())
    {
        QMessageBox::critical(nullptr
                              ,QObject::tr("Cannot open database")
                              ,QObject::tr("error")
                              ,QMessageBox::Cancel);
        
    }
    else
    {
        QSqlQuery       query;
        QString         name;
        int             score;
        QStandardItem   *itemName;
        QStandardItem   *itemScore;
        int             index = 0;
        query.exec("select name, score from person");
    
        while (query.next())
        {
            name        = query.value(0).toString();
            score       = query.value(1).toInt();
            
            itemName    = new QStandardItem;
            itemName->setData(name, 0);
            itemScore   = new QStandardItem;
            itemScore->setData(score, 0);
            
            m_data_model->setItem(index, 0, itemName);
            m_data_model->setItem(index, 1, itemScore);
            
            m_data_model->item(index, 1)->setTextAlignment(Qt::AlignCenter);
            m_data_model->item(index, 1)->setForeground(QBrush(QColor(255, 0, 0)));
            
            index++;
        }
    }
    
    
    this->m_db.close();
    

    return true;
}









