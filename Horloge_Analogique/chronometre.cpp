#include "chronometre.h"
#include "ui_chronometre.h"

Chronometre::Chronometre(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chronometre)
{
    ui->setupUi(this);
    connect(ui->showHideButton, SIGNAL(clicked(bool)), this, SLOT(hideAndShow(bool)));
    connect(ui->quitButton, SIGNAL(clicked(bool)), this, SLOT(close()));
}

Chronometre::~Chronometre()
{
    delete ui;
}

void Chronometre::hideAndShow(bool)
{
    if(ui->showHideButton->arrowType() == Qt::LeftArrow){
        this->setGeometry(ui->showHideButton->width() - this->width(),this->y(),this->width(),this->height());
        ui->showHideButton->setArrowType(Qt::RightArrow);

    }else if(ui->showHideButton->arrowType() == Qt::RightArrow){
        this->setGeometry(0,this->y(),this->width(),this->height());
        ui->showHideButton->setArrowType(Qt::LeftArrow);

    }
}

