#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <QDialog>

namespace Ui {
class Affichage;
}

class Affichage : public QDialog
{
    Q_OBJECT

public:
    explicit Affichage(QWidget *parent = 0);
    ~Affichage();

private:
    Ui::Affichage *ui;
};

#endif // AFFICHAGE_H
