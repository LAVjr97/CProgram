#include "dropoffpage.h"
#include "ui_dropoffpage.h"

DropOffPage::DropOffPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DropOffPage)
{
    ui->setupUi(this);
}

DropOffPage::~DropOffPage()
{
    delete ui;
}

void DropOffPage::on_btnCustomer_clicked()
{

}


//Set functions
void DropOffPage::setDataStructures(std::unordered_map<int, std::vector<orderInfo::order>> *orders, std::vector<cust::customer> *customers){
    this->orders = orders;
    this->customers = customers;
}
