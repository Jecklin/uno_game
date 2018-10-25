#pragma once

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
    void    sRule();
    void    sExit();
    
private slots:
    void    onStart();
    void    onHistory();
    void    onRule();
    void    onExit();
    
private:
    Ui::CBeginDialog *ui;
};

