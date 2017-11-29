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

class Reveil : public QDialog
{
    Q_OBJECT

public:
    explicit Reveil(QWidget *parent = 0);
    ~Reveil();

private:
    Ui::Reveil *ui;
    QMediaPlayer *m_player;
    QTimer *m_timer;
    QSettings *m_settings;
private slots:
    void checkTheState();
    void lancerSonnerie();
    void confirmeSettings();
    void selectSonnerie();
};

#endif // REVEIL_H
