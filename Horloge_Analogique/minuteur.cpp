#include "minuteur.h"
#include "ui_minuteur.h"
#include "mainwindow.h"

Minuteur::Minuteur(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Minuteur)
{
    ui->setupUi(this);
    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    ui->stopButton->setDisabled(true);
    connect(ui->showHideButton, SIGNAL(clicked(bool)), this, SLOT(hideAndShow(bool)));
    connect(ui->quitButton, SIGNAL(clicked(bool)), this, SLOT(quitter()));
    connect(ui->startButton, SIGNAL(clicked(bool)), this,SLOT(startMTimer()));
    connect(ui->stopButton, SIGNAL(clicked(bool)), this, SLOT(stopMTimer()));
    connect(m_timer, SIGNAL(timeout()), this, SLOT(incremente()));
    connect(ui->timeEdit, SIGNAL(timeChanged(QTime)), this, SLOT(updateTime()));
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

void Minuteur::deplacer()
{
    this->setGeometry(this->x(),this->y() - this->height(),this->width(),this->height());

}

void Minuteur::redessiner()
{
    if(ui->showHideButton->arrowType() == Qt::RightArrow){
        this->setGeometry(((QMainWindow*)parent())->width() - this->width(),this->y() ,this->width(),this->height());
    }else if(ui->showHideButton->arrowType() == Qt::LeftArrow){
        this->setGeometry(((QMainWindow*)parent())->width() - ui->showHideButton->width(),this->y() ,this->width(),this->height());
    }
}

void Minuteur::updateTime()
{
    m_s = ui->timeEdit->time().second();
    m_m = ui->timeEdit->time().minute();
    m_h = ui->timeEdit->time().hour();
}

void Minuteur::incremente()
{
        if(m_s == 0){
            if(m_m == 0){
                m_h--;
                m_m = 60;
            }
            m_m--;
            m_s = 60;
        }
        m_s--;
    m_temps.setHMS(m_h,m_m,m_s);
    ui->timeEdit->setTime(m_temps);
    if(m_s == 0 && m_m == 0 && m_h == 0){
        m_timer->stop();
        //ATTENTION LE FICHIER UTILISÉ ICI N'EST PAS INTÉGRÉ AU PROJET
        m_player = new QMediaPlayer(this);
//        connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
        m_player->setMedia(QUrl::fromLocalFile("/home/turwolf/Téléchargements/alarm-clock-01.mp3"));
        m_player->setVolume(50);
        m_player->play();
    }
}

void Minuteur::hideAndShow(bool)
{
    if(ui->showHideButton->arrowType() == Qt::RightArrow){
        ui->showHideButton->setArrowType(Qt::LeftArrow);
    }else if(ui->showHideButton->arrowType() == Qt::LeftArrow){
        ui->showHideButton->setArrowType(Qt::RightArrow);
    }
}

void Minuteur::quitter()
{
    emit closeSigM(m_index);
    close();
}

void Minuteur::startMTimer()
{
    m_timer->start();
    ui->timeEdit->setReadOnly(true);
    ui->startButton->setDisabled(true);
    ui->stopButton->setEnabled(true);
}

void Minuteur::stopMTimer()
{
    if(m_timer->isActive()){
        m_timer->stop();
    }
    else{
        m_player->stop();
    }
    ui->timeEdit->setReadOnly(false);
    ui->startButton->setEnabled(true);
    ui->stopButton->setDisabled(true);
}
