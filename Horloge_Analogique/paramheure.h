#ifndef PARAMHEURE_H
#define PARAMHEURE_H

#include <QDialog>
#include <QFormLayout>
#include <QSettings>

#define LANGUE "Langue"

namespace Ui {
class ParamHeure;
}

/**
 * @brief The ParamHeure class
 */
class ParamHeure : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief ParamHeure
     * @param parent
     */

    explicit ParamHeure(QWidget *parent = 0);

    ~ParamHeure();

private:
    Ui::ParamHeure *ui;

    /**
     * @brief m_settings
     */
    QSettings *m_settings;
};

#endif // PARAMHEURE_H
