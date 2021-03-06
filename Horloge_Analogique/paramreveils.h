#ifndef PARAMREVEILS_H
#define PARAMREVEILS_H

#include <QDialog>
#include <QList>
#include <QDialogButtonBox>

#include "reveilwidget.h"

namespace Ui {
class ParamReveils;
}
/**
 * @brief The ParamReveils class
 */
class ParamReveils : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief ParamReveils
     * @param parent
     */
    explicit ParamReveils(QWidget *parent = 0);

    /**
     * @brief ParamReveils
     * @param numberOReveil
     * @param parent
     */
    explicit ParamReveils(int numberOReveil, QWidget *parent = 0);

    ~ParamReveils();

    /**
     * @brief reveilsActif
     * @param index
     * @return
     */
    bool reveilsActif(int index);

private:
    Ui::ParamReveils *ui;

    /**
     * @brief m_settings
     */
    QSettings *m_settings;

    /**
     * @brief m_listeReveils
     */
    QList<ReveilWidget*> m_listeReveils;

private slots:
    /**
     * @brief confirmeSettings
     */
    void confirmeSettings();

    /**
     * @brief confirmeToutSettings
     */
    void confirmeToutSettings();

    /**
     * @brief supprimerReveil
     * @param index
     */
    void supprimerReveil(int index);
};

#endif // PARAMREVEILS_H
