#ifndef REVEIL_H
#define REVEIL_H

#include <QDialog>

namespace Ui {
class Reveil;
}

class Reveil : public QDialog
{
    Q_OBJECT

public:
    explicit Reveil(QWidget *parent = 0);
    ~Reveil();

private:
    Ui::Reveil *ui;
};

#endif // REVEIL_H
