#include "CBeginDialog.h"
#include "ui_CBeginDialog.h"
#include "CRuleDialog.h"

CBeginDialog::CBeginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CBeginDialog)
{
    ui->setupUi(this);
    
    connect(ui->beginButton,SIGNAL(clicked(bool)),this,SLOT(accept()));
    connect(ui->exitButton,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(ui->ruleButton,SIGNAL(clicked(bool)),this,SLOT(onRule()));
}

CBeginDialog::~CBeginDialog()
{
    delete ui;
}

void CBeginDialog::onStart()
{
    emit sStart();
}

void CBeginDialog::onHistory()
{
    
}

void CBeginDialog::onRule()
{
    CRuleDialog dialog;
    dialog.exec();
}

void CBeginDialog::onExit()
{
    
}
