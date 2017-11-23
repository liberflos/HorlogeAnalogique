#ifndef PARAMHEURE_H
#define PARAMHEURE_H

#include <QDialog>
#include <QFormLayout>

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
};

#endif // PARAMHEURE_H
