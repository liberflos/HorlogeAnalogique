#include "paramreveils.h"
#include "ui_paramreveils.h"

ParamReveils::ParamReveils(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParamReveils)
{
    ui->setupUi(this);
    m_settings = new QSettings("AppliHours", "HorlogeAnalogique");
    ReveilWidget *reveilWidget = new ReveilWidget(this);
    ui->verticalLayout->insertWidget(0, reveilWidget);
    m_listeReveils.append(reveilWidget);
        connect(ui->buttonBox,SIGNAL(accepted()),this, SLOT(accept()));
        connect(ui->buttonBox,SIGNAL(rejected()),this, SLOT(reject()));
        connect(this, SIGNAL(accepted()), this, SLOT(confirmeSettings()));
}

ParamReveils::ParamReveils(int numberOReveil, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ParamReveils)
{
    ui->setupUi(this);
    m_settings = new QSettings("AppliHours", "HorlogeAnalogique");
    for(int i = 0 ; i < numberOReveil ; i++){
        ReveilWidget *reveilWidget = new ReveilWidget(m_settings->value(HEURE_REVEILS).toList().at(i).toString(),
                                                      m_settings->value(PATH_AUDIO).toString(),this);
        ui->verticalLayout->insertWidget(i, reveilWidget);
        m_listeReveils.append(reveilWidget);
        reveilWidget->setProperty("index", i);
        connect(reveilWidget,SIGNAL(supprimerReveil_SIG(int)),this, SLOT(supprimerReveil(int)));
    }
        connect(ui->buttonBox,SIGNAL(accepted()),this, SLOT(accept()));
        connect(ui->buttonBox,SIGNAL(rejected()),this, SLOT(reject()));
        connect(this, SIGNAL(accepted()), this, SLOT(confirmeToutSettings()));

}

ParamReveils::~ParamReveils()
{
    delete ui;
}

void ParamReveils::confirmeSettings()
{
    m_settings->setValue(PATH_AUDIO, m_listeReveils.at(0)->getFilePath());
    QList<QVariant> liste;
    liste.append(m_settings->value(HEURE_REVEILS).toList());
    liste.append(m_listeReveils.at(0)->getTemps().toString());
    m_settings->setValue(HEURE_REVEILS, liste);
}

void ParamReveils::confirmeToutSettings()
{
    m_settings->setValue(PATH_AUDIO, m_listeReveils.at(0)->getFilePath());
    QStringList listeReveilActif;
    QList<QVariant> liste;
    for(int i = 0 ; i < m_listeReveils.length(); i++){
        liste.append(m_listeReveils.at(i)->getTemps().toString());
        if(m_listeReveils.at(i)->isActif()){
            listeReveilActif.append("1");
        }else{
            listeReveilActif.append("0");
        }
    }
    m_settings->setValue(REVEIL_ACTIF, listeReveilActif);
    m_settings->setValue(HEURE_REVEILS, liste);

}

void ParamReveils::supprimerReveil(int index)
{
    QList<QVariant> liste = m_settings->value(HEURE_REVEILS).toList();
    liste.removeAt(index);
    m_settings->setValue(HEURE_REVEILS,liste);
    m_listeReveils.at(index)->deleteLater();
    m_listeReveils.removeAt(index);
    for(int i = index; i < m_listeReveils.length(); i++){
        m_listeReveils.at(i)->setProperty("index", i);
    }
}
