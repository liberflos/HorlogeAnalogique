#ifndef THEME_H
#define THEME_H

#include <QDialog>

namespace Ui {
class Theme;
}
/**
 * @brief The Theme class
 */
class Theme : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Theme
     * @param parent
     */
    explicit Theme(QWidget *parent = 0);
    ~Theme();

private:
    Ui::Theme *ui;
};

#endif // THEME_H
