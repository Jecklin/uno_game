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
    void    setTableItem(const QString &name, int score, int row);
    void    setWinner(const QString &name);
    
private:
    void    initTableView();
    
    
private:
    Ui::CGameOverDialog     *m_dialog;
    QStandardItemModel      *m_data_model;
};


#endif // CGAMEOVERDIALOG_H
