#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <QDialog>
#include <QSettings>

#define TYPE_HORLOGE "TypeHorloge"
#define TAILLE_TEXTE"TailleTexte"

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
    QSettings *m_settings;
    int m_typeHorlogeTMP;
    int m_formeAiguilleTMP;
    int m_typeDeFondTMP;
    int m_couleurHeureTMP;
    int m_couleurMinuteTMP;
    int m_couleurSecondeTMP;
    int m_couleurTexteTMP;
    int m_transparenceTMP;
private slots:
    void setTypeHorloge(int type);
    void confirmeSettings();
};

#endif // AFFICHAGE_H
