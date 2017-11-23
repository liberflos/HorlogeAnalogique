#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QKeyEvent>
#include <QTimerEvent>
#include <QPaintEvent>
#include <QTimer>
#include <QPainter>
#include <cmath>
#include <QDebug>
#include <QTime>
#include <QPoint>
#include <QAction>

#include "paramheure.h"

#define PROPRIETE_ACTION_MENU "propriete_action_menu"
#define VALEUR_ACTION_PARAMETRE_HEURE 1

namespace Ui {
class MainWindow;
}
/**
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow
     * @param parent
     */
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    /**
     * @brief keyPressEvent
     * @param event
     */
    void keyPressEvent(QKeyEvent *event);
    /**
     * @brief paintEvent
     */
    void paintEvent(QPaintEvent *);
private:
    Ui::MainWindow *ui;
    /**
     * @brief pi
     */
    double pi;
    /**
     * @brief couleur
     */
    QColor couleur;
    /**
     * @brief centre
     */
    QPoint centre;
    /**
     * @brief m_secondes
     */
    int m_secondes;
    /**
     * @brief m_minutes
     */
    int m_minutes;
    /**
     * @brief m_heures
     */
    int m_heures;
    /**
     * @brief cXPos
     */
    int cXPos;
    /**
     * @brief cYPos
     */
    int cYPos;
    /**
     * @brief sXPos
     */
    int sXPos;
    /**
     * @brief sYPos
     */
    int sYPos;
    /**
     * @brief mXPos
     */
    int mXPos;
    /**
     * @brief mYPos
     */
    int mYPos;
    /**
     * @brief hXPos
     */
    int hXPos;
    /**
     * @brief hYPos
     */
    int hYPos;
    /**
     * @brief timer
     */
    QTimer *timer;
private slots:
    /**
     * @brief timerSlot
     */
    void timerSlot();
    /**
     * @brief menuAction
     * @param action
     */
    void menuAction(QAction * action);
};

#endif // MAINWINDOW_H
