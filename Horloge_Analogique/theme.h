#ifndef THEME_H
#define THEME_H

#include <QDialog>
#include <QSettings>

#define STYLE_HORLOGE "StyleHorloge"
#define THEME_HORLOGE "ThemeHorloge"
#define TYPE_CHRONO "TypeChrono"
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
    QSettings *m_settings;
private slots:
    /**
     * @brief confirmeSettings
     */
    void confirmeSettings();
};

#endif // THEME_H
