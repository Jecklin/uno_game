#ifndef CDATABASE_H
#define CDATABASE_H
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
    
public:
    void        createDb();
    void        updateDb(const QString &name, int score);
    int         selectDb(const QString &name);
    DbInfo&     selectDb(int row);
    
private:
    QString             m_connection;       //数据库链接
    DbInfo              m_info;             //字段
};

#endif // CDATABASE_H
