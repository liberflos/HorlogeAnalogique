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
