#include "mainwindow.h"
#include "ui_mainwindow.h"


//*********************************************************************************************************************
//*******************************************CONSTRUCTEUR MAINWINDOW***************************************************
//*********************************************************************************************************************
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_nbChrono = 0;
    m_nbMinuteurs = 0;
    m_heures = QTime::currentTime().hour();
    m_minutes = QTime::currentTime().minute() + m_heures*60;
    m_secondes = QTime::currentTime().second();
    m_sXPos= 145 + 125*cos((PI/2)-(m_secondes*PI)/FRACTION_MINUTES);
    m_sYPos= 40 +(125 - 125*sin((PI/2) +(m_secondes*PI)/FRACTION_MINUTES));
    m_mXPos= 145 + 125*cos((PI/2)-(m_minutes*PI)/FRACTION_MINUTES);
    m_mYPos= 165 - 125*sin((PI/2) +(m_minutes*PI)/FRACTION_MINUTES);
    m_hXPos= 145 + 125*cos((PI/2)-(m_minutes*PI)/FRACTION_HEURES);
    m_hYPos= 165 - 125*sin((PI/2) +(m_minutes*PI)/FRACTION_HEURES);
    m_timer = new QTimer(this);
    m_timer->setProperty("isSync", false);
    connect(m_timer, SIGNAL(timeout()),this,SLOT(timerSlot()));
    m_timer->start(TIMER_DELAY - QTime::currentTime().msec());
    ui->actionParametres_de_l_heure->setProperty(PROPRIETE_ACTION_MENU,VALEUR_ACTION_PARAMETRE_HEURE);
    ui->actionAffichage->setProperty(PROPRIETE_ACTION_MENU,VALEUR_ACTION_AFFICHAGE);
    ui->actionThemes->setProperty(PROPRIETE_ACTION_MENU,VALEUR_ACTION_THEME);
    ui->actionNouveau_Chronometre->setProperty(PROPRIETE_ACTION_MENU,VALEUR_ACTION_NOUVEAU_CHRONO);
    ui->actionNouveau_Reveil->setProperty(PROPRIETE_ACTION_MENU,VALEUR_ACTION_NOUVEAU_REVEIL);
    ui->actionMes_Reveils->setProperty(PROPRIETE_ACTION_MENU,VALEUR_ACTION_MES_REVEILS);
    ui->actionParametres->setProperty(PROPRIETE_ACTION_MENU,VALEUR_ACTION_PARAMETRE_REVEIL);
    ui->actionNouveau_Minuteur->setProperty(PROPRIETE_ACTION_MENU,VALEUR_ACTION_NOUVEAU_MINUTEUR);
    ui->actionMes_Minuteurs->setProperty(PROPRIETE_ACTION_MENU,VALEUR_ACTION_MES_MINUTEUR);
    connect(ui->menuBar,SIGNAL(triggered(QAction*)),this, SLOT(menuAction(QAction*)));
}//______________________________________________________________________________________________________Fin MainWindow

MainWindow::~MainWindow()
{
    delete ui;

}

//*********************************************************************************************************************
//***********************************************METHODES EVENT********************************************************
//*********************************************************************************************************************

void MainWindow::keyPressEvent(QKeyEvent *event)//__________________________________________________Debut keyPressEvent
{
    if((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_Q))
        close();
}//___________________________________________________________________________________________________Fin keyPressEvent
void MainWindow::paintEvent(QPaintEvent *)//___________________________________________________________Debut paintEvent
{
    QPainter painter(this);
    m_cXPos = this->width()/2;
    m_cYPos = this->height()/2 + ui->menuBar->height()/2;
    m_centre.setX(m_cXPos);
    m_centre.setY(m_cYPos);
    if(this->height() - ui->menuBar->height() > this->width()){
        painter.drawText(m_cXPos - 50, m_centre.y() + m_cXPos/3,QDate::currentDate().toString());
        m_sXPos= m_cXPos+ (m_cXPos - DECALAGE)*cos((PI/2)-(m_secondes*PI)/FRACTION_MINUTES);
        m_sYPos= m_cYPos- (m_cXPos - DECALAGE)*sin((PI/2)-(m_secondes*PI)/FRACTION_MINUTES);
        m_mXPos= m_cXPos+ (m_cXPos - DECALAGE)*cos((PI/2)-(m_minutes*PI)/FRACTION_MINUTES);
        m_mYPos= m_cYPos- (m_cXPos - DECALAGE)*sin((PI/2)-(m_minutes*PI)/FRACTION_MINUTES);
        m_hXPos= m_cXPos+ (m_cXPos - DECALAGE)*cos((PI/2)-(m_minutes*PI)/FRACTION_HEURES);
        m_hYPos= m_cYPos- (m_cXPos - DECALAGE)*sin((PI/2)-(m_minutes*PI)/FRACTION_HEURES);
        painter.drawEllipse(m_centre,m_cXPos,m_cXPos);
        m_couleur.setRgb(255,0,0);
        painter.setPen(m_couleur);
        painter.drawLine(m_cXPos,m_cYPos,m_sXPos,m_sYPos);
        m_couleur.setRgb(0,255,0);
        painter.setPen(m_couleur);
        painter.drawLine(m_cXPos,m_cYPos,m_mXPos,m_mYPos);
        m_couleur.setRgb(0,0,255);
        painter.setPen(m_couleur);
        painter.drawLine(m_cXPos,m_cYPos,m_hXPos,m_hYPos);
        QPoint point;
        for(int i = 1 ; i <= 60 ; i++){
            if(i%5 == 0){
                painter.drawText(m_cXPos+ (m_cXPos - 10)*cos((PI/2)-(i*PI)/FRACTION_MINUTES) -10
                                 ,m_cYPos- (m_cXPos - 10)*sin((PI/2)-(i*PI)/FRACTION_MINUTES) - 10
                                 ,20,20, Qt::AlignCenter,QString::number(i/5));
            }
            point.setX(m_cXPos+ (m_cXPos - 20)*cos((PI/2)-(i*PI)/FRACTION_MINUTES));
            point.setY(m_cYPos- (m_cXPos - 20)*sin((PI/2)-(i*PI)/FRACTION_MINUTES));
            painter.drawEllipse(point,1,1);
        }
    }else{
        painter.drawText(m_cXPos - 50, m_cYPos + m_cYPos/3,QDate::currentDate().toString());
        m_sXPos= m_cXPos + (m_cYPos - DECALAGE - ui->menuBar->height() )*cos((PI/2)-(m_secondes*PI)/FRACTION_MINUTES);
        m_sYPos= m_cYPos - (m_cYPos - DECALAGE - ui->menuBar->height() )*sin((PI/2)-(m_secondes*PI)/FRACTION_MINUTES);
        m_mXPos= m_cXPos + (m_cYPos - DECALAGE - ui->menuBar->height() )*cos((PI/2)-(m_minutes*PI)/FRACTION_MINUTES);
        m_mYPos= m_cYPos - (m_cYPos - DECALAGE - ui->menuBar->height() )*sin((PI/2)-(m_minutes*PI)/FRACTION_MINUTES);
        m_hXPos= m_cXPos + (m_cYPos - DECALAGE - ui->menuBar->height() )*cos((PI/2)-(m_minutes*PI)/FRACTION_HEURES);
        m_hYPos= m_cYPos - (m_cYPos - DECALAGE - ui->menuBar->height() )*sin((PI/2)-(m_minutes*PI)/FRACTION_HEURES);
        painter.drawEllipse(m_centre,m_cYPos - ui->menuBar->height(),m_cYPos - ui->menuBar->height());
        m_couleur.setRgb(255,0,0);
        painter.setPen(m_couleur);
        painter.drawLine(m_cXPos,m_cYPos,m_sXPos,m_sYPos);
        m_couleur.setRgb(0,255,0);
        painter.setPen(m_couleur);
        painter.drawLine(m_cXPos,m_cYPos,m_mXPos,m_mYPos);
        m_couleur.setRgb(0,0,255);
        painter.setPen(m_couleur);
        painter.drawLine(m_cXPos,m_cYPos,m_hXPos,m_hYPos);
        QPoint point;
        for(int i = 1 ; i <= 60 ; i++){
            if(i%5 == 0){
                painter.drawText(m_cXPos+ (m_cYPos - 10 - ui->menuBar->height())*cos((PI/2)-(i*PI)/FRACTION_MINUTES) -10
                                 ,m_cYPos - (m_cYPos - 10 - ui->menuBar->height())*sin((PI/2)-(i*PI)/FRACTION_MINUTES) - 10
                                 ,20,20, Qt::AlignCenter,QString::number(i/5));
            }
            point.setX(m_cXPos + (m_cYPos - 20 - ui->menuBar->height() )*cos((PI/2)-(i*PI)/FRACTION_MINUTES));
            point.setY(m_cYPos - (m_cYPos - 20 - ui->menuBar->height() )*sin((PI/2)-(i*PI)/FRACTION_MINUTES));
            painter.drawEllipse(point,1,1);
        }
    }
}//___________________________________________________________________________________________________Fin keyPressEvent

//*********************************************************************************************************************
//**********************************************METHODES PUBLIQUES*****************************************************
//*********************************************************************************************************************

//*********************************************************************************************************************
//**************************************************SLOTS PRIVES*******************************************************
//*********************************************************************************************************************

void MainWindow::timerSlot()//__________________________________________________________________________Debut timerSlot
{
    if(!m_timer->property("isSync").toBool()){
        m_timer->setInterval(TIMER_DELAY);
        m_timer->setProperty("isSync", true);
    }
    m_secondes++;

    if(m_secondes == 60){
        m_secondes =0;
        m_minutes++;
        m_heures++;

    }
    if(m_minutes == 60*12){
        m_heures=0;
        m_minutes=0;
    }

    update();

}//_______________________________________________________________________________________________________Fin timerSlot

void MainWindow::menuAction(QAction *action)//_________________________________________________________Debut menuAction
{

    Chronometre *chrono = new Chronometre(this);
    Minuteur *minuteur = new Minuteur(this);

    chrono->setGeometry(0,ui->menuBar->height() + (m_nbChrono*chrono->height()),chrono->width(),chrono->height());
    minuteur->setGeometry(this->width() - minuteur->width(),ui->menuBar->height() + (m_nbMinuteurs*minuteur->height()),minuteur->width(),minuteur->height());
    ParamHeure *nouvelleFenetre = new ParamHeure(this);
    switch (action->property(PROPRIETE_ACTION_MENU).toInt()) {
    case VALEUR_ACTION_PARAMETRE_HEURE:
        nouvelleFenetre->show();
        chrono->close();
        minuteur->close();
        break;
    case VALEUR_ACTION_AFFICHAGE:
        chrono->close();
        minuteur->close();
        break;
    case VALEUR_ACTION_THEME :
        chrono->close();
        minuteur->close();
        break;
    case VALEUR_ACTION_NOUVEAU_CHRONO :
        chrono->show();
        m_nbChrono++;
        minuteur->close();

        break;
    case VALEUR_ACTION_NOUVEAU_REVEIL :
        chrono->close();
        minuteur->close();
        break;
    case VALEUR_ACTION_MES_REVEILS :
        chrono->close();
        minuteur->close();
        break;
    case VALEUR_ACTION_PARAMETRE_REVEIL :
        chrono->close();
        minuteur->close();
        break;
    case VALEUR_ACTION_NOUVEAU_MINUTEUR :
        minuteur->show();
        m_nbMinuteurs++;
        chrono->close();
        break;
    case VALEUR_ACTION_MES_MINUTEUR :
        chrono->close();
        minuteur->close();
        break;
    default:
        break;
    }

}//______________________________________________________________________________________________________Fin menuAction

