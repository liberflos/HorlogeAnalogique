#ifndef PARAMREVEILS_H
#define PARAMREVEILS_H

#include <QDialog>

namespace Ui {
class ParamReveils;
}

class ParamReveils : public QDialog
{
    Q_OBJECT

public:
    explicit ParamReveils(QWidget *parent = 0);
    ~ParamReveils();

private:
    Ui::ParamReveils *ui;
};

#endif // PARAMREVEILS_H
