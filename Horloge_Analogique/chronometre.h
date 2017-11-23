#ifndef CHRONOMETRE_H
#define CHRONOMETRE_H

#include <QWidget>
#include <QTimer>
#include <QTime>

namespace Ui {
class Chronometre;
}

class Chronometre : public QWidget
{
    Q_OBJECT

public:
    explicit Chronometre(QWidget *parent = 0);
    ~Chronometre();
    void setIndex(int index);
    void deplacer(int index);
    void redessiner();
signals:
    void closeSigC(int index);
private:
    Ui::Chronometre *ui;
    int m_index;
    QTime m_temps;
    QTimer *m_timer;
    int m_ms;
    int m_s;
    int m_m;
    int m_h;
private slots:
    void hideAndShow(bool);
    void quitter();
    void startChrono();
    void resetChrono();
};

#endif // CHRONOMETRE_H
