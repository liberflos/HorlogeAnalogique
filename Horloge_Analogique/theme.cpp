#include "theme.h"
#include "ui_theme.h"

Theme::Theme(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Theme)
{
    ui->setupUi(this);
    connect(ui->buttonBox,SIGNAL(accepted()),this, SLOT(accept()));
    connect(ui->buttonBox,SIGNAL(rejected()),this, SLOT(reject()));
}

Theme::~Theme()
{
    delete ui;
}
