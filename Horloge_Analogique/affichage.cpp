#include "affichage.h"
#include "ui_affichage.h"
#include <QSettings>
#include <QDebug>

Affichage::Affichage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Affichage)
{
    ui->setupUi(this);
    m_settings = new QSettings("AppliHours", "HorlogeAnalogique");
    connect(ui->buttonBox,SIGNAL(accepted()),this, SLOT(accept()));
    connect(ui->buttonBox,SIGNAL(rejected()),this, SLOT(reject()));
    connect(this, SIGNAL(accepted()), this, SLOT(confirmeSettings()));
    ui->comboBoxTypeHorloge->addItem("Analogique");
    ui->comboBoxTypeHorloge->addItem("Numerique");
    ui->comboBoxTypeHorloge->setCurrentIndex(m_settings->value(TYPE_HORLOGE, 0).toInt());
    ui->spinBoxTailleTexte->setValue(m_settings->value(TAILLE_TEXTE, 14).toInt());
    connect(ui->comboBoxTypeHorloge, SIGNAL(activated(int)), this, SLOT(setTypeHorloge(int)));
}

Affichage::~Affichage()
{
    delete ui;
}

void Affichage::setTypeHorloge(int type)
{
    m_typeHorlogeTMP = type;
}

void Affichage::confirmeSettings()
{
    m_settings->setValue(TYPE_HORLOGE, ui->comboBoxTypeHorloge->currentIndex());
    m_settings->setValue("FormeAiguille", ui->comboBoxFormeAiguille->currentIndex());
    m_settings->setValue("TypeDeFond", ui->comboBoxTypeFond->currentIndex());
    m_settings->setValue("CouleurHeure", m_couleurHeureTMP);
    m_settings->setValue("CouleurMinute", m_couleurMinuteTMP);
    m_settings->setValue("CouleurSecondes", m_couleurSecondeTMP);
    m_settings->setValue("CouleurTexte", m_couleurTexteTMP);
    m_settings->setValue("Transparence", ui->spinBoxTranspFond->value());
    m_settings->setValue(TAILLE_TEXTE, ui->spinBoxTailleTexte->value());
}
