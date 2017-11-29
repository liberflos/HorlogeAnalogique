#ifndef REVEIL_H
#define REVEIL_H

#include <QDialog>
#include <QMediaPlayer>
#include <QTimer>
#include <QSettings>
#include <QFileDialog>

#define PATH_AUDIO "PathAudio"
#define HEURE_REVEILS "HeureReveils"
namespace Ui {
class Reveil;
}
/**
 * @brief The Reveil class
 */
class Reveil : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Reveil
     * @param parent
     */
    explicit Reveil(QWidget *parent = 0);
    ~Reveil();

private:
    Ui::Reveil *ui;
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
private slots:
    /**
     * @brief checkTheState
     */
    void checkTheState();
    /**
     * @brief lancerSonnerie
     */
    void lancerSonnerie();
    /**
     * @brief confirmeSettings
     */
    void confirmeSettings();
    /**
     * @brief selectSonnerie
     */
    void selectSonnerie();
};

#endif // REVEIL_H
