#include "CDataBase.h"
#include <QMessageBox>
#include <QDebug>

CDataBase::CDataBase()
    :m_connection("connect")
    ,m_info()
{
    this->createDb();
}

CDataBase::~CDataBase()
{
    QSqlDatabase db = QSqlDatabase::database(m_connection);
    if (db.isOpen())
    {
        db.close();
    }
    else
    {
        ;
    }
    
    if (db.contains())
    {
        db.removeDatabase(m_connection);
    }
    else
    {
        ;
    }
    
}

void CDataBase::createDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", m_connection);
    db.setHostName("players");
    db.setDatabaseName("DB_records");
    db.setUserName("111");
    db.setPassword("111");
    if (!db.open())
    {
        QMessageBox::critical(nullptr
                              ,QObject::tr("Cannot open database")
                              ,QObject::tr("Error")
                              ,QMessageBox::Cancel);
    }
    else
    {
        QSqlQuery query(db);
        
        //here should be changed to  Zero in every round
        if (db.contains(m_connection))
        {
//            query.exec("drop table person");
        }
        else
        {
            query.exec("create table person             ("
                       "id      int                     ,"
                       "name    varchar(20)             ,"
                       "score   int                     )");
            query.exec("insert into person values(0, 'Lili'         ,0)");
            query.exec("insert into person values(1, 'Jack'         ,0)");
            query.exec("insert into person values(2, 'Anna'         ,0)");
            query.exec("insert into person values(3, 'Tom'          ,0)");
        }
        

    }
    
    db.close();

}

void CDataBase::updateDb(const QString &name, int score)
{
    QSqlDatabase db = QSqlDatabase::database(m_connection);
    
    if (!db.open())
    {
        QMessageBox::critical(nullptr
                              ,QObject::tr("Cannot open database")
                              ,QObject::tr("Error")
                              ,QMessageBox::Cancel);
        
    }
    else
    {        
        QSqlQuery query(db);
        
        query.prepare("update person set score = (:da) where name = (:name)");
        query.bindValue(":da", score);
        query.bindValue(":name",name);
        query.exec();
   
    }
    
    db.close();
    
}

int CDataBase::selectDb(const QString &name)
{
    QSqlDatabase db = QSqlDatabase::database(m_connection); 
    if (!db.open())
    {
        QMessageBox::critical(nullptr
                              ,QObject::tr("Cannot open database")
                              ,QObject::tr("Error")
                              ,QMessageBox::Cancel);
        
    }
    else
    { 
        QSqlQuery   query(db);
        query.prepare("select score from \"person\" where name = (:da)");
        query.bindValue(":da",name);
        query.exec(); 

        while (query.next())
        {
            this->m_info.score = query.value("score").toInt();
        }
    }
    
    db.close();

    return this->m_info.score;
    
}

CDataBase::DbInfo& CDataBase::selectDb(int row)
{
    QSqlDatabase db = QSqlDatabase::database(m_connection); 
    if (!db.open())
    {
        QMessageBox::critical(nullptr
                              ,QObject::tr("Cannot open database")
                              ,QObject::tr("Error")
                              ,QMessageBox::Cancel);
        
    }
    else
    { 
        QSqlQuery query(db);
        query.prepare("select name, score from \"person\" where id = (:da)");
        query.bindValue(":da",row);
        query.exec();    

        while(query.next())
        {
            m_info.name = query.value(0).toString();
            m_info.score = query.value(1).toInt();
        }

   
    }
    
    db.close();
   
    return m_info;

}






