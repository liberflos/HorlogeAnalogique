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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *);
private:
    Ui::MainWindow *ui;
    double pi;
    QColor couleur;
    QPoint centre;
    int m_secondes;
    int m_minutes;
    int m_heures;
    int cXPos;
    int cYPos;
    int sXPos;
    int sYPos;
    int mXPos;
    int mYPos;
    int hXPos;
    int hYPos;
    QTimer *timer;
private slots:
    void timerSlot();
    void menuAction(QAction * action);
};

#endif // MAINWINDOW_H
