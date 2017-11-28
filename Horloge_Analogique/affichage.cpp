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
    m_settings->setValue(FORME_AIGUILLE, ui->comboBoxFormeAiguille->currentIndex());
    m_settings->setValue(TYPE_DE_FOND, ui->comboBoxTypeFond->currentIndex());
    m_settings->setValue(COULEUR_HEURE, m_couleurHeureTMP);
    m_settings->setValue(COULEUR_MINUTE, m_couleurMinuteTMP);
    m_settings->setValue(COULEUR_SECONDE, m_couleurSecondeTMP);
    m_settings->setValue(COULEUR_TEXTE, m_couleurTexteTMP);
    m_settings->setValue(TRANSPARENCE, ui->spinBoxTranspFond->value());
    m_settings->setValue(TAILLE_TEXTE, ui->spinBoxTailleTexte->value());
}
