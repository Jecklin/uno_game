#ifndef CGAMEOVERDIALOG_H
#define CGAMEOVERDIALOG_H

#include <QDialog>

namespace Ui {
class CGameOverDialog;
}

class CGameOverDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit CGameOverDialog(QWidget *parent = 0);
    ~CGameOverDialog();
    
    void    setTextBrowser(QString texts);
    
private:
    Ui::CGameOverDialog *ui;
};

#endif // CGAMEOVERDIALOG_H
