#include "reveil.h"
#include "ui_reveil.h"

Reveil::Reveil(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Reveil)
{
    ui->setupUi(this);
}

Reveil::~Reveil()
{
    delete ui;
}
