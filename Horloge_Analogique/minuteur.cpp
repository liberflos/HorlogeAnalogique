#include "minuteur.h"
#include "ui_minuteur.h"
#include "mainwindow.h"

Minuteur::Minuteur(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Minuteur)
{
    ui->setupUi(this);
    connect(ui->showHideButton, SIGNAL(clicked(bool)), this, SLOT(hideAndShow(bool)));
    connect(ui->quitButton, SIGNAL(clicked(bool)), this, SLOT(quitter()));
}

Minuteur::~Minuteur()
{
    delete ui;
}

void Minuteur::setIndex(int index)
{
    m_index = index;
}

int Minuteur::getIndex()
{
    return m_index;
}

void Minuteur::deplacer(int index)
{
    this->setGeometry(this->x(),this->y() - this->height(),this->width(),this->height());

}

void Minuteur::redessiner()
{
    this->setGeometry(((QMainWindow*)parent())->width() - this->width(),this->y() ,this->width(),this->height());
}

void Minuteur::hideAndShow(bool)
{
    if(ui->showHideButton->arrowType() == Qt::RightArrow){
//        this->setGeometry(this->width() - minuteur->width(),ui->menuBar->height() + (m_nbMinuteurs*minuteur->height()),minuteur->width(),minuteur->height());
        this->setGeometry(this->x() + this->width() - ui->showHideButton->width(),this->y(),this->width(),this->height());
        ui->showHideButton->setArrowType(Qt::LeftArrow);
    }else if(ui->showHideButton->arrowType() == Qt::LeftArrow){
        this->setGeometry(ui->showHideButton->width() + this->x() - this->width(),this->y(),this->width(),this->height());
        ui->showHideButton->setArrowType(Qt::RightArrow);
    }
}

void Minuteur::quitter()
{
    emit closeSigM(m_index);
    close();
}
