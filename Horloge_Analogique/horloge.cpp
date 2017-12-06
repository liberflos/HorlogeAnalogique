#include "horloge.h"
#include "ui_horloge.h"

Horloge::Horloge(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::Horloge)
{
    ui->setupUi(this);
    m_settings = new QSettings("AppliHours", "HorlogeAnalogique");
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
    m_heures = QTime::currentTime().hour();
    m_minutes = QTime::currentTime().minute() + m_heures*60;
    m_secondes = QTime::currentTime().second();
    m_sXPos= 145 + 125*cos((PI/2)-(m_secondes*PI)/FRACTION_MINUTES);
    m_sYPos= 40 +(125 - 125*sin((PI/2) +(m_secondes*PI)/FRACTION_MINUTES));
    m_mXPos= 145 + 125*cos((PI/2)-(m_minutes*PI)/FRACTION_MINUTES);
    m_mYPos= 165 - 125*sin((PI/2) +(m_minutes*PI)/FRACTION_MINUTES);
    m_hXPos= 145 + 125*cos((PI/2)-(m_minutes*PI)/FRACTION_HEURES);
    m_hYPos= 165 - 125*sin((PI/2) +(m_minutes*PI)/FRACTION_HEURES);

}

Horloge::~Horloge()
{
    delete ui;
}

void Horloge::paintEvent(QPaintEvent *)
{
    int fontSize = m_settings->value(TAILLE_TEXTE, 14).toInt();

    QPainter painter(this);
    m_couleur.setRgba(m_settings->value(COULEUR_FOND, 0).toInt());
    m_brush.setStyle(Qt::SolidPattern);
    m_brush.setColor(m_couleur);
    painter.setBrush(m_brush);
    m_font.setPointSize(fontSize);
    painter.setFont(m_font);
    m_cXPos = this->width()/2;
    m_cYPos = this->height()/2;
    m_centre.setX(m_cXPos);
    m_centre.setY(m_cYPos);
    if(this->height() > this->width()){
        m_sXPos= m_cXPos+ (m_cXPos - DECALAGE)*cos((PI/2)-(m_secondes*PI)/FRACTION_MINUTES);
        m_sYPos= m_cYPos- (m_cXPos - DECALAGE)*sin((PI/2)-(m_secondes*PI)/FRACTION_MINUTES);
        m_mXPos= m_cXPos+ (m_cXPos - DECALAGE)*cos((PI/2)-(m_minutes*PI)/FRACTION_MINUTES);
        m_mYPos= m_cYPos- (m_cXPos - DECALAGE)*sin((PI/2)-(m_minutes*PI)/FRACTION_MINUTES);
        m_hXPos= m_cXPos+ (m_cXPos - DECALAGE)*cos((PI/2)-(m_minutes*PI)/FRACTION_HEURES);
        m_hYPos= m_cYPos- (m_cXPos - DECALAGE)*sin((PI/2)-(m_minutes*PI)/FRACTION_HEURES);
        painter.drawEllipse(m_centre,m_cXPos,m_cXPos);
//        m_couleur.setRgba(m_settings->value(COULEUR_HEURE, 0).toInt());
//        painter.setPen(m_couleur);
        for(int i = 0 ; i < 600 ; i++){
            painter.drawLine(m_cXPos + ((m_cXPos - DECALAGE)/20)*cos((PI/2)-(m_minutes*PI)/FRACTION_HEURES + i)
                             ,m_cYPos - ((m_cXPos - DECALAGE)/20)*sin((PI/2)-(m_minutes*PI)/FRACTION_HEURES + i),m_hXPos,m_hYPos);

        }
//        m_couleur.setRgba(m_settings->value(COULEUR_MINUTE, 0).toInt());
//        painter.setPen(m_couleur);
        for(int i = 0 ; i < 400 ; i++){
            painter.drawLine(m_cXPos + ((m_cXPos - DECALAGE)/30)*cos((PI/2)-(m_minutes*PI)/FRACTION_MINUTES + i)
                             ,m_cYPos - ((m_cXPos - DECALAGE)/30)*sin((PI/2)-(m_minutes*PI)/FRACTION_MINUTES + i),m_mXPos,m_mYPos);


        }
//        m_couleur.setRgba(m_settings->value(COULEUR_SECONDE, 0).toInt());
//        painter.setPen(m_couleur);
        for(int i = 0 ; i < 300 ; i++){
            painter.drawLine(m_cXPos + ((m_cXPos - DECALAGE)/50)*cos((PI/2)-(m_secondes*PI)/FRACTION_MINUTES + i)
                             ,m_cYPos - ((m_cXPos - DECALAGE)/50)*sin((PI/2)-(m_secondes*PI)/FRACTION_MINUTES + i),m_sXPos,m_sYPos);
        }
//        m_couleur.setRgba(m_settings->value(COULEUR_TEXTE, 0).toInt());
//        painter.setPen(m_couleur);

        for(int i = 1 ; i <= 60 ; i++){
            if(i%5 == 0){
                painter.drawText(m_cXPos+ (m_cXPos - fontSize)*cos((PI/2)-(i*PI)/FRACTION_MINUTES) - fontSize
                                 ,m_cYPos- (m_cXPos - fontSize)*sin((PI/2)-(i*PI)/FRACTION_MINUTES) - fontSize
                                 ,2*fontSize,2*fontSize, Qt::AlignCenter,m_listeHeures.at(i/5 -1));
            }
            m_point.setX(m_cXPos+ (m_cXPos - 2*fontSize)*cos((PI/2)-(i*PI)/FRACTION_MINUTES));
            m_point.setY(m_cYPos- (m_cXPos - 2*fontSize)*sin((PI/2)-(i*PI)/FRACTION_MINUTES));
            painter.drawEllipse(m_point,1,1);
        }
        painter.drawText(m_cXPos - (m_font.pointSize()/3)*QDate::currentDate().toString().length() , m_centre.y() + m_cXPos/3,QDate::currentDate().toString());

    }else{
        m_sXPos= m_cXPos + (m_cYPos - DECALAGE)*cos((PI/2)-(m_secondes*PI)/FRACTION_MINUTES);
        m_sYPos= m_cYPos - (m_cYPos - DECALAGE)*sin((PI/2)-(m_secondes*PI)/FRACTION_MINUTES);
        m_mXPos= m_cXPos + (m_cYPos - DECALAGE)*cos((PI/2)-(m_minutes*PI)/FRACTION_MINUTES);
        m_mYPos= m_cYPos - (m_cYPos - DECALAGE)*sin((PI/2)-(m_minutes*PI)/FRACTION_MINUTES);
        m_hXPos= m_cXPos + (m_cYPos - DECALAGE)*cos((PI/2)-(m_minutes*PI)/FRACTION_HEURES);
        m_hYPos= m_cYPos - (m_cYPos - DECALAGE)*sin((PI/2)-(m_minutes*PI)/FRACTION_HEURES);
        painter.drawEllipse(m_centre,m_cYPos,m_cYPos);
//        m_couleur.setRgba(m_settings->value(COULEUR_HEURE, 0).toInt());
//        painter.setPen(m_couleur);
        for(int i = 0 ; i < 600 ; i++){
            painter.drawLine(m_cXPos + ((m_cYPos - DECALAGE)/20)*cos((PI/2)-(m_minutes*PI)/FRACTION_HEURES + i)
                             ,m_cYPos - ((m_cYPos - DECALAGE)/20)*sin((PI/2)-(m_minutes*PI)/FRACTION_HEURES + i),m_hXPos,m_hYPos);

        }
//        m_couleur.setRgba(m_settings->value(COULEUR_MINUTE, 0).toInt());
//        painter.setPen(m_couleur);
        for(int i = 0 ; i < 400 ; i++){
            painter.drawLine(m_cXPos + ((m_cYPos - DECALAGE)/30)*cos((PI/2)-(m_minutes*PI)/FRACTION_MINUTES + i)
                             ,m_cYPos - ((m_cYPos - DECALAGE)/30)*sin((PI/2)-(m_minutes*PI)/FRACTION_MINUTES + i),m_mXPos,m_mYPos);


        }
//        m_couleur.setRgba(m_settings->value(COULEUR_SECONDE, 0).toInt());
//        painter.setPen(m_couleur);
        for(int i = 0 ; i < 300 ; i++){
            painter.drawLine(m_cXPos + ((m_cYPos - DECALAGE)/50)*cos((PI/2)-(m_secondes*PI)/FRACTION_MINUTES + i)
                             ,m_cYPos - ((m_cYPos - DECALAGE)/50)*sin((PI/2)-(m_secondes*PI)/FRACTION_MINUTES + i),m_sXPos,m_sYPos);
        }
//        m_couleur.setRgba(m_settings->value(COULEUR_TEXTE, 0).toInt());
//        painter.setPen(m_couleur);
        for(int i = 1 ; i <= 60 ; i++){
            if(i%5 == 0){
                painter.drawText(m_cXPos+ (m_cYPos - fontSize)*cos((PI/2)-(i*PI)/FRACTION_MINUTES) - fontSize
                                 ,m_cYPos - (m_cYPos - fontSize)*sin((PI/2)-(i*PI)/FRACTION_MINUTES) - fontSize
                                 ,2*fontSize ,2*fontSize , Qt::AlignCenter,m_listeHeures.at(i/5 - 1));
            }
            m_point.setX(m_cXPos + (m_cYPos - 2*fontSize)*cos((PI/2)-(i*PI)/FRACTION_MINUTES));
            m_point.setY(m_cYPos - (m_cYPos - 2*fontSize)*sin((PI/2)-(i*PI)/FRACTION_MINUTES));
            painter.drawEllipse(m_point,1,1);
        }
        painter.drawText(m_cXPos - (m_font.pointSize()/3)*QDate::currentDate().toString().length() , m_cYPos + m_cYPos/3,QDate::currentDate().toString());

    }


}

void Horloge::setParametres(int heures, int minutes, int secondes)
{
    m_heures = heures;
    m_minutes = minutes;
    m_secondes = secondes;
}

void Horloge::setHeures()
{
    m_heures++;

}

void Horloge::setMinutes()
{
    m_minutes++;

}

void Horloge::setSecondes()
{
qDebug() << "increment";
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

}

















//int fontSize = m_settings->value(TAILLE_TEXTE, 14).toInt();

//QPainter painter(this);
//m_couleur.setRgba(m_settings->value(COULEUR_FOND, 0).toInt());
//m_brush.setStyle(Qt::SolidPattern);
//m_brush.setColor(m_couleur);
//painter.setBrush(m_brush);
//m_font.setPointSize(fontSize);
//painter.setFont(m_font);
//m_cXPos = this->width()/2;
//m_cYPos = this->height()/2 + ui->menuBar->height()/2;
//m_centre.setX(m_cXPos);
//m_centre.setY(m_cYPos);
//if(this->height() - ui->menuBar->height() > this->width()){
//    m_sXPos= m_cXPos+ (m_cXPos - DECALAGE)*cos((PI/2)-(m_secondes*PI)/FRACTION_MINUTES);
//    m_sYPos= m_cYPos- (m_cXPos - DECALAGE)*sin((PI/2)-(m_secondes*PI)/FRACTION_MINUTES);
//    m_mXPos= m_cXPos+ (m_cXPos - DECALAGE)*cos((PI/2)-(m_minutes*PI)/FRACTION_MINUTES);
//    m_mYPos= m_cYPos- (m_cXPos - DECALAGE)*sin((PI/2)-(m_minutes*PI)/FRACTION_MINUTES);
//    m_hXPos= m_cXPos+ (m_cXPos - DECALAGE)*cos((PI/2)-(m_minutes*PI)/FRACTION_HEURES);
//    m_hYPos= m_cYPos- (m_cXPos - DECALAGE)*sin((PI/2)-(m_minutes*PI)/FRACTION_HEURES);
//    painter.drawEllipse(m_centre,m_cXPos,m_cXPos);
//    m_couleur.setRgba(m_settings->value(COULEUR_HEURE, 0).toInt());
//    painter.setPen(m_couleur);
//    for(int i = 0 ; i < 600 ; i++){
//        painter.drawLine(m_cXPos + ((m_cXPos - DECALAGE - ui->menuBar->height() )/20)*cos((PI/2)-(m_minutes*PI)/FRACTION_HEURES + i)
//                         ,m_cYPos - ((m_cXPos - DECALAGE - ui->menuBar->height() )/20)*sin((PI/2)-(m_minutes*PI)/FRACTION_HEURES + i),m_hXPos,m_hYPos);

//    }
//    m_couleur.setRgba(m_settings->value(COULEUR_MINUTE, 0).toInt());
//    painter.setPen(m_couleur);
//    for(int i = 0 ; i < 400 ; i++){
//        painter.drawLine(m_cXPos + ((m_cXPos - DECALAGE - ui->menuBar->height() )/30)*cos((PI/2)-(m_minutes*PI)/FRACTION_MINUTES + i)
//                         ,m_cYPos - ((m_cXPos - DECALAGE - ui->menuBar->height() )/30)*sin((PI/2)-(m_minutes*PI)/FRACTION_MINUTES + i),m_mXPos,m_mYPos);


//    }
//    m_couleur.setRgba(m_settings->value(COULEUR_SECONDE, 0).toInt());
//    painter.setPen(m_couleur);
//    for(int i = 0 ; i < 300 ; i++){
//        painter.drawLine(m_cXPos + ((m_cXPos - DECALAGE - ui->menuBar->height() )/50)*cos((PI/2)-(m_secondes*PI)/FRACTION_MINUTES + i)
//                         ,m_cYPos - ((m_cXPos - DECALAGE - ui->menuBar->height() )/50)*sin((PI/2)-(m_secondes*PI)/FRACTION_MINUTES + i),m_sXPos,m_sYPos);
//    }
//    m_couleur.setRgba(m_settings->value(COULEUR_TEXTE, 0).toInt());
//    painter.setPen(m_couleur);

//    for(int i = 1 ; i <= 60 ; i++){
//        if(i%5 == 0){
//            painter.drawText(m_cXPos+ (m_cXPos - fontSize)*cos((PI/2)-(i*PI)/FRACTION_MINUTES) - fontSize
//                             ,m_cYPos- (m_cXPos - fontSize)*sin((PI/2)-(i*PI)/FRACTION_MINUTES) - fontSize
//                             ,2*fontSize,2*fontSize, Qt::AlignCenter,m_listeHeures.at(i/5 -1));
//        }
//        m_point.setX(m_cXPos+ (m_cXPos - 2*fontSize)*cos((PI/2)-(i*PI)/FRACTION_MINUTES));
//        m_point.setY(m_cYPos- (m_cXPos - 2*fontSize)*sin((PI/2)-(i*PI)/FRACTION_MINUTES));
//        painter.drawEllipse(m_point,1,1);
//    }
//    painter.drawText(m_cXPos - (m_font.pointSize()/3)*QDate::currentDate().toString().length() , m_centre.y() + m_cXPos/3,QDate::currentDate().toString());

//}else{
//    m_sXPos= m_cXPos + (m_cYPos - DECALAGE - ui->menuBar->height() )*cos((PI/2)-(m_secondes*PI)/FRACTION_MINUTES);
//    m_sYPos= m_cYPos - (m_cYPos - DECALAGE - ui->menuBar->height() )*sin((PI/2)-(m_secondes*PI)/FRACTION_MINUTES);
//    m_mXPos= m_cXPos + (m_cYPos - DECALAGE - ui->menuBar->height() )*cos((PI/2)-(m_minutes*PI)/FRACTION_MINUTES);
//    m_mYPos= m_cYPos - (m_cYPos - DECALAGE - ui->menuBar->height() )*sin((PI/2)-(m_minutes*PI)/FRACTION_MINUTES);
//    m_hXPos= m_cXPos + (m_cYPos - DECALAGE - ui->menuBar->height() )*cos((PI/2)-(m_minutes*PI)/FRACTION_HEURES);
//    m_hYPos= m_cYPos - (m_cYPos - DECALAGE - ui->menuBar->height() )*sin((PI/2)-(m_minutes*PI)/FRACTION_HEURES);
//    painter.drawEllipse(m_centre,m_cYPos - ui->menuBar->height(),m_cYPos - ui->menuBar->height());
//    m_couleur.setRgba(m_settings->value(COULEUR_HEURE, 0).toInt());
//    painter.setPen(m_couleur);
//    for(int i = 0 ; i < 600 ; i++){
//        painter.drawLine(m_cXPos + ((m_cYPos - DECALAGE - ui->menuBar->height() )/20)*cos((PI/2)-(m_minutes*PI)/FRACTION_HEURES + i)
//                         ,m_cYPos - ((m_cYPos - DECALAGE - ui->menuBar->height() )/20)*sin((PI/2)-(m_minutes*PI)/FRACTION_HEURES + i),m_hXPos,m_hYPos);

//    }
//    m_couleur.setRgba(m_settings->value(COULEUR_MINUTE, 0).toInt());
//    painter.setPen(m_couleur);
//    for(int i = 0 ; i < 400 ; i++){
//        painter.drawLine(m_cXPos + ((m_cYPos - DECALAGE - ui->menuBar->height() )/30)*cos((PI/2)-(m_minutes*PI)/FRACTION_MINUTES + i)
//                         ,m_cYPos - ((m_cYPos - DECALAGE - ui->menuBar->height() )/30)*sin((PI/2)-(m_minutes*PI)/FRACTION_MINUTES + i),m_mXPos,m_mYPos);


//    }
//    m_couleur.setRgba(m_settings->value(COULEUR_SECONDE, 0).toInt());
//    painter.setPen(m_couleur);
//    for(int i = 0 ; i < 300 ; i++){
//        painter.drawLine(m_cXPos + ((m_cYPos - DECALAGE - ui->menuBar->height() )/50)*cos((PI/2)-(m_secondes*PI)/FRACTION_MINUTES + i)
//                         ,m_cYPos - ((m_cYPos - DECALAGE - ui->menuBar->height() )/50)*sin((PI/2)-(m_secondes*PI)/FRACTION_MINUTES + i),m_sXPos,m_sYPos);
//    }
//    m_couleur.setRgba(m_settings->value(COULEUR_TEXTE, 0).toInt());
//    painter.setPen(m_couleur);
//    for(int i = 1 ; i <= 60 ; i++){
//        if(i%5 == 0){
//            painter.drawText(m_cXPos+ (m_cYPos - fontSize - ui->menuBar->height())*cos((PI/2)-(i*PI)/FRACTION_MINUTES) - fontSize
//                             ,m_cYPos - (m_cYPos - fontSize - ui->menuBar->height())*sin((PI/2)-(i*PI)/FRACTION_MINUTES) - fontSize
//                             ,2*fontSize ,2*fontSize , Qt::AlignCenter,m_listeHeures.at(i/5 - 1));
//        }
//        m_point.setX(m_cXPos + (m_cYPos - 2*fontSize - ui->menuBar->height() )*cos((PI/2)-(i*PI)/FRACTION_MINUTES));
//        m_point.setY(m_cYPos - (m_cYPos - 2*fontSize - ui->menuBar->height() )*sin((PI/2)-(i*PI)/FRACTION_MINUTES));
//        painter.drawEllipse(m_point,1,1);
//    }
//    painter.drawText(m_cXPos - (m_font.pointSize()/3)*QDate::currentDate().toString().length() , m_cYPos + m_cYPos/3,QDate::currentDate().toString());

//}
//qDebug() << "Fin paintevent";

