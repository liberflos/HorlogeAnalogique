#include "paramheure.h"
#include "ui_paramheure.h"

ParamHeure::ParamHeure(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParamHeure)
{
    ui->setupUi(this);
}

ParamHeure::~ParamHeure()
{
    delete ui;
}
