#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pi = 3.141592654;
    qDebug() << QTime::currentTime().msec();
    m_heures = QTime::currentTime().hour();
    m_minutes = QTime::currentTime().minute() + m_heures*60;
    m_secondes = QTime::currentTime().second();
    sXPos= 145 + 125*cos((pi/2)-(m_secondes*pi)/30);
    sYPos= 40 +(125 - 125*sin((pi/2) +(m_secondes*pi)/30));
    mXPos= 145 + 125*cos((pi/2)-(m_minutes*pi)/30);
    mYPos= 165 - 125*sin((pi/2) +(m_minutes*pi)/30);
    hXPos= 145 + 125*cos((pi/2)-(m_minutes*pi)/360);
    hYPos= 165 - 125*sin((pi/2) +(m_minutes*pi)/360);
    timer = new QTimer(this);
    timer->setProperty("isSync", false);
    connect(timer, SIGNAL(timeout()),this,SLOT(timerSlot()));
    timer->start(1000 - QTime::currentTime().msec());

    ui->actionParametres_de_l_heure->setProperty(PROPRIETE_ACTION_MENU,VALEUR_ACTION_PARAMETRE_HEURE);
    connect(ui->menuBar,SIGNAL(triggered(QAction*)),this, SLOT(menuAction(QAction*)));
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_Q))
        close();
}
void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    cXPos = this->width()/2;
    cYPos = this->height()/2 + ui->menuBar->height()/2;
    QColor couleur;
    centre.setX(cXPos);
    centre.setY(cYPos);
//    centre.setY(cYPos + ui->menuBar->height()/2);

    if(this->height() - ui->menuBar->height() > this->width()){
        sXPos= cXPos+ (cXPos - 5)*cos((pi/2)-(m_secondes*pi)/30);
        sYPos= cYPos- (cXPos - 5)*sin((pi/2)-(m_secondes*pi)/30);
        mXPos= cXPos+ (cXPos - 5)*cos((pi/2)-(m_minutes*pi)/30);
        mYPos= cYPos- (cXPos - 5)*sin((pi/2)-(m_minutes*pi)/30);
        hXPos=  cXPos+ (cXPos - 5)*cos((pi/2)-(m_minutes*pi)/360);
        hYPos= cYPos- (cXPos - 5)*sin((pi/2)-(m_minutes*pi)/360);
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
                painter.drawText(cXPos+ (cXPos - 10)*cos((pi/2)-(i*pi)/30) -10,cYPos- (cXPos - 10)*sin((pi/2)-(i*pi)/30) - 10,20,20, Qt::AlignCenter,QString::number(i/5));
            }
            point.setX(cXPos+ (cXPos - 20)*cos((pi/2)-(i*pi)/30));
            point.setY(cYPos- (cXPos - 20)*sin((pi/2)-(i*pi)/30));
            painter.drawEllipse(point,1,1);
        }
    }else{
        sXPos= cXPos+ (cYPos - 5 - ui->menuBar->height() )*cos((pi/2)-(m_secondes*pi)/30);
        sYPos= cYPos- (cYPos - 5 - ui->menuBar->height() )*sin((pi/2)-(m_secondes*pi)/30);
        mXPos= cXPos+ (cYPos - 5 - ui->menuBar->height() )*cos((pi/2)-(m_minutes*pi)/30);
        mYPos= cYPos- (cYPos - 5 - ui->menuBar->height() )*sin((pi/2)-(m_minutes*pi)/30);
        hXPos=  cXPos+ (cYPos - 5 - ui->menuBar->height() )*cos((pi/2)-(m_minutes*pi)/360);
        hYPos= cYPos- (cYPos - 5 - ui->menuBar->height() )*sin((pi/2)-(m_minutes*pi)/360);
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
                painter.drawText(cXPos+ (cYPos - 10 - ui->menuBar->height())*cos((pi/2)-(i*pi)/30) -10,cYPos - (cYPos - 10 - ui->menuBar->height())*sin((pi/2)-(i*pi)/30) - 10,20,20, Qt::AlignCenter,QString::number(i/5));
            }
            point.setX(cXPos+ (cYPos - 20 - ui->menuBar->height() )*cos((pi/2)-(i*pi)/30));
            point.setY(cYPos - (cYPos - 20 - ui->menuBar->height() )*sin((pi/2)-(i*pi)/30));
            painter.drawEllipse(point,1,1);
        }
    }
}

void MainWindow::timerSlot()
{
    if(!timer->property("isSync").toBool()){
        timer->setInterval(1000);
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

}

void MainWindow::menuAction(QAction *action)
{
    switch (action->property(PROPRIETE_ACTION_MENU).toInt()) {
//    case ui->actionParametres_de_l_heure->property(PROPRIETE_ACTION_MENU).toInt():

//        break;
//    case ui->actionAffichage->objectName():

//        break;
//    case ui->actionParametres_de_l_heure->objectName():

//        break;
//    case ui->actionParametres_de_l_heure->objectName():

//        break;
//    case ui->actionParametres_de_l_heure->objectName():

//        break;
    default:
        break;
    }
}

