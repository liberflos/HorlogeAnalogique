#include "reveilmodel.h"

ReveilModel::ReveilModel(QWidget *parent) : QWidget(parent)
{
}

ReveilModel::ReveilModel(QString temps,QString nomFichierAudio, QWidget *parent)
{
    m_timer = new QTimer(this);
    m_temps = temps;
    m_nomFichierAudio = nomFichierAudio;
    connect(m_timer, SIGNAL(timeout()), this, SLOT(lancerSonnerie()));
    long delai = ((QTime::fromString(m_temps).hour()*3600 + QTime::fromString(m_temps).minute()*60) -
                  (QTime::currentTime().hour()*3600 + QTime::currentTime().minute()*60 +
                   QTime::currentTime().second()))*1000 - QTime::currentTime().msec();
    if(delai<=0){
        delai += 24*3600000;
    }
        m_timer->start(delai);
}

void ReveilModel::setTime(int time)
{
    m_timer->setInterval(time);
}

void ReveilModel::lancerSonnerie()
{
        m_player = new QMediaPlayer(this);
        m_player->setAudioRole(QAudio::AlarmRole);
        m_player->setMedia(QUrl::fromLocalFile(m_nomFichierAudio));
        m_player->setVolume(50);
        m_player->play();
        connect(m_player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(lancerSonnerie()));
}
