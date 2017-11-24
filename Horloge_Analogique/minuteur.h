#ifndef MINUTEUR_H
#define MINUTEUR_H

#include <QWidget>

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
private slots:
    /**
     * @brief hideAndShow
     */
    void hideAndShow(bool);
    /**
     * @brief quitter
     */
    void quitter();
};

#endif // MINUTEUR_H
