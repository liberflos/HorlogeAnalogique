#include "reveil.h"
#include "ui_reveil.h"
#include <QDebug>

Reveil::Reveil(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Reveil)
{
    ui->setupUi(this);
    connect(ui->checkBox_8, SIGNAL(stateChanged(int)), this, SLOT(checkTheState()));
    this->setMinimumWidth(ui->horizontalLayout_2->minimumSize().width() + 20);
}

Reveil::~Reveil()
{
    delete ui;
}

void Reveil::checkTheState()
{
    if(ui->checkBox_8->checkState() == Qt::PartiallyChecked ||ui->checkBox_8->checkState() == Qt::Unchecked){
        ui->spinBox->setDisabled(true);
    }else{
        ui->spinBox->setEnabled(true);
    }

}
