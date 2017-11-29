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
    explicit ParamReveils(int numberOReveil, QWidget *parent = 0);
    ~ParamReveils();

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
    void confirmeToutSettings();
};

#endif // PARAMREVEILS_H
