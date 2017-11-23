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
private slots:
    void hideAndShow(bool);
};

#endif // MINUTEUR_H
