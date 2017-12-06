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
    qDebug() << m_settings->allKeys();
    if(m_settings->value(GEOMETRIE_FENETRE, 0) != 0){
        this->setGeometry(m_settings->value(GEOMETRIE_FENETRE).toRect());

    }
//Configuration de l'interface graphique
    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setToolTip("Double-cliquer pour afficher/cacher les menus");
    ui->menuBar->hide();
    m_nbChrono = 0;
    m_nbMinuteurs = 0;
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
    ui->label->update();
}//______________________________________________________________________________________________________Fin paintEvent

void MainWindow::mouseDoubleClickEvent(QMouseEvent *)
{

    if(this->windowFlags().testFlag(Qt::FramelessWindowHint)){
        this->setWindowFlags(Qt::WindowTitleHint);
        this->setAttribute(Qt::WA_TranslucentBackground, false);
        this->setAttribute(Qt::WA_NoSystemBackground, false);
//        this->move(m_settings->value(GEOMETRIE_FENETRE).toRect().topLeft());
        this->setGeometry(m_settings->value(GEOMETRIE_FENETRE).toRect());
        ui->menuBar->show();
        this->show();
    }else{
        ui->menuBar->hide();
        this->setAttribute(Qt::WA_TranslucentBackground);
        this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
//        this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
//        this->move(m_settings->value(GEOMETRIE_FENETRE).toRect().topLeft());
        this->setGeometry(m_settings->value(GEOMETRIE_FENETRE).toRect());
        this->show();
    }
}

void MainWindow::moveEvent(QMoveEvent *event)
{
    m_settings->setValue(GEOMETRIE_FENETRE, this->geometry());
    qDebug() << m_settings->value(GEOMETRIE_FENETRE, 0);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    m_settings->setValue(GEOMETRIE_FENETRE, this->geometry());
}

//*********************************************************************************************************************
//**********************************************METHODES PUBLIQUES*****************************************************
//*********************************************************************************************************************

//*********************************************************************************************************************
//**************************************************SLOTS PRIVES*******************************************************
//*********************************************************************************************************************

void MainWindow::MAJC(int index)//___________________________________________________________________________Debut MAJC
{
    m_listeChronometres.removeAt(index);
    for(int i = index ; i < m_listeChronometres.size(); i++){
        m_listeChronometres.at(i)->deplacer();
        m_listeChronometres.at(i)->setIndex(i);
    }
}//____________________________________________________________________________________________________________Fin MAJC
void MainWindow::MAJM(int index)//___________________________________________________________________________Debut MAJM
{
    m_listeMinuteurs.removeAt(index);
    for(int i = index ; i < m_listeMinuteurs.size(); i++){
        m_listeMinuteurs.at(i)->deplacer();
        m_listeMinuteurs.at(i)->setIndex(i);
    }
}//____________________________________________________________________________________________________________Fin MAJM
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
        connect(nouvelleFenetre,SIGNAL(accepted()),this, SLOT(settingsModifie()));
        nouvelleFenetre->show();
        break;
    case VALEUR_ACTION_AFFICHAGE:
        affichage = new Affichage(this);
        affichage->setAttribute(Qt::WA_DeleteOnClose);
        connect(affichage,SIGNAL(accepted()),this, SLOT(settingsModifie()));
        affichage->show();
        break;
    case VALEUR_ACTION_THEME :
        theme = new Theme(this);
        theme->setAttribute(Qt::WA_DeleteOnClose);
        connect(theme,SIGNAL(accepted()),this, SLOT(settingsModifie()));
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
        if(paramReveils->exec()){
            reveilModel= new ReveilModel(m_settings->value(HEURE_REVEILS).toList().last().toString(),
                                         m_settings->value(PATH_AUDIO).toString(),this);
            m_listeReveils.append(reveilModel);
            settingsModifie();
        }
        break;
    case VALEUR_ACTION_PARAMETRE_REVEIL :
        paramReveils = new ParamReveils(m_settings->value(HEURE_REVEILS).toList().length(), this);
        paramReveils->setAttribute(Qt::WA_DeleteOnClose);
        if(paramReveils->exec()){
            settingsModifie();
        }
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
        settingsModifie();
        break;
    default:
        break;
    }
}//______________________________________________________________________________________________________Fin menuAction
void MainWindow::settingsModifie()//______________________________________________________________Debut settingsModifie
{
    m_listeHeures.clear();
    switch (m_settings->value(STYLE_HORLOGE).toInt()) {
    case 0:
        m_listeHeures.append("1");
        m_listeHeures.append("2");
        m_listeHeures.append("3");
        m_listeHeures.append("4");
        m_listeHeures.append("5");
        m_listeHeures.append("6");
        m_listeHeures.append("7");
        m_listeHeures.append("8");
        m_listeHeures.append("9");
        m_listeHeures.append("10");
        m_listeHeures.append("11");
        m_listeHeures.append("12");
        break;
    case 1:
        m_listeHeures.append("I");
        m_listeHeures.append("II");
        m_listeHeures.append("III");
        m_listeHeures.append("IV");
        m_listeHeures.append("V");
        m_listeHeures.append("VI");
        m_listeHeures.append("VII");
        m_listeHeures.append("VIII");
        m_listeHeures.append("IX");
        m_listeHeures.append("X");
        m_listeHeures.append("XI");
        m_listeHeures.append("XII");
        break;
    case 2:
        m_listeHeures.append("0001");
        m_listeHeures.append("0010");
        m_listeHeures.append("0011");
        m_listeHeures.append("0100");
        m_listeHeures.append("0101");
        m_listeHeures.append("0110");
        m_listeHeures.append("0111");
        m_listeHeures.append("1000");
        m_listeHeures.append("1001");
        m_listeHeures.append("1010");
        m_listeHeures.append("1011");
        m_listeHeures.append("1100");
        break;
    case 3:
        m_listeHeures.append("1");
        m_listeHeures.append("2");
        m_listeHeures.append("3");
        m_listeHeures.append("4");
        m_listeHeures.append("5");
        m_listeHeures.append("6");
        m_listeHeures.append("7");
        m_listeHeures.append("8");
        m_listeHeures.append("9");
        m_listeHeures.append("A");
        m_listeHeures.append("B");
        m_listeHeures.append("C");
        break;
    default:
        break;
    }
}//_________________________________________________________________________________________________Fin settingsModifie
void MainWindow::timerSlot()//__________________________________________________________________________Debut timerSlot
{
    if(!m_timer->property("isSync").toBool()){
        m_timer->setInterval(TIMER_DELAY);
        m_timer->setProperty("isSync", true);
    }
    ui->label->setSecondes();
    update();
}//_______________________________________________________________________________________________________Fin timerSlot
