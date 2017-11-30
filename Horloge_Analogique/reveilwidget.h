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

    /**
     * @brief ReveilWidget
     * @param fichierAudio
     * @param parent
     */
    explicit ReveilWidget(QString fichierAudio, QWidget *parent);

    /**
     * @brief ReveilWidget
     * @param temps
     * @param fichierAudio
     * @param parent
     */
    explicit ReveilWidget(QString temps, QString fichierAudio, QWidget *parent = 0);

    ~ReveilWidget();

    /**
     * @brief getFilePath
     * @return
     */
    QString getFilePath();

    /**
     * @brief getTemps
     * @return
     */
    QTime getTemps();

    /**
     * @brief isActif
     * @return
     */
    bool isActif();

signals:
    /**
     * @brief supprimerReveil_SIG
     * @param index
     */
    void supprimerReveil_SIG(int index);

private:
    Ui::ReveilWidget *ui;

    /**
     * @brief m_filePath
     */
    QString m_filePath;

    /**
     * @brief m_temps
     */
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

    /**
     * @brief setTemps
     * @param temps
     */
    void setTemps(QTime temps);
    /**
     * @brief supprimerReveil
     */
    void supprimerReveil();
};

#endif // REVEILWIDGET_H
