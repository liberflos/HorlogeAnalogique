#ifndef REVEILMODEL_H
#define REVEILMODEL_H

#include <QObject>
#include <QWidget>
#include <QMediaPlayer>
#include <QSettings>
#include <QTimer>
#include <QTime>

#define PATH_AUDIO "PathAudio"
#define HEURE_REVEILS "HeureReveils"

class ReveilModel : public QWidget
{
    Q_OBJECT
public:
    explicit ReveilModel(QWidget *parent = 0);
    explicit ReveilModel(QString temps, QString nomFichierAudio, QWidget *parent = 0);
    void setTime(int time);
signals:

public slots:
private:
    /**
     * @brief m_player
     */
    QMediaPlayer *m_player;
    /**
     * @brief m_timer
     */
    QTimer *m_timer;
    /**
     * @brief m_settings
     */
    QSettings *m_settings;
    QString m_nomFichierAudio;
    QString m_temps;
private slots:
    /**
     * @brief lancerSonnerie
     */
    void lancerSonnerie();
};

#endif // REVEILMODEL_H
