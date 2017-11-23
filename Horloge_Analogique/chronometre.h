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
    void setIndex(int index);
signals:
    void closeSig(int index);
private:
    Ui::Chronometre *ui;
    int m_index;
private slots:
    void hideAndShow(bool);
    void quitter();
};

#endif // CHRONOMETRE_H
