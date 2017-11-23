#include "minuteur.h"
#include "ui_minuteur.h"

Minuteur::Minuteur(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Minuteur)
{
    ui->setupUi(this);
}

Minuteur::~Minuteur()
{
    delete ui;
}
