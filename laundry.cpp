#include "laundry.h"
#include "ui_laundry.h"

Laundry::Laundry(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Laundry)
{
    ui->setupUi(this);
}

Laundry::~Laundry()
{
    delete ui;
}
