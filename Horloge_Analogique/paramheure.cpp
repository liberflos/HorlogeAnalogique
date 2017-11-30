#include "paramheure.h"
#include "ui_paramheure.h"

ParamHeure::ParamHeure(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParamHeure)
{
    ui->setupUi(this);
    m_settings = new QSettings("AppliHours", "HorlogeAnalogique");
    ui->comboBox->addItem("Allemand");
    ui->comboBox->addItem("Anglais");
    ui->comboBox->addItem("Espagnol");
    ui->comboBox->addItem("Français");
    ui->comboBox->addItem("Italien");
    switch (m_settings->value(LANGUE, 3).toInt()) {
    case 0:
        ui->comboBox->setCurrentIndex(0);
        break;
    case 1:
        ui->comboBox->setCurrentIndex(1);
        break;
    case 2:
        ui->comboBox->setCurrentIndex(2);
        break;
    case 3:
        ui->comboBox->setCurrentIndex(3);
        break;
    case 4:
        ui->comboBox->setCurrentIndex(4);
        break;
    default:
        ui->comboBox->setCurrentIndex(3);
        break;
    }
    ui->dateEdit->setDate(QDate::currentDate());
    ui->timeEdit->setTime(QTime::currentTime());
    connect(ui->buttonBox,SIGNAL(accepted()),this, SLOT(accept()));
    connect(ui->buttonBox,SIGNAL(rejected()),this, SLOT(reject()));
}

ParamHeure::~ParamHeure()
{
    delete ui;
}
