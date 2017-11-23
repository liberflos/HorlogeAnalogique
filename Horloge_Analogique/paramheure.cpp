#include "paramheure.h"
#include "ui_paramheure.h"

ParamHeure::ParamHeure(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParamHeure)
{
    ui->setupUi(this);
    ui->comboBox->addItem("Allemand");
    ui->comboBox->addItem("Anglais");
    ui->comboBox->addItem("Espagnol");
    ui->comboBox->addItem("Français");
    ui->comboBox->addItem("Italien");
}

ParamHeure::~ParamHeure()
{
    delete ui;
}
