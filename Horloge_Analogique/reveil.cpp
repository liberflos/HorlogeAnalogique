#include "reveil.h"
#include "ui_reveil.h"
#include <QDebug>

Reveil::Reveil(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Reveil)
{
    ui->setupUi(this);
    m_settings = new QSettings("AppliHours", "HorlogeAnalogique");
    ui->timeEdit->setTime(QTime::currentTime());
    ui->lineEditFilePath->setText(m_settings->value(PATH_AUDIO).toString());
    connect(ui->checkBox_8, SIGNAL(stateChanged(int)), this, SLOT(checkTheState()));
    this->setMinimumWidth(ui->horizontalLayout_2->minimumSize().width() + 20);
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(lancerSonnerie()));
    connect(this, SIGNAL(accepted()), this, SLOT(confirmeSettings()));
    connect(ui->toolButtonSelFile, SIGNAL(clicked(bool)), this, SLOT(selectSonnerie()));
    connect(ui->buttonBox,SIGNAL(accepted()),this, SLOT(accept()));
    connect(ui->buttonBox,SIGNAL(rejected()),this, SLOT(reject()));
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
        m_player->setAudioRole(QAudio::AlarmRole);
        m_player->setMedia(QUrl::fromLocalFile(m_settings->value(PATH_AUDIO).toString()));
        m_player->setVolume(50);
        m_player->play();
        connect(m_player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(lancerSonnerie()));
}

void Reveil::confirmeSettings()
{
    m_settings->setValue(PATH_AUDIO, ui->lineEditFilePath->text());
    QList<QVariant> liste;
    liste.append(m_settings->value(HEURE_REVEILS).toList());
    liste.append(ui->timeEdit->time());
    m_settings->setValue(HEURE_REVEILS, liste);

    m_timer->start(((ui->timeEdit->time().hour()*3600 + ui->timeEdit->time().minute()*60) -
                    (QTime::currentTime().hour()*3600 + QTime::currentTime().minute()*60 +
                     QTime::currentTime().second()))*1000 - QTime::currentTime().msec());

}

void Reveil::selectSonnerie()
{
    QFileDialog *dialFichier = new QFileDialog(this);
    QString filePath;
    filePath = dialFichier->getOpenFileName();
//    if(filePath.endsWith(".jpg") || filePath.endsWith(".png") ||
//            filePath.endsWith(".JPEG") || filePath.endsWith(".bmp")){
        ui->lineEditFilePath->setText(filePath);
//    }else {
//        QErrorMessage *message = new QErrorMessage(this);
//        message->setWindowTitle("Erreur d'Extension");
//        message->showMessage("le fichier selectionné n'est pas une image, ou l'extension n'est pas prise en charge.");
//    }
}
