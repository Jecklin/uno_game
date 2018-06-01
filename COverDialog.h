#ifndef COVERDIALOG_H
#define COVERDIALOG_H

#include <QDialog>

namespace Ui {
class COverDialog;
}

class COverDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit COverDialog(QWidget *parent = 0);
    ~COverDialog();
    
    void setBrowser(QString string);
    
private:
    Ui::COverDialog *ui;
};

#endif // COVERDIALOG_H
