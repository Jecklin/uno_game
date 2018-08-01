#ifndef CBEGINDIALOG_H
#define CBEGINDIALOG_H

#include <QDialog>

namespace Ui {
class CBeginDialog;
}

class CBeginDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit CBeginDialog(QWidget *parent = 0);
    ~CBeginDialog();
    
signals:
    void    sStart();
    void    sHistory();
    void    sClear();
    void    sExit();
    
private slots:
    void    onStart();
    void    onHistory();
    void    onClear();
    void    onExit();
    
private:
    Ui::CBeginDialog *ui;
};

#endif // CBEGINDIALOG_H
