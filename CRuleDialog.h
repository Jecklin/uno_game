#pragma once

#include <QDialog>

namespace Ui {
class CRuleDialog;
}

class CRuleDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit CRuleDialog(QWidget *parent = 0);
    ~CRuleDialog();
    
    
private slots:
    void    onCombox(int current);
    
private:
    Ui::CRuleDialog *ui;
};

