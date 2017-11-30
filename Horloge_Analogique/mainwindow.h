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
#include <QObject>
#include <QList>
#include <QMouseEvent>
#include <QSettings>

#include "paramheure.h"
#include "chronometre.h"
#include "paramreveils.h"
#include "minuteur.h"
#include "affichage.h"
#include "theme.h"
#include "reveilwidget.h"
#include "reveilmodel.h"

#define PI 3.141592654
#define DECALAGE 5
#define FRACTION_MINUTES 30
#define FRACTION_HEURES 360
#define TIMER_DELAY 1000
#define PROPRIETE_ACTION_MENU "propriete_action_menu"
#define VALEUR_ACTION_FERMER 1
#define VALEUR_ACTION_PARAMETRE_HEURE 2
#define VALEUR_ACTION_AFFICHAGE 3
#define VALEUR_ACTION_THEME 4
#define VALEUR_ACTION_NOUVEAU_CHRONO 5
#define VALEUR_ACTION_NOUVEAU_REVEIL 6
#define VALEUR_ACTION_PARAMETRE_REVEIL 7
#define VALEUR_ACTION_NOUVEAU_MINUTEUR 8
#define VALEUR_ACTION_MES_MINUTEUR 9
#define VALEUR_ACTION_PARAM_DEFAUT 10

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
    /**
     * @brief mouseDoubleClickEvent
     */
    void mouseDoubleClickEvent(QMouseEvent *);
    /**
     * @brief painterThemeNum
     * @param painter
     * @param fontSize
     */
    void painterThemeNum(QPainter &painter, int fontSize);
private:
    Ui::MainWindow *ui;
    /**
     * @brief couleur
     */
    QColor m_couleur;
    /**
     * @brief centre : Centre de la MainWindow
     */
    QPoint m_centre;
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
    int m_cXPos;
    /**
     * @brief cYPos
     */
    int m_cYPos;
    /**
     * @brief sXPos
     */
    int m_sXPos;
    /**
     * @brief sYPos
     */
    int m_sYPos;
    /**
     * @brief mXPos
     */
    int m_mXPos;
    /**
     * @brief mYPos
     */
    int m_mYPos;
    /**
     * @brief hXPos
     */
    int m_hXPos;
    /**
     * @brief hYPos
     */
    int m_hYPos;
    /**
     * @brief timer
     */
    QTimer *m_timer;
    /**
     * @brief m_timerShowFrame
     */
    QTimer *m_timerShowFrame;
    /**
     * @brief m_nbChrono
     */
    int m_nbChrono;
    /**
     * @brief m_nbMinuteurs
     */
    int m_nbMinuteurs;
    /**
     * @brief m_listeMinuteurs
     */
    QList<Minuteur*> m_listeMinuteurs;
    /**
     * @brief m_listeChronometres
     */
    QList<Chronometre*> m_listeChronometres;
    /**
     * @brief m_settings
     */
    QSettings *m_settings;
    /**
     * @brief m_listeReveils
     */
    QList<ReveilModel*> m_listeReveils;
    /**
     * @brief m_brush
     */
    QBrush m_brush;
    /**
     * @brief m_font
     */
    QFont m_font;
    /**
     * @brief m_point
     */
    QPoint m_point;
    QStringList m_listeHeures;

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
    /**
     * @brief MAJC
     * @param index
     */
    void MAJC(int index);
    /**
     * @brief MAJM
     * @param index
     */
    void MAJM(int index);
    /**
     * @brief settingsModifie
     */
    void settingsModifie();

};

#endif // MAINWINDOW_H
