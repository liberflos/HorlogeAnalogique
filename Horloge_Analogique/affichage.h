#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class Affichage;
}
/**
 * @brief The Affichage class
 */
class Affichage : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Affichage
     * @param parent
     */
    explicit Affichage(QWidget *parent = 0);
    ~Affichage();

private:
    Ui::Affichage *ui;
    QSettings m_settings;
private slots:
    void setTypeHorloge(int type);
};

#endif // AFFICHAGE_H
