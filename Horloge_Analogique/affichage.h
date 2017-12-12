#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <QDialog>
#include <QSettings>
#include <QFileDialog>
#include <QErrorMessage>
#include <QScreen>

#define TYPE_HORLOGE "TypeHorloge"
#define TAILLE_TEXTE "TailleTexte"
#define FORME_AIGUILLE "FormeAiguille"
#define TYPE_DE_FOND "TypeDeFond"
#define PATH_IMAGE "PathImage"
#define COULEUR_FOND "CouleurFond"
#define COULEUR_HEURE "CouleurHeure"
#define COULEUR_MINUTE "CouleurMinute"
#define COULEUR_SECONDE "CouleurSeconde"
#define COULEUR_TEXTE "CouleurTexte"
#define TRANSPARENCE "Transparence"
#define FORMEAIGUILLE "FormeAiguille"

namespace Ui {
class Affichage;
}
/**
 * @brief The Affichage class
 */
class Affichage : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Affichage
     * @param parent
     */
    explicit Affichage(QWidget *parent = 0);

    ~Affichage();

private:
    Ui::Affichage *ui;
    /**
     * @brief m_settings
     */
    QSettings *m_settings;

    /**
     * @brief m_couleurFondTMP
     */
    unsigned int m_couleurFondTMP;

    /**
     * @brief m_couleurHeureTMP
     */
    int m_couleurHeureTMP;

    /**
     * @brief m_couleurMinuteTMP
     */
    int m_couleurMinuteTMP;

    /**
     * @brief m_couleurSecondeTMP
     */
    int m_couleurSecondeTMP;

    /**
     * @brief m_couleurTexteTMP
     */
    int m_couleurTexteTMP;

    /**
     * @brief m_transparenceTMP
     */
    int m_transparenceTMP;

private slots:
    /**
     * @brief confirmeSettings
     */
    void confirmeSettings();

    /**
     * @brief setTypeFond
     * @param index
     */
    void setTypeFond(int index);

    /**
     * @brief selectImage
     */
    void selectImage();

    /**
     * @brief selectCouleurFond
     */
    void selectCouleurFond();

    /**
     * @brief selectCouleurTexte
     */
    void selectCouleurTexte();

    /**
     * @brief selectCouleurHeure
     */
    void selectCouleurHeure();

    /**
     * @brief selectCouleurMinute
     */
    void selectCouleurMinute();

    /**
     * @brief selectCouleurSeconde
     */
    void selectCouleurSeconde();
};

#endif // AFFICHAGE_H
