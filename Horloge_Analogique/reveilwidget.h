#ifndef REVEILWIDGET_H
#define REVEILWIDGET_H

#include <QDialog>
#include <QMediaPlayer>
#include <QTimer>
#include <QSettings>
#include <QFileDialog>
#include <QErrorMessage>
#include <QWidget>
#include <QTime>

#include "reveilmodel.h"

namespace Ui {
class ReveilWidget;
}
/**
 * @brief The ReveilWidget class
 */
class ReveilWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief ReveilWidget
     */
    explicit ReveilWidget(QWidget *parent = 0);
    ~ReveilWidget();
    QString getFilePath();
    QTime getTemps();
private:
    Ui::ReveilWidget *ui;
    /**
     * @brief m_settings
     */
    QSettings *m_settings;
    QString m_filePath;
    QTime m_temps;
private slots:
    /**
     * @brief selectSonnerie
     */
    void selectSonnerie();
    /**
     * @brief checkTheState
     */
    void checkTheState();
    void setTemps(QTime temps);
};

#endif // REVEILWIDGET_H
