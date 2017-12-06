#ifndef HORLOGE_H
#define HORLOGE_H

#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QSettings>

#include "paramheure.h"
#include "chronometre.h"
#include "paramreveils.h"
#include "minuteur.h"
#include "affichage.h"
#include "theme.h"
#include "reveilwidget.h"
#include "reveilmodel.h"
#include <mainwindow.h>

namespace Ui {
class Horloge;
}

class Horloge : public QLabel
{
    Q_OBJECT

public:
    explicit Horloge(QWidget *parent = 0);
    ~Horloge();
    void paintEvent(QPaintEvent *);
    void setParametres(int heures, int minutes, int secondes);
    void setHeures();
    void setMinutes();
    void setSecondes();

private:
    Ui::Horloge *ui;
    QSettings *m_settings;
    /**
     * @brief m_listeHeures
     */
    QStringList m_listeHeures;

    //Attributs associes au painter
    //---------------------------------------------------------------------------------------------------------------------
        //Mise en forme

        /**
         * @brief m_brush
         */
        QBrush m_brush;

        /**
         * @brief couleur
         */
        QColor m_couleur;

        /**
         * @brief m_font
         */
        QFont m_font;

        //Mise en Positions

        /**
         * @brief centre : Centre de la MainWindow
         */
        QPoint m_centre;

        /**
         * @brief cXPos
         */
        int m_cXPos;

        /**
         * @brief cYPos
         */
        int m_cYPos;

        /**
         * @brief hXPos
         */
        int m_hXPos;

        /**
         * @brief hYPos
         */
        int m_hYPos;

        /**
         * @brief mXPos
         */
        int m_mXPos;

        /**
         * @brief mYPos
         */
        int m_mYPos;

        /**
         * @brief sXPos
         */
        int m_sXPos;

        /**
         * @brief sYPos
         */
        int m_sYPos;

        /**
         * @brief m_point
         */
        QPoint m_point;

        //Decompte

        /**
         * @brief m_heures
         */
        int m_heures;

        /**
         * @brief m_minutes
         */
        int m_minutes;

        /**
         * @brief m_secondes
         */
        int m_secondes;

};

#endif // HORLOGE_H
