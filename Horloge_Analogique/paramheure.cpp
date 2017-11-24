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
    connect(ui->buttonBox,SIGNAL(accepted()),this, SLOT(accept()));
    connect(ui->buttonBox,SIGNAL(rejected()),this, SLOT(reject()));
}

ParamHeure::~ParamHeure()
{
    delete ui;
}
