#ifndef CHRONOMETRE_H
#define CHRONOMETRE_H

#include <QWidget>

namespace Ui {
class Chronometre;
}

class Chronometre : public QWidget
{
    Q_OBJECT

public:
    explicit Chronometre(QWidget *parent = 0);
    ~Chronometre();

private:
    Ui::Chronometre *ui;
private slots:
    void hideAndShow(bool);
};

#endif // CHRONOMETRE_H
