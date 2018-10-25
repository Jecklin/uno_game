#pragma once
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

class CDataBase
{
public:
    CDataBase();
    ~CDataBase();
    
    struct DbInfo
    {
        QString name;
        int     score;
    };  
    
    typedef QList<DbInfo> DbInfos;
    
public:
    void            CreateDb();
    void            updateDb(const QString &name, int score);
    int             selectDb(const QString &name);
    
    DbInfos*        getInfos();

    
private:
    QString             m_connection;       //数据库链接
    DbInfo              m_info;             //字段
    DbInfos             *m_infos;
};


