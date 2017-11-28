#ifndef REVEIL_H
#define REVEIL_H

#include <QDialog>
#include <QMediaPlayer>
#include <QTimer>

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
private slots:
    void checkTheState();
    void lancerSonnerie();
};

#endif // REVEIL_H
