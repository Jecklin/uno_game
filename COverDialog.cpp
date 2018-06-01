#include "COverDialog.h"
#include "ui_COverDialog.h"

COverDialog::COverDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::COverDialog)
{
    ui->setupUi(this);
}

COverDialog::~COverDialog()
{
    delete ui;
}

void COverDialog::setBrowser(QString string)
{
    this->ui->m_textBrowser->setText(string);
}
