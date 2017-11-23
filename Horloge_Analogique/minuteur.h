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
    void setIndex(int index);
    void deplacer(int index);
    void redessiner();
signals:
    void closeSig(int index);
private:
    Ui::Minuteur *ui;
    int m_index;
private slots:
    void hideAndShow(bool);
    void quitter();
};

#endif // MINUTEUR_H
