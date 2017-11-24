#include "paramreveils.h"
#include "ui_paramreveils.h"

ParamReveils::ParamReveils(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParamReveils)
{
    ui->setupUi(this);
}

ParamReveils::~ParamReveils()
{
    delete ui;
}
