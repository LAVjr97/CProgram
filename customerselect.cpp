#include "customerselect.h"
#include "ui_customerselect.h"

CustomerSelect::CustomerSelect(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CustomerSelect)
{
    ui->setupUi(this);
}

CustomerSelect::~CustomerSelect()
{
    delete ui;
}
