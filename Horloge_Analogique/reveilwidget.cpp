#include "reveilwidget.h"
#include "ui_reveilwidget.h"
#include <QDebug>

ReveilWidget::ReveilWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReveilWidget)
{
    ui->setupUi(this);
    m_settings = new QSettings("AppliHours", "HorlogeAnalogique");
    ui->timeEdit->setTime(QTime::currentTime());
    ui->lineEditFilePath->setText(m_settings->value(PATH_AUDIO).toString());
    connect(ui->checkBox_8, SIGNAL(stateChanged(int)), this, SLOT(checkTheState()));
    this->setMinimumWidth(ui->horizontalLayout_2->minimumSize().width() + 20);
    connect(ui->toolButtonSelFile, SIGNAL(clicked(bool)), this, SLOT(selectSonnerie()));
    connect(ui->timeEdit, SIGNAL(timeChanged(QTime)), this, SLOT(setTemps(QTime)));
}

ReveilWidget::~ReveilWidget()
{
    delete ui;
}

QString ReveilWidget::getFilePath()
{
    return m_filePath;
}

QTime ReveilWidget::getTemps()
{
    return m_temps;
}



void ReveilWidget::selectSonnerie()
{
    QFileDialog *dialFichier = new QFileDialog(this);
    m_filePath = dialFichier->getOpenFileName();
    if(m_filePath.endsWith(".wav") || m_filePath.endsWith(".mp3")){
//            filePath.endsWith(".JPEG") || filePath.endsWith(".bmp")){
        ui->lineEditFilePath->setText(m_filePath);
    }else {
        QErrorMessage *message = new QErrorMessage(this);
        message->setWindowTitle("Erreur d'Extension");
        message->showMessage("le fichier selectionné n'est pas une image, ou l'extension n'est pas prise en charge.");
    }
}
void ReveilWidget::checkTheState()
{
    if(ui->checkBox_8->checkState() == Qt::PartiallyChecked ||ui->checkBox_8->checkState() == Qt::Unchecked){
        ui->spinBox->setDisabled(true);
    }else{
        ui->spinBox->setEnabled(true);
    }

}

void ReveilWidget::setTemps(QTime temps)
{
        m_temps = temps;
}
