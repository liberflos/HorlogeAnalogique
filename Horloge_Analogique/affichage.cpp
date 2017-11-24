#include "affichage.h"
#include "ui_affichage.h"

Affichage::Affichage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Affichage)
{
    ui->setupUi(this);
    connect(ui->buttonBox,SIGNAL(accepted()),this, SLOT(accept()));
    connect(ui->buttonBox,SIGNAL(rejected()),this, SLOT(reject()));
}

Affichage::~Affichage()
{
    delete ui;
}
