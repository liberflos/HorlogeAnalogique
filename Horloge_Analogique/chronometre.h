#ifndef CHRONOMETRE_H
#define CHRONOMETRE_H

#include <QWidget>
#include <QTimer>
#include <QTime>

namespace Ui {
class Chronometre;
}
/**
 * @brief The Chronometre class
 */
class Chronometre : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Chronometre
     * @param parent
     */
    explicit Chronometre(QWidget *parent = 0);
    ~Chronometre();
    /**
     * @brief setIndex
     * @param index
     */
    void setIndex(int index);
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
     * @brief closeSigC
     * @param index
     */
    void closeSigC(int index);
private:
    Ui::Chronometre *ui;
    /**
     * @brief m_index
     */
    int m_index;
    /**
     * @brief m_temps
     */
    QTime m_temps;
    /**
     * @brief m_timer
     */
    QTimer *m_timer;
    /**
     * @brief m_ms
     */
    int m_ms;
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
private slots:
    /**
     * @brief hideAndShow
     */
    void hideAndShow(bool);
    /**
     * @brief quitter
     */
    void quitter();
    /**
     * @brief startChrono
     */
    void startChrono();
    /**
     * @brief resetChrono
     */
    void resetChrono();
    void incrementChrono();
    void stopChrono();
};

#endif // CHRONOMETRE_H
