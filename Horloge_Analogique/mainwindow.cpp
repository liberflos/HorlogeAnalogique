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
    m_heures = QTime::currentTime().hour();
    m_minutes = QTime::currentTime().minute() + m_heures*60;
    m_secondes = QTime::currentTime().second();
    sXPos= 145 + 125*cos((PI/2)-(m_secondes*PI)/FRACTION_MINUTES);
    sYPos= 40 +(125 - 125*sin((PI/2) +(m_secondes*PI)/FRACTION_MINUTES));
    mXPos= 145 + 125*cos((PI/2)-(m_minutes*PI)/FRACTION_MINUTES);
    mYPos= 165 - 125*sin((PI/2) +(m_minutes*PI)/FRACTION_MINUTES);
    hXPos= 145 + 125*cos((PI/2)-(m_minutes*PI)/FRACTION_HEURES);
    hYPos= 165 - 125*sin((PI/2) +(m_minutes*PI)/FRACTION_HEURES);
    timer = new QTimer(this);
    timer->setProperty("isSync", false);
    connect(timer, SIGNAL(timeout()),this,SLOT(timerSlot()));
    timer->start(TIMER_DELAY - QTime::currentTime().msec());
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
    cXPos = this->width()/2;
    cYPos = this->height()/2 + ui->menuBar->height()/2;
    QColor couleur;
    centre.setX(cXPos);
    centre.setY(cYPos);
    if(this->height() - ui->menuBar->height() > this->width()){
        painter.drawText(cXPos - 50, centre.y() + cXPos/3,QDate::currentDate().toString());
        sXPos= cXPos+ (cXPos - DECALAGE)*cos((PI/2)-(m_secondes*PI)/FRACTION_MINUTES);
        sYPos= cYPos- (cXPos - DECALAGE)*sin((PI/2)-(m_secondes*PI)/FRACTION_MINUTES);
        mXPos= cXPos+ (cXPos - DECALAGE)*cos((PI/2)-(m_minutes*PI)/FRACTION_MINUTES);
        mYPos= cYPos- (cXPos - DECALAGE)*sin((PI/2)-(m_minutes*PI)/FRACTION_MINUTES);
        hXPos=  cXPos+ (cXPos - DECALAGE)*cos((PI/2)-(m_minutes*PI)/FRACTION_HEURES);
        hYPos= cYPos- (cXPos - DECALAGE)*sin((PI/2)-(m_minutes*PI)/FRACTION_HEURES);
        painter.drawEllipse(centre,cXPos,cXPos);
        couleur.setRgb(255,0,0);
        painter.setPen(couleur);
        painter.drawLine(cXPos,cYPos,sXPos,sYPos);
        couleur.setRgb(0,255,0);
        painter.setPen(couleur);
        painter.drawLine(cXPos,cYPos,mXPos,mYPos);
        couleur.setRgb(0,0,255);
        painter.setPen(couleur);
        painter.drawLine(cXPos,cYPos,hXPos,hYPos);
        QPoint point;
        for(int i = 1 ; i <= 60 ; i++){
            if(i%5 == 0){
                painter.drawText(cXPos+ (cXPos - 10)*cos((PI/2)-(i*PI)/FRACTION_MINUTES) -10
                                 ,cYPos- (cXPos - 10)*sin((PI/2)-(i*PI)/FRACTION_MINUTES) - 10
                                 ,20,20, Qt::AlignCenter,QString::number(i/5));
            }
            point.setX(cXPos+ (cXPos - 20)*cos((PI/2)-(i*PI)/FRACTION_MINUTES));
            point.setY(cYPos- (cXPos - 20)*sin((PI/2)-(i*PI)/FRACTION_MINUTES));
            painter.drawEllipse(point,1,1);
        }
    }else{
        painter.drawText(cXPos - 50, cYPos + cYPos/3,QDate::currentDate().toString());
        sXPos= cXPos+ (cYPos - DECALAGE - ui->menuBar->height() )*cos((PI/2)-(m_secondes*PI)/FRACTION_MINUTES);
        sYPos= cYPos- (cYPos - DECALAGE - ui->menuBar->height() )*sin((PI/2)-(m_secondes*PI)/FRACTION_MINUTES);
        mXPos= cXPos+ (cYPos - DECALAGE - ui->menuBar->height() )*cos((PI/2)-(m_minutes*PI)/FRACTION_MINUTES);
        mYPos= cYPos- (cYPos - DECALAGE - ui->menuBar->height() )*sin((PI/2)-(m_minutes*PI)/FRACTION_MINUTES);
        hXPos=  cXPos+ (cYPos - DECALAGE - ui->menuBar->height() )*cos((PI/2)-(m_minutes*PI)/FRACTION_HEURES);
        hYPos= cYPos- (cYPos - DECALAGE - ui->menuBar->height() )*sin((PI/2)-(m_minutes*PI)/FRACTION_HEURES);
        painter.drawEllipse(centre,cYPos - ui->menuBar->height(),cYPos - ui->menuBar->height());
        couleur.setRgb(255,0,0);
        painter.setPen(couleur);
        painter.drawLine(cXPos,cYPos,sXPos,sYPos);
        couleur.setRgb(0,255,0);
        painter.setPen(couleur);
        painter.drawLine(cXPos,cYPos,mXPos,mYPos);
        couleur.setRgb(0,0,255);
        painter.setPen(couleur);
        painter.drawLine(cXPos,cYPos,hXPos,hYPos);
        QPoint point;
        for(int i = 1 ; i <= 60 ; i++){
            if(i%5 == 0){
                painter.drawText(cXPos+ (cYPos - 10 - ui->menuBar->height())*cos((PI/2)-(i*PI)/FRACTION_MINUTES) -10
                                 ,cYPos - (cYPos - 10 - ui->menuBar->height())*sin((PI/2)-(i*PI)/FRACTION_MINUTES) - 10
                                 ,20,20, Qt::AlignCenter,QString::number(i/5));
            }
            point.setX(cXPos+ (cYPos - 20 - ui->menuBar->height() )*cos((PI/2)-(i*PI)/FRACTION_MINUTES));
            point.setY(cYPos - (cYPos - 20 - ui->menuBar->height() )*sin((PI/2)-(i*PI)/FRACTION_MINUTES));
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
    if(!timer->property("isSync").toBool()){
        timer->setInterval(TIMER_DELAY);
        timer->setProperty("isSync", true);
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

    ParamHeure *nouvelleFenetre = new ParamHeure(this);
    nouvelleFenetre->setVisible(true);
    nouvelleFenetre->setBaseSize(300,300);
    switch (action->property(PROPRIETE_ACTION_MENU).toInt()) {
    case VALEUR_ACTION_PARAMETRE_HEURE:
        nouvelleFenetre->show();
        break;
    case VALEUR_ACTION_AFFICHAGE:
        break;
    case VALEUR_ACTION_THEME :
        break;
    case VALEUR_ACTION_NOUVEAU_CHRONO :
        break;
    case VALEUR_ACTION_NOUVEAU_REVEIL :
        break;
    case VALEUR_ACTION_MES_REVEILS :
        break;
    case VALEUR_ACTION_PARAMETRE_REVEIL :
        break;
    case VALEUR_ACTION_NOUVEAU_MINUTEUR :
        break;
    case VALEUR_ACTION_MES_MINUTEUR :
        break;
    default:
        break;
    }

}//______________________________________________________________________________________________________Fin menuAction

