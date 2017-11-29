#include "reveil.h"
#include "ui_reveil.h"
#include <QDebug>

Reveil::Reveil(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Reveil)
{
    ui->setupUi(this);
    connect(ui->checkBox_8, SIGNAL(stateChanged(int)), this, SLOT(checkTheState()));
    this->setMinimumWidth(ui->horizontalLayout_2->minimumSize().width() + 20);
    m_timer = new QTimer(this);
    m_timer->setInterval(10000);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(lancerSonnerie()));
}

Reveil::~Reveil()
{
    delete ui;
}

void Reveil::checkTheState()
{
    if(ui->checkBox_8->checkState() == Qt::PartiallyChecked ||ui->checkBox_8->checkState() == Qt::Unchecked){
        ui->spinBox->setDisabled(true);
    }else{
        ui->spinBox->setEnabled(true);
    }

}

void Reveil::lancerSonnerie()
{
    m_player = new QMediaPlayer(this);
//        connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    m_player->setMedia(QUrl::fromLocalFile("/home/turwolf/Téléchargements/alarm-clock-01.mp3"));
    m_player->setVolume(50);
    m_player->play();
}
