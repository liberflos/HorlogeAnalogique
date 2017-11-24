#ifndef PARAMREVEILS_H
#define PARAMREVEILS_H

#include <QDialog>

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
    ~ParamReveils();

private:
    Ui::ParamReveils *ui;
};

#endif // PARAMREVEILS_H
