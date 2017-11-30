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
    explicit ReveilWidget(QString fichierAudio, QWidget *parent);
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
    bool isActif();
signals:
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
    void supprimerReveil();
};

#endif // REVEILWIDGET_H
