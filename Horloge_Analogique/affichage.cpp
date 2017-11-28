#include "affichage.h"
#include "ui_affichage.h"
#include <QSettings>
#include <QDebug>

Affichage::Affichage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Affichage)
{
    ui->setupUi(this);
    connect(ui->buttonBox,SIGNAL(accepted()),this, SLOT(accept()));
    connect(ui->buttonBox,SIGNAL(rejected()),this, SLOT(reject()));
    ui->comboBoxTypeHorloge->addItem("Analogique");
    ui->comboBoxTypeHorloge->addItem("Numerique");
    ui->comboBoxTypeHorloge->setCurrentIndex(m_settings.value("TypeHorloge", 0).toInt());
    connect(ui->comboBoxTypeHorloge, SIGNAL(activated(int)), this, SLOT(setTypeHorloge(int)));
}

Affichage::~Affichage()
{
    delete ui;
}

void Affichage::setTypeHorloge(int type)
{
        m_settings.setValue("TypeHorloge", type);
}
