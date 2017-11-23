#ifndef MINUTEUR_H
#define MINUTEUR_H

#include <QWidget>

namespace Ui {
class Minuteur;
}

class Minuteur : public QWidget
{
    Q_OBJECT

public:
    explicit Minuteur(QWidget *parent = 0);
    ~Minuteur();

private:
    Ui::Minuteur *ui;
};

#endif // MINUTEUR_H
