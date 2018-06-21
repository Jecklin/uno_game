#ifndef CGAMEOVERDIALOG_H
#define CGAMEOVERDIALOG_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QStandardItemModel>

namespace Ui {
class CGameOverDialog;
}

class CGameOverDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit CGameOverDialog(QWidget *parent = 0);
    ~CGameOverDialog();
    
public:
    bool    createDb();
    bool    updateDb(const QString &name, int score);
    bool    selectDb();

    
private:
    void    initTableView();
    
    
private:
    Ui::CGameOverDialog     *m_dialog;
    QStandardItemModel      *m_data_model;
    QSqlDatabase            m_db;
};






#endif // CGAMEOVERDIALOG_H
