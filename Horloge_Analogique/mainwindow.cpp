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
//Récupération des settings
    QCoreApplication::setOrganizationName("AppliHours");
    QCoreApplication::setApplicationName("HorlogeAnalogique");
    m_settings = new QSettings("AppliHours", "HorlogeAnalogique");
    qDebug() << m_settings->value(HEURE_REVEILS);
//Configuration de l'interface graphique
    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setToolTip("Double-cliquer pour afficher/cacher les menus");
    ui->menuBar->hide();
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
//Definitions des propriétés des actions du menu
    ui->actionParametres_de_l_heure->setProperty(PROPRIETE_ACTION_MENU,VALEUR_ACTION_PARAMETRE_HEURE);
    ui->actionAffichage_2->setProperty(PROPRIETE_ACTION_MENU,VALEUR_ACTION_AFFICHAGE);
    ui->actionThemes->setProperty(PROPRIETE_ACTION_MENU,VALEUR_ACTION_THEME);
    ui->actionNouveau_Chronometre->setProperty(PROPRIETE_ACTION_MENU,VALEUR_ACTION_NOUVEAU_CHRONO);
    ui->actionNouveau_Reveil->setProperty(PROPRIETE_ACTION_MENU,VALEUR_ACTION_NOUVEAU_REVEIL);
    ui->actionParametresReveils->setProperty(PROPRIETE_ACTION_MENU,VALEUR_ACTION_PARAMETRE_REVEIL);
    ui->actionNouveau_Minuteur->setProperty(PROPRIETE_ACTION_MENU,VALEUR_ACTION_NOUVEAU_MINUTEUR);
    ui->actionMes_Minuteurs->setProperty(PROPRIETE_ACTION_MENU,VALEUR_ACTION_MES_MINUTEUR);
    ui->actionFermer->setProperty(PROPRIETE_ACTION_MENU,VALEUR_ACTION_FERMER);
    ui->actionParam_tres_par_d_faut->setProperty(PROPRIETE_ACTION_MENU, VALEUR_ACTION_PARAM_DEFAUT);
    connect(ui->menuBar,SIGNAL(triggered(QAction*)),this, SLOT(menuAction(QAction*)));
    connect(m_timer, SIGNAL(timeout()),this,SLOT(timerSlot()));
//Demmarage de l'horloge
    m_timer->start(TIMER_DELAY - QTime::currentTime().msec());
//Création des réveils
    QList<QVariant> listeReveils;
    listeReveils.append(m_settings->value(HEURE_REVEILS).toList());
    for(int i = 0 ; i < listeReveils.length() ; i++){
        ReveilModel *reveilModel = new ReveilModel(m_settings->value(HEURE_REVEILS).toList().at(i).toString(),
                                     m_settings->value(PATH_AUDIO).toString(),this);
        m_listeReveils.append(reveilModel);
    }
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
    for(int i = 0 ; i < m_listeMinuteurs.size(); i++){
        m_listeMinuteurs.at(i)->redessiner();
    }
    int fontSize = m_settings->value(TAILLE_TEXTE, 14).toInt();

    QPainter painter(this);
    m_couleur.setRgba(m_settings->value(COULEUR_FOND, 0).toInt());
    m_brush.setStyle(Qt::SolidPattern);
    m_brush.setColor(m_couleur);
    painter.setBrush(m_brush);
    m_font.setPointSize(fontSize);
    painter.setFont(m_font);
    m_cXPos = this->width()/2;
    m_cYPos = this->height()/2 + ui->menuBar->height()/2;
    m_centre.setX(m_cXPos);
    m_centre.setY(m_cYPos);
    if(this->height() - ui->menuBar->height() > this->width()){
        m_sXPos= m_cXPos+ (m_cXPos - DECALAGE)*cos((PI/2)-(m_secondes*PI)/FRACTION_MINUTES);
        m_sYPos= m_cYPos- (m_cXPos - DECALAGE)*sin((PI/2)-(m_secondes*PI)/FRACTION_MINUTES);
        m_mXPos= m_cXPos+ (m_cXPos - DECALAGE)*cos((PI/2)-(m_minutes*PI)/FRACTION_MINUTES);
        m_mYPos= m_cYPos- (m_cXPos - DECALAGE)*sin((PI/2)-(m_minutes*PI)/FRACTION_MINUTES);
        m_hXPos= m_cXPos+ (m_cXPos - DECALAGE)*cos((PI/2)-(m_minutes*PI)/FRACTION_HEURES);
        m_hYPos= m_cYPos- (m_cXPos - DECALAGE)*sin((PI/2)-(m_minutes*PI)/FRACTION_HEURES);
        painter.drawEllipse(m_centre,m_cXPos,m_cXPos);
        m_couleur.setRgb(0,0,255);
        painter.setPen(m_couleur);
        for(int i = 0 ; i < 600 ; i++){
            painter.drawLine(m_cXPos + ((m_cXPos - DECALAGE - ui->menuBar->height() )/20)*cos((PI/2)-(m_minutes*PI)/FRACTION_HEURES + i)
                             ,m_cYPos - ((m_cXPos - DECALAGE - ui->menuBar->height() )/20)*sin((PI/2)-(m_minutes*PI)/FRACTION_HEURES + i),m_hXPos,m_hYPos);

        }
        m_couleur.setRgb(0,255,0);
        painter.setPen(m_couleur);
        for(int i = 0 ; i < 400 ; i++){
            painter.drawLine(m_cXPos + ((m_cXPos - DECALAGE - ui->menuBar->height() )/30)*cos((PI/2)-(m_minutes*PI)/FRACTION_MINUTES + i)
                             ,m_cYPos - ((m_cXPos - DECALAGE - ui->menuBar->height() )/30)*sin((PI/2)-(m_minutes*PI)/FRACTION_MINUTES + i),m_mXPos,m_mYPos);


        }
        m_couleur.setRgb(255,0,0);
        painter.setPen(m_couleur);
        for(int i = 0 ; i < 300 ; i++){
            painter.drawLine(m_cXPos + ((m_cXPos - DECALAGE - ui->menuBar->height() )/50)*cos((PI/2)-(m_secondes*PI)/FRACTION_MINUTES + i)
                             ,m_cYPos - ((m_cXPos - DECALAGE - ui->menuBar->height() )/50)*sin((PI/2)-(m_secondes*PI)/FRACTION_MINUTES + i),m_sXPos,m_sYPos);
        }
        m_couleur.setRgb(0,0,0);
        painter.setPen(m_couleur);

        for(int i = 1 ; i <= 60 ; i++){
            if(i%5 == 0){
                painter.drawText(m_cXPos+ (m_cXPos - fontSize)*cos((PI/2)-(i*PI)/FRACTION_MINUTES) - fontSize
                                 ,m_cYPos- (m_cXPos - fontSize)*sin((PI/2)-(i*PI)/FRACTION_MINUTES) - fontSize
                                 ,2*fontSize,2*fontSize, Qt::AlignCenter,QString::number(i/5));
            }
            m_point.setX(m_cXPos+ (m_cXPos - 2*fontSize)*cos((PI/2)-(i*PI)/FRACTION_MINUTES));
            m_point.setY(m_cYPos- (m_cXPos - 2*fontSize)*sin((PI/2)-(i*PI)/FRACTION_MINUTES));
            painter.drawEllipse(m_point,1,1);
        }
        painter.drawText(m_cXPos - (m_font.pointSize()/3)*QDate::currentDate().toString().length() , m_centre.y() + m_cXPos/3,QDate::currentDate().toString());

    }else{
        m_sXPos= m_cXPos + (m_cYPos - DECALAGE - ui->menuBar->height() )*cos((PI/2)-(m_secondes*PI)/FRACTION_MINUTES);
        m_sYPos= m_cYPos - (m_cYPos - DECALAGE - ui->menuBar->height() )*sin((PI/2)-(m_secondes*PI)/FRACTION_MINUTES);
        m_mXPos= m_cXPos + (m_cYPos - DECALAGE - ui->menuBar->height() )*cos((PI/2)-(m_minutes*PI)/FRACTION_MINUTES);
        m_mYPos= m_cYPos - (m_cYPos - DECALAGE - ui->menuBar->height() )*sin((PI/2)-(m_minutes*PI)/FRACTION_MINUTES);
        m_hXPos= m_cXPos + (m_cYPos - DECALAGE - ui->menuBar->height() )*cos((PI/2)-(m_minutes*PI)/FRACTION_HEURES);
        m_hYPos= m_cYPos - (m_cYPos - DECALAGE - ui->menuBar->height() )*sin((PI/2)-(m_minutes*PI)/FRACTION_HEURES);
        painter.drawEllipse(m_centre,m_cYPos - ui->menuBar->height(),m_cYPos - ui->menuBar->height());
        m_couleur.setRgb(0,0,255);
        painter.setPen(m_couleur);
        for(int i = 0 ; i < 600 ; i++){
            painter.drawLine(m_cXPos + ((m_cYPos - DECALAGE - ui->menuBar->height() )/20)*cos((PI/2)-(m_minutes*PI)/FRACTION_HEURES + i)
                             ,m_cYPos - ((m_cYPos - DECALAGE - ui->menuBar->height() )/20)*sin((PI/2)-(m_minutes*PI)/FRACTION_HEURES + i),m_hXPos,m_hYPos);

        }
        m_couleur.setRgb(0,255,0);
        painter.setPen(m_couleur);
        for(int i = 0 ; i < 400 ; i++){
            painter.drawLine(m_cXPos + ((m_cYPos - DECALAGE - ui->menuBar->height() )/30)*cos((PI/2)-(m_minutes*PI)/FRACTION_MINUTES + i)
                             ,m_cYPos - ((m_cYPos - DECALAGE - ui->menuBar->height() )/30)*sin((PI/2)-(m_minutes*PI)/FRACTION_MINUTES + i),m_mXPos,m_mYPos);


        }
        m_couleur.setRgb(255,0,0);
        painter.setPen(m_couleur);
        for(int i = 0 ; i < 300 ; i++){
            painter.drawLine(m_cXPos + ((m_cYPos - DECALAGE - ui->menuBar->height() )/50)*cos((PI/2)-(m_secondes*PI)/FRACTION_MINUTES + i)
                             ,m_cYPos - ((m_cYPos - DECALAGE - ui->menuBar->height() )/50)*sin((PI/2)-(m_secondes*PI)/FRACTION_MINUTES + i),m_sXPos,m_sYPos);
        }
        m_couleur.setRgb(0,0,0);
        painter.setPen(m_couleur);
        for(int i = 1 ; i <= 60 ; i++){
            if(i%5 == 0){
                painter.drawText(m_cXPos+ (m_cYPos - fontSize - ui->menuBar->height())*cos((PI/2)-(i*PI)/FRACTION_MINUTES) - fontSize
                                 ,m_cYPos - (m_cYPos - fontSize - ui->menuBar->height())*sin((PI/2)-(i*PI)/FRACTION_MINUTES) - fontSize
                                 ,2*fontSize ,2*fontSize , Qt::AlignCenter,QString::number(i/5));
            }
            m_point.setX(m_cXPos + (m_cYPos - 2*fontSize - ui->menuBar->height() )*cos((PI/2)-(i*PI)/FRACTION_MINUTES));
            m_point.setY(m_cYPos - (m_cYPos - 2*fontSize - ui->menuBar->height() )*sin((PI/2)-(i*PI)/FRACTION_MINUTES));
            painter.drawEllipse(m_point,1,1);
        }
        painter.drawText(m_cXPos - (m_font.pointSize()/3)*QDate::currentDate().toString().length() , m_cYPos + m_cYPos/3,QDate::currentDate().toString());

    }
}//______________________________________________________________________________________________________Fin paintEvent

void MainWindow::mouseDoubleClickEvent(QMouseEvent *)
{
    if(this->windowFlags().testFlag(Qt::FramelessWindowHint)){
        this->setWindowFlags(Qt::WindowTitleHint);
        ui->menuBar->show();
        this->show();
    }else{
        ui->menuBar->hide();
        this->setGeometry(this->x(),this->y(), this->width(), this->height());
        this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
        this->show();
    }
}

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

    ParamHeure *nouvelleFenetre;
    Affichage *affichage;
    Theme *theme;
    Chronometre *chrono;
    ReveilModel *reveilModel;
    Minuteur *minuteur;
    ParamReveils *paramReveils;


    switch (action->property(PROPRIETE_ACTION_MENU).toInt()) {
    case VALEUR_ACTION_PARAMETRE_HEURE:
        nouvelleFenetre = new ParamHeure(this);
        nouvelleFenetre->setAttribute(Qt::WA_DeleteOnClose);
        nouvelleFenetre->show();
        break;
    case VALEUR_ACTION_AFFICHAGE:
        affichage = new Affichage(this);
        affichage->setAttribute(Qt::WA_DeleteOnClose);
        affichage->show();
        break;
    case VALEUR_ACTION_THEME :
        theme = new Theme(this);
        theme->show();
        break;
    case VALEUR_ACTION_NOUVEAU_CHRONO :
        chrono = new Chronometre(this);
        chrono->setAttribute(Qt::WA_DeleteOnClose);
        chrono->setGeometry(0,ui->menuBar->height() + (m_listeChronometres.size()*chrono->height()),
                            chrono->width(),chrono->height());
        m_listeChronometres.append(chrono);
        connect(chrono,SIGNAL(closeSigC(int)),this, SLOT(MAJC(int)));
        chrono->setIndex(m_listeChronometres.size() - 1);
        chrono->show();
        break;
    case VALEUR_ACTION_NOUVEAU_REVEIL :
        paramReveils = new ParamReveils(this);
        paramReveils->setAttribute(Qt::WA_DeleteOnClose);
        paramReveils->exec();
        reveilModel= new ReveilModel(m_settings->value(HEURE_REVEILS).toList().last().toString(),
                                     m_settings->value(PATH_AUDIO).toString(),this);
        m_listeReveils.append(reveilModel);
        break;
    case VALEUR_ACTION_PARAMETRE_REVEIL :
        paramReveils = new ParamReveils(this);
        break;
    case VALEUR_ACTION_NOUVEAU_MINUTEUR :
        minuteur = new Minuteur(this);
        minuteur->setGeometry(this->width() - minuteur->width(),
                              ui->menuBar->height() + (m_listeMinuteurs.size()*minuteur->height()),
                              minuteur->width(),minuteur->height());
        m_listeMinuteurs.append(minuteur);
        connect(minuteur,SIGNAL(closeSigM(int)),this, SLOT(MAJM(int)));
        minuteur->setIndex(m_listeMinuteurs.size() - 1);
        minuteur->show();
        break;
    case VALEUR_ACTION_MES_MINUTEUR :
        break;
    case VALEUR_ACTION_FERMER :
        this->close();
        break;
    case VALEUR_ACTION_PARAM_DEFAUT :
        m_settings->clear();
        qDebug() << "settings cleared";
        break;
    default:
        break;
    }

}//______________________________________________________________________________________________________Fin menuAction

void MainWindow::MAJC(int index)
{
    m_listeChronometres.removeAt(index);
    for(int i = index ; i < m_listeChronometres.size(); i++){
        m_listeChronometres.at(i)->deplacer();
        m_listeChronometres.at(i)->setIndex(i);
    }
}
void MainWindow::MAJM(int index)
{
    m_listeMinuteurs.removeAt(index);
    for(int i = index ; i < m_listeMinuteurs.size(); i++){
        m_listeMinuteurs.at(i)->deplacer();
        m_listeMinuteurs.at(i)->setIndex(i);
    }
}
