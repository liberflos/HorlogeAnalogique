#include "theme.h"
#include "ui_theme.h"

Theme::Theme(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Theme)
{
    ui->setupUi(this);
    m_settings = new QSettings("AppliHours", "HorlogeAnalogique");
    ui->comboBoxStyleHorloge->addItem("Chiffres Arabes");
    ui->comboBoxStyleHorloge->addItem("Chiffres Romains");
    ui->comboBoxStyleHorloge->addItem("chiffres Binaires");
    ui->comboBoxStyleHorloge->addItem("chiffres Hexadecimals");
    ui->comboBoxThemeHorloge->addItem("Old School");
    ui->comboBoxThemeHorloge->addItem("Matrix");
    ui->comboBoxThemeHorloge->addItem("8 bits");
    ui->comboBoxTypeChrono->addItem("Analogique");
    ui->comboBoxTypeChrono->addItem("Numerique");

    ui->comboBoxStyleHorloge->setCurrentIndex(m_settings->value(STYLE_HORLOGE).toInt());
    connect(ui->buttonBox,SIGNAL(accepted()),this, SLOT(accept()));
    connect(ui->buttonBox,SIGNAL(rejected()),this, SLOT(reject()));
    connect(this,SIGNAL(accepted()),this, SLOT(confirmeSettings()));
}

Theme::~Theme()
{
    delete ui;
}

void Theme::confirmeSettings()
{
    m_settings->setValue(STYLE_HORLOGE, ui->comboBoxStyleHorloge->currentIndex());
    m_settings->setValue(THEME_HORLOGE, ui->comboBoxThemeHorloge->currentIndex());
    m_settings->setValue(TYPE_CHRONO, ui->comboBoxTypeChrono->currentIndex());
}
