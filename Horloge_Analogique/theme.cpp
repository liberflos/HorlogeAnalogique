#include "theme.h"
#include "ui_theme.h"

Theme::Theme(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Theme)
{
    ui->setupUi(this);
    ui->comboBoxStyleHorloge->addItem("Chiffres Arabes");
    ui->comboBoxStyleHorloge->addItem("Chiffres Romains");
    ui->comboBoxStyleHorloge->addItem("chiffres Binaires");
    ui->comboBoxStyleHorloge->addItem("chiffres Hexadecimals");
    ui->comboBoxThemeHorloge->addItem("Old School");
    ui->comboBoxThemeHorloge->addItem("Matrix");
    ui->comboBoxThemeHorloge->addItem("8 bits");
    ui->comboBoxTypeChrono->addItem("Analogique");
    ui->comboBoxTypeChrono->addItem("Numerique");
    connect(ui->buttonBox,SIGNAL(accepted()),this, SLOT(accept()));
    connect(ui->buttonBox,SIGNAL(rejected()),this, SLOT(reject()));
}

Theme::~Theme()
{
    delete ui;
}
