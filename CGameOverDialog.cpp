#include "CGameOverDialog.h"
#include "ui_CGameOverDialog.h"

CGameOverDialog::CGameOverDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CGameOverDialog)
{
    ui->setupUi(this);
}

CGameOverDialog::~CGameOverDialog()
{
    delete ui;
}

void CGameOverDialog::setTextBrowser(QString texts)
{
    this->ui->textBrowser->setText(texts);
}
