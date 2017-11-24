#ifndef MINUTEUR_H
#define MINUTEUR_H

#include <QWidget>
#include <QTime>
#include <QTimer>
#include <QAudioOutput>
#include <QAudioFormat>
#include <QAudioDeviceInfo>

namespace Ui {
class Minuteur;
}
/**
 * @brief The Minuteur class
 */
class Minuteur : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Minuteur
     * @param parent
     */
    explicit Minuteur(QWidget *parent = 0);
    ~Minuteur();
    /**
     * @brief setIndex
     * @param index
     */
    void setIndex(int index);
    /**
     * @brief getIndex
     * @return
     */
    int getIndex();
    /**
     * @brief deplacer
     */
    void deplacer();
    /**
     * @brief redessiner
     */
    void redessiner();
signals:
    /**
     * @brief closeSigM
     * @param index
     */
    void closeSigM(int index);
private:
    Ui::Minuteur *ui;
    /**
     * @brief m_index
     */
    int m_index;
    /**
     * @brief m_s
     */
    int m_s;
    /**
     * @brief m_m
     */
    int m_m;
    /**
     * @brief m_h
     */
    int m_h;
    /**
     * @brief m_timer
     */
    QTimer *m_timer;
    QTime m_temps;
private slots:
    /**
     * @brief updateTime
     */
    void updateTime();
    /**
     * @brief incremente
     */
    void incremente();
    /**
     * @brief hideAndShow
     */
    void hideAndShow(bool);
    /**
     * @brief quitter
     */
    void quitter();
    void startMTimer();
    void stopMTimer();
};

#endif // MINUTEUR_H
