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

    ui->comboBoxTypeHorloge->addItem("Analogique");
    ui->comboBoxTypeHorloge->addItem("Numerique");
    ui->comboBoxTypeHorloge->setCurrentIndex(m_settings->value(TYPE_HORLOGE, 0).toInt());
    ui->comboBoxTypeFond->addItem("Image");
    ui->comboBoxTypeFond->addItem("Couleur");
    ui->spinBoxTailleTexte->setValue(m_settings->value(TAILLE_TEXTE, 14).toInt());
    ui->lineEditImageFond->setText(m_settings->value(PATH_IMAGE, "").toString());

    if(ui->comboBoxTypeFond->currentIndex() == 0){
        ui->labelCouleurFond->hide();
        ui->pushButtonCouleurFond->hide();
    }else if(ui->comboBoxTypeFond->currentIndex() == 1){
        ui->labelImageFond->hide();
        ui->lineEditImageFond->hide();
        ui->toolButtonImageFond->hide();
    }

    connect(ui->buttonBox,SIGNAL(accepted()),this, SLOT(accept()));
    connect(ui->buttonBox,SIGNAL(rejected()),this, SLOT(reject()));
    connect(this, SIGNAL(accepted()), this, SLOT(confirmeSettings()));
    connect(ui->comboBoxTypeHorloge, SIGNAL(activated(int)), this, SLOT(setTypeHorloge(int)));
    connect(ui->comboBoxTypeFond,SIGNAL(activated(int)),this, SLOT(setTypeFond(int)));
    connect(ui->toolButtonImageFond, SIGNAL(clicked(bool)), this, SLOT(selectImage()));
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
    m_settings->setValue(PATH_IMAGE, ui->lineEditImageFond->text());
}

void Affichage::setTypeFond(int index)
{
    if(index == 0){
        ui->labelCouleurFond->hide();
        ui->pushButtonCouleurFond->hide();
        ui->labelImageFond->show();
        ui->lineEditImageFond->show();
        ui->toolButtonImageFond->show();
    }else if(index == 1){
        ui->labelImageFond->hide();
        ui->lineEditImageFond->hide();
        ui->toolButtonImageFond->hide();
        ui->labelCouleurFond->show();
        ui->pushButtonCouleurFond->show();
    }

}

void Affichage::selectImage()
{
    QFileDialog *dialFichier = new QFileDialog(this);
    QString filePath;
    filePath = dialFichier->getOpenFileName();
    if(filePath.endsWith(".jpg") || filePath.endsWith(".png") ||
            filePath.endsWith(".JPEG") || filePath.endsWith(".bmp")){
        ui->lineEditImageFond->setText(filePath);
    }else {
        QErrorMessage *message = new QErrorMessage(this);
        message->setWindowTitle("Erreur d'Extension");
        message->showMessage("le fichier selectionné n'est pas une image, ou l'extension n'est pas prise en charge.");
    }
}
