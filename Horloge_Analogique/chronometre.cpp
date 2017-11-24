#include "chronometre.h"
#include "ui_chronometre.h"
#include "mainwindow.h"

Chronometre::Chronometre(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chronometre)
{
    ui->setupUi(this);
    m_h = 0;
    m_m = 0;
    m_s = 0;
    m_ms = 0;
    m_timer = new QTimer(this);
    m_temps.setHMS(m_h,m_m,m_s,m_ms);
    m_timer->setInterval(10);
    connect(ui->showHideButton, SIGNAL(clicked(bool)), this, SLOT(hideAndShow(bool)));
    connect(ui->quitButton, SIGNAL(clicked(bool)), this, SLOT(quitter()));
    connect(ui->startButton, SIGNAL(clicked(bool)), m_timer, SLOT(start()));
    connect(ui->stopButton, SIGNAL(clicked(bool)), m_timer, SLOT(stop()));
    connect(m_timer, SIGNAL(timeout()), this, SLOT(startChrono()));
    connect(ui->resetButton, SIGNAL(clicked(bool)), this, SLOT(resetChrono()));
}

Chronometre::~Chronometre()
{
    delete ui;
}

void Chronometre::setIndex(int index)
{
    m_index = index;
}

void Chronometre::deplacer()
{
    this->setGeometry(this->x(),this->y() - this->height(),this->width(),this->height());
}

void Chronometre::redessiner()
{
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

void Chronometre::quitter()
{
    emit closeSigC(m_index);
    close();
}

void Chronometre::startChrono()
{

    m_ms+= 10;
    if(m_ms == 1000){
        if(m_s == 59){
            if(m_m == 59){
                m_h++;
                m_m = 0;
            }
            m_m++;
            m_s = 0;
        }
        m_s++;
        m_ms = 0;
    }
    m_temps.setHMS(m_h,m_m,m_s,m_ms);
    ui->timeEdit->setTime(m_temps);
}

void Chronometre::resetChrono()
{
    m_h = 0;
    m_m = 0;
    m_s = 0;
    m_ms = 0;
    m_temps.setHMS(m_h,m_m,m_s,m_ms);
    ui->timeEdit->setTime(m_temps);

}

