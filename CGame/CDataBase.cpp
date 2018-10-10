#include "CDataBase.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>

CDataBase::CDataBase()
    :m_connection()
    ,m_info()
{
    ;
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
    qDebug() << "createDb";
    
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
        
        if (!db.tables().contains("person"))
        {
            qDebug() << "create table person ";
            
            QSqlQuery query(db);
            
            query.prepare("create table person             ("
                          "id      integer                 ,"
                          "name    varchar(20)             ,"
                          "score   integer                  )");
            if (!query.exec())
            {
                qDebug() << query.lastError();
            }
            
            query.prepare("insert into person values(0, 'Lili'         ,0)");
            if (!query.exec())
            {
                qDebug() << query.lastError();
            }
            
            query.prepare("insert into person values(1, 'Jack'         ,0)");
            if (!query.exec())
            {
                qDebug() << query.lastError();
            }
            
            query.prepare("insert into person values(2, 'Anna'         ,0)");
            if (!query.exec())
            {
                qDebug() << query.lastError();
            }
            
            query.prepare("insert into person values(3, 'Tom'         ,0)");
            if (!query.exec())
            {
                qDebug() << query.lastError();
            }
        }
 

        
    }
        


    
    db.close();

}

void CDataBase::updateDb(const QString &name, int score)
{
    qDebug() << "updateDb";
    
    qDebug() << "name:" << name << "score:" << score;
    
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
        
        query.prepare("update person set score = :da where name = :name");
        query.bindValue(":da", score);
        query.bindValue(":name",name);
        if (!query.exec())
        {
            qDebug() << query.lastError();
        }
   
    }
    
    db.close();
    
}

int CDataBase::selectDb(const QString &name)
{
    qDebug() << "selectDb(const QString &name)";
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
        query.prepare("select score from \'person\' where name = :da;");
        query.bindValue(":da",name);
        if (!query.exec())
        {
            qDebug() << query.lastError();
        }

        while (query.next())
        {
            this->m_info.score = query.value("score").toInt();
        }
    }    
    db.close();

    return this->m_info.score;
    
}

//CDataBase::DbInfo& CDataBase::selectDb(int row)
//{
    
//    qDebug() << "selectDb(int row)";
    
//    QSqlDatabase db = QSqlDatabase::database(m_connection); 
//    if (!db.open())
//    {
//        QMessageBox::critical(nullptr
//                              ,QObject::tr("Cannot open database")
//                              ,QObject::tr("Error")
//                              ,QMessageBox::Cancel);
        
//    }
//    else
//    { 
//        QSqlQuery query(db);
//        query.prepare("select name, score from \"person\" where id = (:da)");
//        query.bindValue(":da",row);
//        if (!query.exec())
//        {
//            qDebug() << query.lastError();
//        }   

//        while(query.next())
//        {
//            m_info.name = query.value(0).toString();
//            m_info.score = query.value(1).toInt();
//        }

   
//    }
    
//    db.close();
   
//    return m_info;
    
//}

CDataBase::DbInfos* CDataBase::getInfos()
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
        query.prepare("select * from \"person\"");
        if (!query.exec())
        {
            qDebug() << query.lastError();
        }   

        while(query.next())
        {
            DbInfo info;
            info.name = query.value(0).toString();
            info.score = query.value(1).toInt();
            m_infos->push_back(info);
        }

   
    }
    
    db.close();
    
    return m_infos;
}








